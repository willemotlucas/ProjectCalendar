#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>

#include "tacheunitaire.h"
#include "global.h"

void TacheUnitaire::write(const QString& projet) const {
    qDebug()<<"start write tache unitaire\n";

    QDomDocument* dom = new QDomDocument("projets");
    QFile newfile(fileXML);

    if (!newfile.open(QIODevice::ReadWrite | QIODevice::Text))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    if(!dom->setContent(&newfile))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture objet dom"));

    QDomElement dom_element = dom->documentElement();

    //=============================================================
    //On crée le noeud <tache> que l'on veut ajouter et tous ses éléments
    QDomElement tache = dom->createElement("tache");

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

    //On ajoute au noeau tache tous ses elements
    tache.appendChild(idTache);
    tache.appendChild(titreTache);
    tache.appendChild(dispoTache);
    tache.appendChild(echeanceTache);
    //=============================================================
    QDomElement projectNode = dom_element.firstChildElement("projet");
    QDomElement child = projectNode.firstChild().toElement();
    qDebug()<<"projectNode  = "<<projectNode.nodeName()<<"\n";
    qDebug()<<"projectNode firstChild name = "<<child.nodeName()<<"\n";
    qDebug()<<"projectNode firstChild value = "<<child.nodeValue()<<"\n";
    projectNode = projectNode.nextSiblingElement("projet");
    qDebug()<<"projectNode value2 = "<<projectNode.firstChild().nodeValue()<<"\n";

//    while(projectNode.nodeValue() != projet){
//        qDebug()<<"4\n";
//        projectNode = dom_element.nextSiblingElement("projet");
//    }

    QDomElement node = projectNode.firstChildElement("taches");
    qDebug()<<"node = "<<node.nodeName()<<"\n";

    //Si des taches sont déjà existantes au projet, on rajoute la nouvelle tache à la fin
    if(node.nodeName() == "taches"){
        //On ajoute la tache au noeud <taches>
        node.appendChild(tache);
    }
    //S'il n'y a pas de noeud <taches>
    else if(node.nodeName() == "nom"){
        //on doit le créer pour ajouter la nouvelle tache et les taches futures
        QDomElement taches = dom->createElement("taches");
        taches.appendChild(tache);
        projectNode.appendChild(taches);
    }

    QString write_doc = dom->toString();
    QTextStream stream(&newfile);
    stream<<write_doc;
    newfile.close();




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

