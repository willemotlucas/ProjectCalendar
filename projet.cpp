#include "projet.h"
#include <QDebug>

void Projet::ajouterTache(Tache& t){
    if (trouverTache(t.getId())) throw CalendarException("La tache " + t.getId() + " existe déjà. Veuillez modifier son identificateur.");
    taches.push_back(&t);
}

Tache* Projet::trouverTache(const QString& id)const{
    for(unsigned int i=0; i<taches.size(); i++)
        if (id==taches[i]->getId()) return taches[i];
    return 0;
}

//Tache& Projet::getTache(const QString& id){
//    Tache* t=trouverTache(id);
//    if (!t) throw CalendarException("La tache " + id + " est inexistante.");
//    return *t;
//}

//const Tache& Projet::getTache(const QString& id)const{
//    return const_cast<Projet*>(this)->getTache(id);
//}

Tache* Projet::getTache(const QString &id){
    Tache* t=trouverTache(id);
    if(!t) throw CalendarException("La tache " + id + " est inexistante.");
    return t;
}

