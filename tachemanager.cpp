#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include "tachemanager.h"
#include "tacheunitaire.h"
#include "tacheunitairepreemptive.h"
#include "projet.h"
#include "global.h"

TacheManager::TacheManager():taches(0){}

void TacheManager::addItem(Tache* t){
    taches.push_back(t);
}

Tache* TacheManager::trouverTache(const QString& id)const{
    for(unsigned int i=0; i<taches.size(); i++)
        if (id==taches[i]->getId()) return taches[i];
    return 0;
}

/*Tache& TacheManager::ajouterTache(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline){
//    if (trouverTache(id)) throw CalendarException("erreur, TacheManager, tache deja existante");
//    Tache* newt=new Tache(id,t,dispo,deadline);
//    addItem(newt);
//    return *newt;
}*/

Tache& TacheManager::creerTacheUnitaire(const QString &id, const QString &desc, const QDate &dispo, const QDate &echeance, const QTime &duree, const int& etat){
    Tache* t = new TacheUnitaire(id,desc,dispo,echeance,duree, etat);
    return *t;
}

Tache& TacheManager::creerTacheUnitairePreemptive(const QString &id, const QString &desc, const QDate &dispo, const QDate &echeance, const QTime &duree, const int& etat){
    Tache* t = new TacheUnitairePreemptive(id,desc,dispo,echeance,duree, etat);
    return *t;
}

Tache& TacheManager::getTache(const QString& id){
    Tache* t=trouverTache(id);
    if (!t) throw CalendarException("erreur, TacheManager, tache inexistante");
    return *t;
}

const Tache& TacheManager::getTache(const QString& id)const{
    return const_cast<TacheManager*>(this)->getTache(id);
}

TacheManager::~TacheManager(){
    //if (file!="") save(file);
//    taches.clear();
//    file="";
}

void TacheManager::load(const QString& f){
    //qDebug()<<"debut load\n";
    //this->~TacheManager();
    taches.clear();
//    delete[] taches;
    file=f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier tâches");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "taches") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "tache") {
                qDebug()<<"new tache\n";
                QString identificateur;
                QString titre;
                QDate disponibilite;
                QDate echeance;
                Duree duree;
                bool preemptive;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */
                if(attributes.hasAttribute("preemptive")) {
                    QString val =attributes.value("preemptive").toString();
                    preemptive=(val == "true" ? true : false);
                }
                //qDebug()<<"preemptive="<<preemptive<<"\n";

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named tache.


                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "identificateur") {
                            xml.readNext(); identificateur=xml.text().toString();
                            //qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            //qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found disponibilite
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            disponibilite=QDate::fromString(xml.text().toString(),Qt::TextDate);
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=QDate::fromString(xml.text().toString(),Qt::TextDate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                        // We've found duree
                        if(xml.name() == "duree") {
                            xml.readNext();
                            duree.setDuree(xml.text().toString().toUInt());
                            //qDebug()<<"duree="<<duree.getDureeEnMinutes()<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                //qDebug()<<"ajout tache "<<identificateur<<"\n";
                //ajouterTache(identificateur,titre,disponibilite,echeance);

            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier taches, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void  TacheManager::save(const QString& projet, const Tache& t){
    t.save(projet);
}


TacheManager::Handler TacheManager::handler=TacheManager::Handler();

TacheManager& TacheManager::getInstance(){
    if (handler.instance==0) handler.instance=new TacheManager;
    return *(handler.instance);
}

void TacheManager::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}
