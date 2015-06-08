#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>

#include "tacheunitairepreemptive.h"
#include "global.h"

QDomNode& TacheUnitairePreemptive::write(const QString& type, const QString &id,QDomDocument* dom){
//    qDebug()<<"start write tache preemtive\n";

//    QDomDocument* dom = new QDomDocument("projets");
//    QFile newfile(fileXML);

//    if (!newfile.open(QIODevice::ReadOnly | QIODevice::Text))
//        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
//    if(!dom->setContent(&newfile))
//        throw CalendarException(QString("erreur sauvegarde tâches : ouverture objet dom"));
//    newfile.close();

//    QDomElement dom_element = dom->documentElement();

//    //=============================================================
    //On crée le noeud <tache> que l'on veut ajouter et tous ses éléments
    QDomElement tache = dom->createElement("tache");
    tache.setAttribute("type", "preemtive");
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

    QDomElement dureeTacheInit = dom->createElement("dureeInitiale");
    dureeTacheInit.setAttribute("heure", QString::number(this->getDureeInit().hour()));
    dureeTacheInit.setAttribute("minute", QString::number(this->getDureeInit().minute()));

    QDomElement dureeTacheRestante = dom->createElement("dureeRestante");
    dureeTacheRestante.setAttribute("heure", QString::number(this->getDureeRestante().hour()));
    dureeTacheRestante.setAttribute("minute", QString::number(this->getDureeRestante().minute()));

    //On ajoute au noeau tache tous ses elements
    tache.appendChild(idTache);
    tache.appendChild(titreTache);
    tache.appendChild(dispoTache);
    tache.appendChild(echeanceTache);
    tache.appendChild(dureeTacheInit);
    tache.appendChild(dureeTacheRestante);

    return tache;
}
//    //=============================================================
//    //
//    QDomElement projectNode = dom_element.firstChildElement(type);
//    QDomElement projectName = projectNode.firstChild().toElement();

//    while(projectName.text() != id){
//        projectNode = projectNode.nextSiblingElement(type);
//        projectName = projectNode.firstChild().toElement();
//    }

//    if(type == "projet")
//    {
//        QDomElement node = projectNode.firstChildElement("taches");
//        node.appendChild(tache);
//    }
//    else if(type == "tache")
//    {
//        QDomElement node = projectNode.firstChildElement("soustaches");
//        node.appendChild(tache);
//    }
//    QDomElement node = projectNode.firstChildElement("taches");

//    QFile fichier(fileXML);
//    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
//    {
//        fichier.close();
//        throw new CalendarException(QString("Erreur lors de l'ouverture du fichier XML pour écriture."));
//    }

//    QString write_doc = dom->toString();
//    QTextStream stream(&fichier);
//    stream<<write_doc;
//    fichier.close();
    
//}


