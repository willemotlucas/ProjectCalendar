#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include "projetmanager.h"
#include "tachemanager.h"
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
    if(!dom->setContent(&fin))
        throw CalendarException(QString("erreur ouverture projet : ouverture objet dom"));

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
        qDebug()<<"nom = "<<nom<<"\n";
        qDebug()<<"description = "<<description<<"\n";
        qDebug()<<"dispo = "<<dispo<<"\n";
        qDebug()<<"echeance = "<<echeance<<"\n";

        //Ajouter le projet pour récupérer l'objet
        Projet& p = this->ajouterProjet(nom, description, dispo);

        //Lire toutes les taches et les ajouter au projet
        QDomNode taches = projet.firstChildElement("taches");

        //Si il y a des taches dans le projet, on doit les parcourir
        if(!taches.isNull()){
            for(QDomNode tache = taches.firstChildElement("tache"); !tache.isNull(); tache = tache.nextSiblingElement("tache")){
                QDomNodeList childrensTache = tache.childNodes();

                QDomNamedNodeMap attributes = tache.attributes();
                for(int i = 0; attributes.length(); i++)
                {
                    qDebug()<<"attribute = "<<attributes.item(i).nodeName();
                }
                QString type = attributes.namedItem("type").toElement().text();

                qDebug()<<"type = "<<type<<"\n";
                int etat = attributes.namedItem("etat").toElement().text().toInt();
                qDebug()<<"etat = "<<etat<<"\n";

                QString identifiant;
                QString titre;
                QDate dispoTache;
                QDate echeanceTache;
                QTime duree;
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
                        TacheManager& tm = TacheManager::getInstance();
                        Tache& t = dynamic_cast<Tache&>(tm.creerTacheUnitaire(identifiant, titre, dispoTache, echeanceTache, duree, etat));
                        p.ajouterTache(t);
                    }
                }
            }
        }
    }

    fin.close();
//    // QXmlStreamReader takes any QIODevice.
//    QXmlStreamReader xml(&fin);
//    qDebug()<<"debut fichier\n";
//    // We'll parse the XML until we reach end of it.
//    while(!xml.atEnd() && !xml.hasError()) {
//        // Read next element.
//        QXmlStreamReader::TokenType token = xml.readNext();
//        // If token is just StartDocument, we'll go to next.
//        if(token == QXmlStreamReader::StartDocument) continue;
//        qDebug()<<"StartDocument\n";
//        // If token is StartElement, we'll see if we can read it.
//        if(token == QXmlStreamReader::StartElement) {
//            // If it's named projets, we'll go to the next.
//            if(xml.name() == "projets") continue;
//            // If it's named projet, we'll dig the information from there.
//            if(xml.name() == "projet") {
//                qDebug()<<"new projet";
//                QString nom;
//                QString desc;
//                QDate disponibilite;
//                QDate echeance;

//                QXmlStreamAttributes attributes = xml.attributes();
//                /* Let's check that Task has attribute. */

//                xml.readNext();
//                //We're going to loop over the things because the order might change.
//                //We'll continue the loop until we hit an EndElement named projet.

//                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
//                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
//                        // We've found nom.
//                        if(xml.name() == "nom") {
//                            xml.readNext(); nom=xml.text().toString();
//                            qDebug()<<"id="<<nom;
//                        }

//                        // We've found description.
//                        if(xml.name() == "description") {
//                            xml.readNext(); desc=xml.text().toString();
//                            qDebug()<<"desc="<<desc;
//                        }
//                        // We've found disponibilite
//                        if(xml.name() == "disponibilite") {
//                            xml.readNext();
//                            qDebug()<<"date = "<<xml.text().toString();
//                            disponibilite=QDate::fromString(xml.text().toString(),Qt::TextDate);
//                            qDebug()<<"disp="<<disponibilite.toString("d MMM yyyy");
//                        }
//                        // We've found echeance
//                        if(xml.name() == "echeance") {
//                            xml.readNext();
//                            echeance=QDate::fromString(xml.text().toString(),Qt::TextDate);
//                            qDebug()<<"echeance="<<echeance.toString();
//                        }

//                        Projet& p=ajouterProjet(nom,desc,disponibilite);

//                        if(xml.name() == "taches"){
//                            qDebug()<<"<taches>\n";
//                        }

//                        if(xml.name() == "tache"){
//                            qDebug()<<"new tache\n";
//                            QString type;
//                            QString identifiant;
//                            QString titre;
//                            QDate dispoTache;
//                            QDate echeanceTache;
//                            QTime duree;
//                            int etat;

//                            QXmlStreamAttributes attributes = xml.attributes();
//                            /* Let's check that Task has attribute. */
//                            if(attributes.hasAttribute("type")) {
//                                type=attributes.value("type").toString();
//                            }
//                            if(attributes.hasAttribute("etat")) {
//                                etat=attributes.value("etat").toInt();
//                            }


//                            xml.readNext();
//                            //We're going to loop over the things because the order might change.
//                            //We'll continue the loop until we hit an EndElement named projet.

//                            while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
//                                qDebug()<<"boucle tache\n";
//                                if(xml.tokenType() == QXmlStreamReader::StartElement) {
//                                    // We've found identifiant.
//                                    if(xml.name() == "identifiant") {
//                                        xml.readNext(); identifiant=xml.text().toString();
//                                        qDebug()<<"id="<<identifiant;
//                                    }

//                                    // We've found titre.
//                                    if(xml.name() == "titre") {
//                                        xml.readNext(); titre=xml.text().toString();
//                                        qDebug()<<"titre="<<titre;
//                                    }
//                                    // We've found disponibilite
//                                    if(xml.name() == "disponibilite") {
//                                        xml.readNext();
//                                        qDebug()<<"date = "<<xml.text().toString();
//                                        dispoTache=QDate::fromString(xml.text().toString(),Qt::TextDate);
//                                        qDebug()<<"dispotache="<<dispoTache.toString("d MMM yyyy");
//                                    }
//                                    // We've found echeance
//                                    if(xml.name() == "echeance") {
//                                        xml.readNext();
//                                        echeanceTache=QDate::fromString(xml.text().toString(),Qt::TextDate);
//                                        qDebug()<<"echeance="<<echeanceTache.toString();
//                                    }

//                                    if(xml.name() == "duree") {
//                                        QXmlStreamAttributes attributes = xml.attributes();
//                                        /* Let's check that duree has attribute. */
//                                        if(attributes.hasAttribute("heure") && attributes.hasAttribute("minute")) {
//                                            int heures =attributes.value("heure").toInt();
//                                            int minutes = attributes.value("minute").toInt();
//                                            QTime tmp(heures, minutes);
//                                            duree = tmp;
//                                            qDebug()<<"duree ="<<duree.hour()<<"h"<<duree.minute()<<"\n";
//                                        }

//                                        xml.readNext();
//                                    }
//                                }
//                                // ...and next...
//                                xml.readNext();
//                            }
//                            TacheManager& tm = TacheManager::getInstance();
//                            if(type=="unitaire")
//                            {
//                                Tache& t = dynamic_cast<Tache&>(tm.creerTacheUnitaire(identifiant, titre, dispoTache,echeanceTache,duree, etat));
//                                p.ajouterTache(t);
//                            }
//                        }
//                    }
//                    // ...and next...
//                    xml.readNext();
//                }
//            }
//        }

//    }
//    qDebug()<<"fin load projetmanager";
//    // Error handling.
//    if(xml.hasError()) {
//        throw CalendarException("Erreur lecteur fichier projets, parser xml");
//    }
//    // Removes any device() or data from the reader * and resets its internal state to the initial state.
//    xml.clear();
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

