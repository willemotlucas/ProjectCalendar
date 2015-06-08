#include "tachecomposite.h"

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
