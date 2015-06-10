#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

#include <vector>
#include "tache.h"
#include <QTreeWidget>

class TacheComposite : public Tache
{
    //typedef std::vector<Tache*> contSousTache;
    std::vector<Tache*> soustaches;

    //Seule la méthode ajouterSousTache aura accès à setDateEcheance. A chaque ajout d'une nouvelle tache, on regarde si la date d'echeance de cette nouvelle tache
    //est supérieur à la date d'echeance actuelle de la tache composite. L'utilisateur ne doit pas pouvoir changer la date d'echeance lui même.
    void setDateEcheance(const QDate& e){echeance=e;}

    friend class TacheFactory;
    TacheComposite(const QString& id, const QString& t, const QDate& dispo, const int& e=2):Tache(id, t, dispo,e){echeance=dispo;}
    TacheComposite(const TacheComposite& t);
    const TacheComposite& operator=(const TacheComposite& t);
    QDomElement& write(QDomDocument* dom);
    QTreeWidgetItem& chargerTreeTache(QTreeWidget* tree);
    void setEtat(const int &e){}
    const int& getEtat() const{return (int)etat;}


public:
    //La destruction d'une tache composite entraîne la destruction de ses sous-tâches
    virtual ~TacheComposite(){ soustaches.clear(); }

    //SOUSTACHE METHODS
    void ajouterSousTaches(Tache& tache);
    void supprimerSousTache(const Tache& tache);
    bool trouverTache(const Tache& tache);
    Tache* getSousTache(const QString& tache);
};

#endif // TACHECOMPOSITE_H
