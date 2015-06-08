#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include <vector>
#include "tache.h"

class TacheComposite : public Tache
{
    typedef std::vector<Tache*> contTache;
    contTache soustaches;

    //Seule la méthode ajouterSousTache aura accès à setDateEcheance. A chaque ajout d'une nouvelle tache, on regarde si la date d'echeance de cette nouvelle tache
    //est supérieur à la date d'echeance actuelle de la tache composite. L'utilisateur ne doit pas pouvoir changer la date d'echeance lui même.
    void setDateEcheance(const QDate& e);

    friend class TacheFactory;
    TacheComposite(const QString& id, const QString& t, const QDate& dispo):Tache(id, t, dispo){}
    TacheComposite(const TacheComposite& t);
    const TacheComposite& operator=(const TacheComposite& t);
    void write(const QString& type, const QString& id) const{}

public:
    //La destruction d'une tache composite entraîne la destruction de ses sous-tâches
    ~TacheComposite(){ soustaches.clear(); }

    bool isCommencee() const;
    bool isTerminee() const;

    //SOUSTACHE METHODS
    void ajouterSousTache(Tache& tache);
    void supprimerSousTache(const Tache& tache);
    bool trouverTache(const Tache& tache);
};

#endif // TACHECOMPOSITE_H
