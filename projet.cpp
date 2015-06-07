#include "projet.h"

void Projet::ajouterTache(const Tache &t){
    taches.push_back(t);
}

Tache* Projet::trouverTache(const QString& id)const{
    for(unsigned int i=0; i<taches.size(); i++)
        if (id==taches[i]->getId()) return taches[i];
    return 0;
}

Tache& Projet::getTache(const QString& id){
    Tache* t=trouverTache(id);
    if (!t) throw CalendarException("erreur, Projet, tache inexistante");
    return *t;
}

const Tache& Projet::getTache(const QString& id)const{
    return const_cast<Projet*>(this)->getTache(id);
}

