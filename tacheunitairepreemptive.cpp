#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>

#include "tacheunitairepreemptive.h"
#include "global.h"

QDomElement& TacheUnitairePreemptive::write(QDomDocument* dom){
    //On crée le noeud <tache> que l'on veut ajouter et tous ses éléments
    QDomElement* tache = new QDomElement(dom->createElement("tache"));
    tache->setAttribute("type", "preemtive");
    tache->setAttribute("etat", (int)this->getEtat());

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
    tache->appendChild(idTache);
    tache->appendChild(titreTache);
    tache->appendChild(dispoTache);
    tache->appendChild(echeanceTache);
    tache->appendChild(dureeTacheInit);
    tache->appendChild(dureeTacheRestante);

    return *tache;
}

QTreeWidgetItem& TacheUnitairePreemptive::chargerTreeTache(QTreeWidget* tree){
    QTreeWidgetItem* tache = new QTreeWidgetItem();
    tache->setText(0,this->getId());
    if(this->getEtat()==1)
        tache->setTextColor(0,Qt::green);
    if(this->getEtat() == 0)
        tache->setTextColor(0,Qt::blue);
    return *tache;
}



