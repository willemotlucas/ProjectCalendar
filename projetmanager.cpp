#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QDebug>
#include <typeinfo>
#include "global.h"

#include "projetmanager.h"
#include "projet.h"
#include "tachefactory.h"
#include "tachecomposite.h"
#include "calendarexception.h"

ProjetManager::Handler ProjetManager::handler=ProjetManager::Handler();

ProjetManager& ProjetManager::getInstance(){
    if (handler.instance==0) handler.instance=new ProjetManager;
    return *(handler.instance);
}

void ProjetManager::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

ProjetManager::ProjetManager():projets(0){projets.reserve(10);}

ProjetManager::~ProjetManager(){
    projets.clear();
}

Projet& ProjetManager::ajouterProjet(const QString &nom, const QString &desc, const QDate &dispo){
    if (trouverProjet(nom)){
        throw CalendarException("Le projet " + nom + " existe déjà.");
    }
    if(nom.isEmpty()){
        throw CalendarException("Attention, le nom de projet ne peut pas être vide.");
    }
    Projet* newp=new Projet(nom,desc,dispo);
    addItem(newp);
    return *newp;
}

void ProjetManager::addItem(Projet* p){
    projets.push_back(p);
}

const Projet& ProjetManager::getProjetConst(const QString& nom) const{
    for(unsigned int i=0; i<projets.size(); i++){
        if (nom==projets[i]->getNom()){
            return *projets[i];
        }
    }
}

Projet* ProjetManager::getProjet(const QString& nom) const{
    for(unsigned int i=0; i<projets.size(); i++){
        if (nom==projets[i]->getNom()){
            return projets[i];
        }
    }
    return NULL;
}


Projet* ProjetManager::trouverProjet(const QString& nom)const{
    for(unsigned int i=0; i<projets.size(); i++){
        if (nom==projets[i]->getNom()){
            return projets[i];
        }
    }
    return 0;
}

void ProjetManager::load(const QString& f){
    //Utilisation de la STL
    projets.clear();
    //delete[] projets;
    file=f;
    QDomDocument* dom = new QDomDocument("projets");
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier projets");
    }
    if(!dom->setContent(&fin)){
        throw CalendarException(QString("erreur ouverture projet : ouverture objet dom"));
    }

    QDomElement dom_element = dom->documentElement();

    //On parcourt chaque noeud <projet> pour créer les objets projets avec leur vector de tache correspondants
    for(QDomNode projet = dom_element.firstChildElement("projet"); !projet.isNull(); projet = projet.nextSiblingElement("projet")){
        QDomNodeList childrens = projet.childNodes();
        QString nom;
        QString description;
        QDate dispo;
        QDate echeance;
        //On parcourt toutes les caracteristiques d'un projet pour construire l'objet
        for(unsigned int i = 0; i < childrens.length(); i++){
            QDomNode children = childrens.at(i);
            if(children.nodeName() == "nom")
                nom = children.toElement().text();
            if(children.nodeName() == "description")
                description = children.toElement().text();
            if(children.nodeName() == "dateDebut")
                dispo = QDate::fromString(children.toElement().text(),Qt::TextDate);
            if(children.nodeName() == "dateEcheance")
                echeance = QDate::fromString(children.toElement().text(),Qt::TextDate);
        }
        //Ajouter le projet pour récupérer l'objet
        Projet& p = this->ajouterProjet(nom, description, dispo);

        //Lire toutes les taches et les ajouter au projet
        QDomNode taches = projet.firstChildElement("taches");

        //Si il y a des taches dans le projet, on doit les parcourir
        if(!taches.isNull()){
            for(QDomNode tache = taches.firstChildElement("tache"); !tache.isNull(); tache = tache.nextSiblingElement("tache")){
                //QDomNodeList childrensTache = tache.childNodes();
                Tache& t = loadTache(dom, &tache);
                p.ajouterTache(t);
            }
        }
    }

    fin.close();
}

Tache& ProjetManager::loadTache(QDomDocument* dom ,QDomNode* tache){
    QDomNodeList childrensTache = tache->childNodes();
    QDomElement tacheElement = tache->toElement();
    QString type = tacheElement.attribute("type");

    int etat = tacheElement.attribute("etat").toInt();

    QString identifiant;
    QString titre;
    QDate dispoTache;
    QDate echeanceTache;
    //Pour les tâches unitaires et préemptives
    QTime duree;
    QTime dureeInit; //Pour les taches preemptives
    QTime dureeRestante; //Pour les taches preemptives

    if(type=="unitaire"){
        //On construit la tache en parcourant tous les noeuds représentants ses caractéristiques
        for(int i = 0; i < childrensTache.length(); i++){
            QDomNode children = childrensTache.at(i);
            if(children.nodeName() == "identifiant")
                identifiant = children.toElement().text();
            if(children.nodeName() == "titre")
                titre = children.toElement().text();
            if(children.nodeName() == "disponibilite")
                dispoTache = QDate::fromString(children.toElement().text(),Qt::TextDate);
            if(children.nodeName() == "echeance")
                echeanceTache = QDate::fromString(children.toElement().text(),Qt::TextDate);
            if(children.nodeName() == "duree"){
               QTime tmp = QTime(children.toElement().attribute("heure").toInt(),children.toElement().attribute("minute").toInt());
               duree = tmp;
            }
        }
        //On cree la tache unitaire
        TacheFactory& tm = TacheFactory::getInstance();
        Tache& t = dynamic_cast<Tache&>(tm.creerTacheUnitaire(identifiant, titre, dispoTache, echeanceTache, duree, etat));
        return t;
    }
    else if (type=="preemtive"){
        //On construit la tache en parcourant tous les noeuds représentants ses caractéristiques
        for(int i = 0; i < childrensTache.length(); i++){
            QDomNode children = childrensTache.at(i);
            if(children.nodeName() == "identifiant")
                identifiant = children.toElement().text();
            if(children.nodeName() == "titre")
                titre = children.toElement().text();
            if(children.nodeName() == "disponibilite")
                dispoTache = QDate::fromString(children.toElement().text(),Qt::TextDate);
            if(children.nodeName() == "echeance")
                echeanceTache = QDate::fromString(children.toElement().text(),Qt::TextDate);
            if(children.nodeName() == "dureeInitiale"){
                QTime tmp = QTime(children.toElement().attribute("heure").toInt(), children.toElement().attribute("minute").toInt());
                dureeInit = tmp;
            }
            if(children.nodeName() == "dureeRestante"){
                QTime tmp = QTime(children.toElement().attribute("heure").toInt(), children.toElement().attribute("minute").toInt());
                dureeRestante = tmp;
            }
        }

        //On cree la tache unitaire preemptive
        TacheFactory& tm = TacheFactory::getInstance();
        Tache& t = dynamic_cast<Tache&>(tm.creerTacheUnitairePreemptive(identifiant, titre, dispoTache, echeanceTache, dureeInit, dureeRestante, etat));
        return t;

    }
    else if (type=="composite"){
        //On construit la tache en parcourant tous les noeuds représentants ses caractéristiques
        for(int i = 0; i < childrensTache.length(); i++){
            QDomNode children = childrensTache.at(i);
            if(children.nodeName() == "identifiant")
                identifiant = children.toElement().text();
            if(children.nodeName() == "titre")
                titre = children.toElement().text();
            if(children.nodeName() == "disponibilite")
                dispoTache = QDate::fromString(children.toElement().text(),Qt::TextDate);
            if(children.nodeName() == "echeance")
                echeanceTache = QDate::fromString(children.toElement().text(),Qt::TextDate);

        }

        //On cree la tache unitaire composite
        TacheFactory& tm = TacheFactory::getInstance();
        TacheComposite& t =dynamic_cast<TacheComposite&>(tm.creerTacheComposite(identifiant, titre, dispoTache));

        //Lire toutes les soustaches et les ajouter a notre tache composite
        QDomNode* sousTaches = new QDomNode(tache->firstChildElement("soustaches"));

        if(!sousTaches->isNull()){
            for(QDomNode soustache = sousTaches->firstChildElement("tache"); !soustache.isNull(); soustache = soustache.nextSiblingElement("tache")){
                Tache& s = loadTache(dom, &soustache);
                t.ajouterSousTaches(s);
            }
        }
        return dynamic_cast<Tache&>(t);
    }
}




void  ProjetManager::save(){

    QDomDocument* dom = new QDomDocument("projets");
    QDomElement dom_element = dom->documentElement();

    //On créé le noeud <projets> qui contiendra tous les projets
    QDomNode projets = dom->createElement("projets");

    //On parcourt tous les projets du vector
    for(contProjet::iterator it = ProjetManager::begin(); it != ProjetManager::end(); ++it){
        //A chaque projet, on créé un noeud <projet> contenant le projet crée, son titre, description, etc...
        QDomElement projet = dom->createElement("projet");


        QDomElement nom = dom->createElement("nom");
        QDomText nomText = dom->createTextNode((*it)->getNom());
        nom.appendChild(nomText);

        QDomElement desc = dom->createElement("description");
        QDomText descText = dom->createTextNode((*it)->getDescription());
        desc.appendChild(descText);

        QDomElement dateDebut = dom->createElement("dateDebut");
        QDomText dateDebText = dom->createTextNode((*it)->getDisponibilite().toString(Qt::TextDate));
        dateDebut.appendChild(dateDebText);

        QDomElement dateEcheance = dom->createElement("dateEcheance");
        QDomText dateEchText = dom->createTextNode((*it)->getEcheance().toString(Qt::TextDate));
        dateEcheance.appendChild(dateEchText);

        QDomElement taches = dom->createElement("taches");
        for(std::vector<Tache*>::iterator i = (*it)->begin(); i != (*it)->end(); ++i){
            QDomElement m = (*i)->save(dom);
            taches.appendChild(m);
        }


        projet.appendChild(nom);
        projet.appendChild(desc);
        projet.appendChild(dateDebut);
        projet.appendChild(dateEcheance);
        projet.appendChild(taches);

        //Ajout du projet dans projetS !
        projets.appendChild(projet);
    }

    dom->appendChild(projets);

    QFile fichier(fileXML);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fichier.close();
        throw new CalendarException(QString("Erreur lors de l'ouverture du fichier " + fileXML + " pour écriture."));
    }

    //Ecriture de l'arbre DOM dans le fichier XML
    QString write_doc = dom->toString();
    QTextStream stream(&fichier);
    stream<<write_doc;
    fichier.close();
}
