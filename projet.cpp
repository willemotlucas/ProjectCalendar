#include "projet.h"
#include "tachecomposite.h"
#include <QDebug>
#include <algorithm>


void Projet::ajouterTache(Tache& t){
    if (trouverTache(t.getId())) throw CalendarException("La tache " + t.getId() + " existe déjà. Veuillez modifier son identificateur.");
    //Mise à jour de la date d'échéance du projet
    if(t.getDateEcheance() > this->echeance)
        this->echeance = t.getDateEcheance();
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

void Projet::supprimerTache(const Tache &tache){
    std::vector<Tache*>::iterator it = find(taches.begin(),taches.end(),&tache);
    if(it != taches.end()){
    taches.erase(it);
    }
}

std::vector<TacheComposite*> Projet::getTacheCompo()const{
    std::vector<TacheComposite*> tacheCompo;
    for(std::vector<Tache*>::const_iterator it = taches.begin(); it !=taches.end();++it){
        TacheComposite* tmp =dynamic_cast<TacheComposite*>(*it);
        if(tmp!=0)
            tacheCompo.push_back(tmp);
    }
    return tacheCompo;
}
