#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include "projetmanager.h"
#include "tachefactory.h"
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
    qDebug()<<"debut load projetmanager";
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
            if(children.nodeName() == "disponibilite")
                dispo = QDate::fromString(children.toElement().text(),Qt::TextDate);
            if(children.nodeName() == "echeance")
                echeance = QDate::fromString(children.toElement().text(),Qt::TextDate);
        }
        //Ajouter le projet pour récupérer l'objet
        Projet& p = this->ajouterProjet(nom, description, dispo);

        //Lire toutes les taches et les ajouter au projet
        QDomNode taches = projet.firstChildElement("taches");

        //Si il y a des taches dans le projet, on doit les parcourir
        if(!taches.isNull()){
            for(QDomNode tache = taches.firstChildElement("tache"); !tache.isNull(); tache = tache.nextSiblingElement("tache")){
                QDomNodeList childrensTache = tache.childNodes();

                QDomElement tacheElement = tache.toElement();
                QString type = tacheElement.attribute("type");
                int etat = tacheElement.attribute("etat").toInt();

                QString identifiant;
                QString titre;
                QDate dispoTache;
                QDate echeanceTache;
                //Pour les tâches unitaires et préemptives
                QTime duree;
                //On construit la tache en parcourant tous les noeuds représentants ses caractéristiques
                for(unsigned int i = 0; i < childrensTache.length(); i++){
                    QDomNode children = childrensTache.at(i);
                    if(children.nodeName() == "identifiant")
                        identifiant = children.toElement().text();
                    if(children.nodeName() == "titre")
                        titre = children.toElement().text();
                    if(children.nodeName() == "disponibilite")
                        dispoTache = QDate::fromString(children.toElement().text(),Qt::TextDate);
                    if(children.nodeName() == "echeance")
                        echeanceTache = QDate::fromString(children.toElement().text(),Qt::TextDate);
                    if(type == "unitaire" || type == "preemptive"){
                        if(children.nodeName() == "duree"){
                            QTime tmp = QTime(children.toElement().attribute("heure").toInt(),children.toElement().attribute("minute").toInt());
                            duree = tmp;
                        }
                    }
                }

                //On construit l'objet tache qui convient en fonction du type de la tache
                //Mais on enregistre une Tache (générale donc) dans le vector taches du projet
                if(type == "unitaire"){
                    TacheFactory& tm = TacheFactory::getInstance();
                    Tache& t = dynamic_cast<Tache&>(tm.creerTacheUnitaire(identifiant, titre, dispoTache, echeanceTache, duree, etat));
                    //On ajoute la tache au projet que l'on est en train de parcourir
                    p.ajouterTache(t);
                }
                else if (type == "preemtive"){
                    TacheFactory& tm = TacheFactory::getInstance();
                    Tache& t = dynamic_cast<Tache&>(tm.creerTacheUnitairePreemptive(identifiant, titre, dispoTache, echeanceTache, duree, etat));
                    //On ajoute la tache au projet que l'on est en train de parcourir
                    p.ajouterTache(t);
                }
            }
        }
    }

    fin.close();
}

void  ProjetManager::save(const QString& f){
    qDebug()<<"debut save projetManager";
    file=f;
    QFile newfile( file);
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("projets");
    for(unsigned int i=0; i<projets.size(); i++){
        stream.writeStartElement("projet");
        stream.writeTextElement("nom",projets[i]->getNom());
        qDebug()<<"nom ="<<projets[i]->getNom();
        stream.writeTextElement("description",projets[i]->getDescription());
        qDebug()<<"description ="<<projets[i]->getDescription();
        stream.writeTextElement("disponibilite",projets[i]->getDisponibilite().toString(Qt::TextDate));
        qDebug()<<"dispo = "<<projets[i]->getDisponibilite().toString(Qt::TextDate);
        stream.writeTextElement("echeance",projets[i]->getEcheance().toString(Qt::TextDate));
        qDebug()<<"echeance = "<<projets[i]->getEcheance().toString(Qt::TextDate);
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

