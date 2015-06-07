#ifndef PROJET_H
#define PROJET_H

/*!
 * \file projet.h
 * \brief Fichier portant sur les projets
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QString>
#include <QDate>
#include <vector>
#include "tache.h"

/*! \class Projet
   * \brief classe representant les projets.
   *
   *  La classe gere la creation de tous les projets de l' utilisateur.
   *  Un nouveau projet se compose obligatoirement d'un titre, d'une date de dispo
   *  et d'une description.
   */
class Projet
{
public:
    typedef std::vector<Tache*> contTache;
private:

    friend class ProjetManager;

    QString nom;/*!< Nom du projet*/
    QString description;/*!< Description du projet*/
    QDate disponibilite;/*!< Date de disponibilite du projet*/
    QDate echeance;/*!< Date d'echeance du projet*/

    //+Liste des taches du projet
    contTache taches;/*!< Vector des taches du projet*/

    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie de la classe Projet
         *
         *  \param p : projet que l'on veut recopier
         */
    Projet(const Projet& p);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe Projet
         *
         *  \param p : projet que l'on veut recopier
         */
    Projet& operator=(const Projet& p);

    //Appelé par la méthode ajouterTache seulement

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Projet
         *
         *  \param d : nom du projet
         *  \param desc : description du projet.
         *  \param disp : date de Disponibilite du projet
         *
         */
    Projet(const QString& n, const QString& desc, const QDate& disp):nom(n), description(desc), disponibilite(disp), echeance(QDate()){}

    Tache* trouverTache(const QString& id) const;
public:
    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Projet
         */
    ~Projet();

    /*!
         *  \brief getNom
         *
         *  Accesseur en lecture du nom du projet
         */
    const QString& getNom() const { return nom; }

    /*!
         *  \brief getDescription
         *
         *  Accesseur en lecture de la description du projet
         */
    const QString& getDescription() const { return description; }

    /*!
         *  \brief getDisponibilite
         *
         *  Accesseur en lecture de la date de Disponibilite du projet
         */
    const QDate& getDisponibilite() const { return disponibilite; }

    /*!
         *  \brief getDescription
         *
         *  Accesseur en lecture de la date d'Echeance du projet
         */
    const QDate& getEcheance() const { return echeance; }

    /*!
         *  \brief ajouterTache
         *
         *  Fonction permettant d'ajouter une tache au projet
         *
         *  \param t : tache a ajouter au projet
         */

    void ajouterTache(const Tache& t);
    Tache& getTache(const QString& id);
    bool isTacheExistante(const QString& id) const { return trouverTache(id)!=0; }
    const Tache& getTache(const QString& code) const;

    contTache::iterator begin(){return taches.begin();}
    contTache::iterator end(){return taches.end();}
};

#endif // PROJET_H
