#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>
#include <QMetaEnum>

#include "tacheunitaire.h"
#include "global.h"

void TacheUnitaire::write(const QString& type, const QString& id) const {
    QDomDocument* dom = new QDomDocument("projets");
    QFile newfile(fileXML);

    if (!newfile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    if(!dom->setContent(&newfile))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture objet dom"));
    newfile.close();

    QDomElement dom_element = dom->documentElement();

    //=============================================================
    //On crée le noeud <tache> que l'on veut ajouter et tous ses éléments
    QDomElement tache = dom->createElement("tache");
    tache.setAttribute("type", "unitaire");
    qDebug()<<"etat"<<this->getEtat();
    tache.setAttribute("etat", (int)this->getEtat());

    QDomElement idTache = dom->createElement("identifiant");
    QDomText idTacheText = dom->createTextNode(this->getId());
    idTache.appendChild(idTacheText);

    QDomElement titreTache = dom->createElement("titre");
    QDomText titreTacheText = dom->createTextNode(this->titre);
    titreTache.appendChild(titreTacheText);

    QDomElement dispoTache = dom->createElement("disponibilite");
    QDomText dispoTacheText = dom->createTextNode(this->getDateDisponibilite().toString(Qt::TextDate));
    dispoTache.appendChild(dispoTacheText);

    QDomElement echeanceTache = dom->createElement("echeance");
    QDomText echeanceTacheText = dom->createTextNode(this->getDateEcheance().toString(Qt::TextDate));
    echeanceTache.appendChild(echeanceTacheText);

    QDomElement dureeTache = dom->createElement("duree");
    dureeTache.setAttribute("heure", QString::number(this->getDuree().hour()));
    dureeTache.setAttribute("minute", QString::number(this->getDuree().minute()));

    //On ajoute au noeau tache tous ses elements
    tache.appendChild(idTache);
    tache.appendChild(titreTache);
    tache.appendChild(dispoTache);
    tache.appendChild(echeanceTache);
    tache.appendChild(dureeTache);
    //=============================================================
    //
    QDomElement projectNode = dom_element.firstChildElement(type);
    QDomElement projectName = projectNode.firstChild().toElement();

    while(projectName.text() != id){
        projectNode = projectNode.nextSiblingElement(type);
        projectName = projectNode.firstChild().toElement();
    }

    if(type == "tache")
    {
        QDomElement node = projectNode.firstChildElement("soustaches");
        node.appendChild(tache);
    }
    else if(type == "projet")
    {
        QDomElement node = projectNode.firstChildElement("taches");
        node.appendChild(tache);
    }

    QFile fichier(fileXML);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fichier.close();
        throw new CalendarException(QString("Erreur lors de l'ouverture du fichier XML pour écriture."));
    }

    QString write_doc = dom->toString();
    QTextStream stream(&fichier);
    stream<<write_doc;
    fichier.close();




    /*QXmlStreamWriter stream(&newfile);
    QXmlStreamReader xml(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    while(!xml.atEnd() && !xml.hasError()) {
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;

        if(token == QXmlStreamReader::StartElement) {
            qDebug()<<"Element : "<<xml.name().toString();

            //Si on est sur la balise projets, on continue pour atteindre le premier projet
            if(xml.name() == "projets") continue;

            //Une fois sur la balise projet
            if(xml.name() == "projet") {
                //On regarde si on est sur le bon projet
                xml.readNext();
                if(xml.text() == projet){
                    qDebug()<<"Projet : "<<xml.text();
                    //on cherche à atteindre la balise <taches> pour ajouter la nouvelle tache
                    while(xml.name() != "taches" && xml.tokenType() == QXmlStreamReader::StartElement){
                        qDebug()<<"boucle. xml.name() = "<<xml.name().toString()<<"\n";
                        //On est sur la balise </projet>, la balise <taches> n'a pas encore été trouvée, il faut la crééer
                        if(xml.name() == "projet" && xml.tokenType() == QXmlStreamReader::EndElement) break;
                        else xml.readNext();
                    }
                    if(xml.name() == "projet" && xml.tokenType() == QXmlStreamReader::EndElement){
                        //Si pas de balises <taches> dans le projet, il faut en créer une et ajouter toutes les taches du projet
                        //Sauf celle déjà ajoutées
                            stream.writeStartElement("taches");
                            stream.writeStartElement("tache");
                            stream.writeTextElement("identificateur",this->getId());
                            stream.writeTextElement("titre",this->getTitre());
                            stream.writeTextElement("disponibilite",this->getDateDisponibilite().toString(Qt::TextDate));
                            stream.writeTextElement("echeance",this->getDateEcheance().toString(Qt::TextDate));
                            stream.writeEndElement();
                            stream.writeEndElement();
                    }
                }
                //Sinon on commence l'itération suivante pour trouver le bon projet
                else continue;



            }
        }
    }*/
//    stream.writeEndDocument();
//    newfile.close();
}

