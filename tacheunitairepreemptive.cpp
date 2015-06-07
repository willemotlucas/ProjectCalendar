#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>

#include "tacheunitairepreemptive.h"
#include "global.h"

void TacheUnitairePreemptive::write(const QString &projet) const{
    qDebug()<<"start write tache preemtive\n";

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

    QDomElement dureeTacheInit = dom->createElement("duree initiale");
    dureeTacheInit.setAttribute("heure", QString::number(this->getDuree().hour()));
    dureeTacheInit.setAttribute("minute", QString::number(this->getDuree().minute()));

    QDomElement dureeTacheRestante = dom->createElement("duree restante");
    dureeTacheRestante.setAttribute("heure", QString::number(this->getDuree().hour()));
    dureeTacheRestante.setAttribute("minute", QString::number(this->getDuree().minute()));

    //On ajoute au noeau tache tous ses elements
    tache.appendChild(idTache);
    tache.appendChild(titreTache);
    tache.appendChild(dispoTache);
    tache.appendChild(echeanceTache);
    tache.appendChild(dureeTacheInit);
    tache.appendChild(dureeTacheRestante);
    //=============================================================
    //
    QDomElement projectNode = dom_element.firstChildElement("projet");
    QDomElement projectName = projectNode.firstChild().toElement();

    while(projectName.text() != projet){
        projectNode = projectNode.nextSiblingElement("projet");
        projectName = projectNode.firstChild().toElement();
    }

    QDomElement node = projectNode.firstChildElement("taches");
    //Si des taches sont déjà existantes au projet, on rajoute la nouvelle tache à la fin
    if(node.nodeName() == "taches"){
        //On ajoute la tache au noeud <taches>
        node.appendChild(tache);
    }
    //S'il n'y a pas de noeud <taches>
    else if(node.nodeName() == ""){
        //on doit le créer pour ajouter la nouvelle tache et les taches futures
        QDomElement taches = dom->createElement("taches");
        taches.appendChild(tache);
        projectNode.appendChild(taches);
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
    
}


