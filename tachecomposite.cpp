#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QDebug>
#include <QMetaEnum>

#include "tachecomposite.h"
#include "tachemanager.h"
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

QDomElement& TacheComposite::write(const QString& type, const QString& id,QDomDocument* dom) {}
//    QDomDocument* dom = new QDomDocument("projets");
//    QFile newfile(fileXML);

//    if (!newfile.open(QIODevice::ReadOnly | QIODevice::Text))
//        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
//    if(!dom->setContent(&newfile))
//        throw CalendarException(QString("erreur sauvegarde tâches : ouverture objet dom"));
//    newfile.close();

//    QDomElement dom_element = dom->documentElement();

//    //=============================================================
//    //On crée le noeud <tache> que l'on veut ajouter et tous ses éléments
//    QDomElement tache = dom->createElement("tache");
//    tache.setAttribute("type", "composite");
////    qDebug()<<"etat"<<this->getEtat();
////    tache.setAttribute("etat", (int)this->getEtat());

//    QDomElement idTache = dom->createElement("identifiant");
//    QDomText idTacheText = dom->createTextNode(this->getId());
//    idTache.appendChild(idTacheText);

//    QDomElement titreTache = dom->createElement("titre");
//    QDomText titreTacheText = dom->createTextNode(this->titre);
//    titreTache.appendChild(titreTacheText);

//    QDomElement dispoTache = dom->createElement("disponibilite");
//    QDomText dispoTacheText = dom->createTextNode(this->getDateDisponibilite().toString(Qt::TextDate));
//    dispoTache.appendChild(dispoTacheText);

//    QDomElement echeanceTache = dom->createElement("echeance");
//    QDomText echeanceTacheText = dom->createTextNode(this->getDateEcheance().toString(Qt::TextDate));
//    echeanceTache.appendChild(echeanceTacheText);

//    QDomElement sousTache = dom->createElement("soustaches") ;


//    //On ajoute au noeau tache tous ses elements
//    tache.appendChild(idTache);
//    tache.appendChild(titreTache);
//    tache.appendChild(dispoTache);
//    tache.appendChild(echeanceTache);
//    tache.appendChild(sousTache);
//    //=============================================================
//    //
//    QDomElement projectNode = dom_element.firstChildElement("projet");
//    QDomElement projectName = projectNode.firstChild().toElement();

//    while(projectName.text() != projet){
//        projectNode = projectNode.nextSiblingElement("projet");
//        projectName = projectNode.firstChild().toElement();
//    }

//    QDomElement node = projectNode.firstChildElement("taches");
//    //Si des taches sont déjà existantes au projet, on rajoute la nouvelle tache à la fin
//    if(node.nodeName() == "taches"){
//        //On ajoute la tache au noeud <taches>
//        node.appendChild(tache);
//    }
//    //S'il n'y a pas de noeud <taches>
//    else if(node.nodeName() == ""){
//        //on doit le créer pour ajouter la nouvelle tache et les taches futures
//        QDomElement taches = dom->createElement("taches");
//        taches.appendChild(tache);
//        projectNode.appendChild(taches);
//    }

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

