#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>
#include <QMetaEnum>

#include "tachecomposite.h"
#include "global.h"
#include "tache.h"

bool TacheComposite::isCommencee() const {
    //2 indirections, 1 pour l'itérator et 1 pour l'adresse
    for(contTache::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        if((*it)->isCommencee())
            return true;
    }
    return false;
}

bool TacheComposite::isTerminee() const {
    for(contTache::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        if(!(*it)->isTerminee())
            return false;
    }
    return true;
}

void TacheComposite::ajouterSousTache(Tache& tache){
    if(!trouverTache(tache)){
        soustaches.push_back(&tache);
        if(tache.getDateEcheance() > echeance)
            setDateEcheance(tache.getDateEcheance());
    }
}

void TacheComposite::supprimerSousTache(const Tache &tache){
    int i = 0;
    for(contTache::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        if((*it)->getId() == tache.getId())
            soustaches.erase(soustaches.begin()+i);
        i++;
    }
}

bool TacheComposite::trouverTache(const Tache& tache){
    for(contTache::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        if((*it)->getId() == tache.getId())
            return true;
    }
    return false;
}

QDomElement& TacheComposite::write(QDomDocument* dom) {

    //On crée le noeud <tache> que l'on veut ajouter et tous ses éléments
    QDomElement* tache = new QDomElement(dom->createElement("tache"));
    tache->setAttribute("type", "composite");
    qDebug()<<"etat preemtive"<<this->getId();

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

    QDomElement sousTache = dom->createElement("soustaches");
    for(contTache::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        QDomElement m = (*it)->save(dom);
        sousTache.appendChild(m);
    }


    //On ajoute au noeau tache tous ses elements
    tache->appendChild(idTache);
    tache->appendChild(titreTache);
    tache->appendChild(dispoTache);
    tache->appendChild(echeanceTache);
    tache->appendChild(sousTache);
    return *tache;
}
