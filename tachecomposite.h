#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include <vector>
#include "tache.h"

class TacheComposite : public Tache
{
    std::vector<Tache*> soustaches;

    //Seule la méthode ajouterSousTache aura accès à setDateEcheance. A chaque ajout d'une nouvelle tache, on regarde si la date d'echeance de cette nouvelle tache
    //est supérieur à la date d'echeance actuelle de la tache composite. L'utilisateur ne doit pas pouvoir changer la date d'echeance lui même.
    void setDateEcheance(const QDate& e);


public:
    TacheComposite(const QString& id, const QString& t, const QDate& dispo):Tache(id, t, dispo){}
    //La destruction d'une tache composite entraîne la destruction de ses sous-tâches
    ~TacheComposite(){ soustaches.clear(); }

    bool isCommencee() const;
    bool isTerminee() const;

    //SOUSTACHE METHODS
    void ajouterSousTache(const Tache& tache);
    void supprimerSousTache(const Tache& tache);
};

#endif // TACHECOMPOSITE_H