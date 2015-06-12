#ifndef TACHECOMPOSITE_H
#define TACHECOMPOSITE_H

/*!
 * \file TacheComposite.h
 * \brief Fichier portant sur les taches composites
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <vector>
#include "tache.h"
#include <QTreeWidget>


/*! \class TacheComposite
   * \brief classe representant les taches composites
   *
   *  La classe gere la creation de toutes les taches composites de l' utilisateur.
   *  Une tache composite est une tache pouvant contenir plusieurs sous-taches
   *  de nature divers ( unitaire, preemptive, ou meme composite).
   */
class TacheComposite : public Tache
{
    //typedef std::vector<Tache*> contSousTache;
    std::vector<Tache*> soustaches;/*!< Vector des soustaches de la tache composite*/

    //Seule la méthode ajouterSousTache aura accès à setDateEcheance. A chaque ajout d'une nouvelle tache, on regarde si la date d'echeance de cette nouvelle tache
    //est supérieur à la date d'echeance actuelle de la tache composite. L'utilisateur ne doit pas pouvoir changer la date d'echeance lui même.
    /*!
         *  \brief setDateEcheance
         *
         *  Accesseur en ecriture de la date d'Echeance de la Tache
         *
         *  \param e : nouvelle date d'Echeance
         */
    void setDateEcheance(const QDate& e){echeance=e;}

    friend class TacheFactory;
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe TacheComposite
         *
         *  \param id : identificateur de la Tache
         *  \param t : titre de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param e : etat de la Tache
         */
    TacheComposite(const QString& id, const QString& t, const QDate& dispo):Tache(id, t, dispo,2){echeance=dispo;}


    /*!
         *  \brief Constructeur de recopie
         *
         *  Contructeur de recopie de la classe TacheComposite
         *
         *  \param t : tache que l'on veut recopier
         */
    TacheComposite(const TacheComposite& t);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe TacheComposite
         *
         *  \param t : tache que l'on veut recopier
         */
    const TacheComposite& operator=(const TacheComposite& t);

    /*!
         *  \brief write
         *
         *  Ecriture de la tache a l'interieur de notre arborescence
         *
         *  \param dom : arborescence de notre fichier XML
         */
    QDomElement& write(QDomDocument* dom);

    /*!
         *  \brief chargerTreeTache
         *
         *  Chargement de la tache a l'interieur de notre arborescence TreeWidget
         *
         *  \param tree : arborescence de notre treeview
         */
    QTreeWidgetItem& chargerTreeTache();
    void setEtat(unsigned int e){}
    unsigned int getEtat() const{return (unsigned int)etat;}


public:
    //La destruction d'une tache composite entraîne la destruction de ses sous-tâches

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Tache
         */
    virtual ~TacheComposite(){ soustaches.clear(); }

    //SOUSTACHE METHODS

    /*!
         *  \brief ajouterSousTaches
         *
         *  Fonction permettant d'ajouter une sous-tache a notre tache composite
         *
         *  \param tache : tache a ajouter au vector
         */
    void ajouterSousTaches(Tache& tache);

    /*!
         *  \brief supprimerSousTache
         *
         *  Fonction permettant de supprimer une sous-tache dans le vector
         *
         *  \param tache : tache a supprimer au projet
         */
    void supprimerSousTache(const Tache& tache);

    /*!
         *  \brief trouverTache
         *
         *  Renvoie un booleen vrai si on possede la tache dans le vector
         *  de sous-taches
         *
         *  \param tache : la tache a retrouver
         */
    bool trouverTache(const Tache& tache);

    /*!
         *  \brief getSousTache
         *
         *  Renvoie un pointeur sur la sous-tache
         *  possedant le titre demande
         *
         *  \param tache : titre de la sous-tache a retrouver
         */
    Tache* getSousTache(const QString& tache);
};

#endif // TACHECOMPOSITE_H
