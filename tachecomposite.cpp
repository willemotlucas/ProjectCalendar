#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>
#include <QMetaEnum>
#include <typeinfo>

#include "tachecomposite.h"
#include "global.h"
#include "tache.h"

void TacheComposite::ajouterSousTaches(Tache& tache){
   qDebug()<<trouverTache(tache);
    if(!(trouverTache(tache))){
        soustaches.push_back(&tache);
        if(tache.getDateEcheance() > echeance){
            setDateEcheance(tache.getDateEcheance());
        }
    }
    else
        throw CalendarException("La tache " + tache.getId() + " existe deja.");
}

void TacheComposite::supprimerSousTache(const Tache &tache){
    int i = 0;
    for(std::vector<Tache*>::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        if((*it)->getId() == tache.getId())
            soustaches.erase(soustaches.begin()+i);
        i++;
    }
}

bool TacheComposite::trouverTache(const Tache& tache){
    for(std::vector<Tache*>::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        qDebug()<<"id tache ajoutée:"<<tache.getId();
        qDebug()<<"id tache parcourue:"<<(*it)->getId();
        if((*it)->getId() == tache.getId())
            return true;
    }
    return false;
}

Tache* TacheComposite::getSousTache(const QString& tache){
    for(std::vector<Tache*>::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        if((*it)->getId() == tache)
            return (*it);
    }
    return NULL;
}

QDomElement& TacheComposite::write(QDomDocument* dom) {

    //On crée le noeud <tache> que l'on veut ajouter et tous ses éléments
    QDomElement* tache = new QDomElement(dom->createElement("tache"));
    tache->setAttribute("type", "composite");

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
    for(std::vector<Tache*>::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
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


QTreeWidgetItem& TacheComposite::chargerTreeTache(QTreeWidget* tree){
    QTreeWidgetItem* tache = new QTreeWidgetItem();
    tache->setText(0,this->getId());

    for(std::vector<Tache*>::const_iterator it = soustaches.begin(); it != soustaches.end(); ++it){
        QTreeWidgetItem& sousTache = (*it)->chargerTree(tree);
        tache->addChild(&sousTache);
    }
    return *tache;
}
