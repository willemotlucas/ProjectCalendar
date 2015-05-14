#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>

#include "projetmanager.h"
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
        qDebug()<<"projet deja existant\n";
        throw CalendarException("Le projet " + nom + " existe déjà.");
    }
    if(nom.isEmpty()){
        throw CalendarException("Attention, le nom de projet ne peut pas être vide.");
    }
    qDebug()<<"dispo = "<<dispo.toString();
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
}


Projet* ProjetManager::trouverProjet(const QString& nom)const{
    qDebug()<<"size = "<<projets.size();
    for(unsigned int i=0; i<projets.size(); i++){
        if (nom==projets[i]->getNom()){
            return projets[i];
        }
    }
    return 0;
}

void ProjetManager::load(const QString& f){
    qDebug()<<"debut load\n";
    //this->~ProjetManager();
    //for(unsigned int i=0; i<nb; i++) delete projets[i];

    //Utilisation de la STL
    projets.clear();
    //delete[] projets;
    file=f;
    QFile fin(file);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw CalendarException("Erreur ouverture fichier projets");
    }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        qDebug()<<"StartDocument\n";
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named projets, we'll go to the next.
            if(xml.name() == "projets") continue;
            // If it's named projet, we'll dig the information from there.
            if(xml.name() == "projet") {
                qDebug()<<"new projet\n";
                QString nom;
                QString desc;
                QDate disponibilite;
                QDate echeance;

                QXmlStreamAttributes attributes = xml.attributes();
                /* Let's check that Task has attribute. */

                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named projet.

                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "projet")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found nom.
                        if(xml.name() == "nom") {
                            xml.readNext(); nom=xml.text().toString();
                            //qDebug()<<"id="<<nom<<"\n";
                        }

                        // We've found description.
                        if(xml.name() == "description") {
                            xml.readNext(); desc=xml.text().toString();
                            //qDebug()<<"desc="<<desc<<"\n";
                        }
                        // We've found disponibilite
                        if(xml.name() == "disponibilite") {
                            xml.readNext();
                            qDebug()<<"date5 = "<<xml.text().toString();
                            disponibilite=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"disp="<<disponibilite.toString()<<"\n";
                        }
                        // We've found echeance
                        if(xml.name() == "echeance") {
                            xml.readNext();
                            echeance=QDate::fromString(xml.text().toString(),Qt::ISODate);
                            //qDebug()<<"echeance="<<echeance.toString()<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                //qDebug()<<"ajout projet "<<identificateur<<"\n";
                ajouterProjet(nom,desc,disponibilite);

            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw CalendarException("Erreur lecteur fichier projets, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    //qDebug()<<"fin load\n";
}

void  ProjetManager::save(const QString& f){
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
        stream.writeTextElement("description",projets[i]->getDescription());
        qDebug()<<"save date = "<<projets[i]->getDisponibilite().toString(Qt::ISODate);
        stream.writeTextElement("disponibilite",projets[i]->getDisponibilite().toString(Qt::ISODate));
//        stream.writeTextElement("echeance",projets[i]->getDateEcheance().toString(Qt::ISODate));
        stream.writeEndElement();
    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}

