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
<<<<<<< HEAD
public:
    typedef std::vector<Tache*> contTache;
    ~Projet();
    const QString& getNom() const { return nom; }
    const QString& getDescription() const { return description; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }

    void ajouterTache(const Tache& t);

    contTache::iterator begin(){return taches.begin();}
    contTache::iterator end(){return taches.end();}

private:
    /**
     * @brief nom
     * nom du projet
     */
    QString nom;
    /**
     * @brief description
     * description du projet
     */
    QString description;
    /**
     * @brief disponibilite
     * date de disponibilite du projet
     */
    QDate disponibilite;
    /**
     * @brief echeance
     * date d'échéance du projet
     */
    QDate echeance;

    //+Liste des taches du projet
    contTache taches;
=======
    friend class ProjetManager;
    QString nom;/*!< Nom du projet*/
    QString description;/*!< Description du projet*/
    QDate disponibilite;/*!< Date de disponibilite du projet*/
    QDate echeance;/*!< Date d'echeance du projet*/

    //+Liste des taches du projet
    std::vector<Tache*> taches;/*!< Vector des taches du projet*/
>>>>>>> 49d0b2809723ee167f5b8507b9834d9ad6f8cb87

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
         *  \brief setDateEcheance
         *
         *  Accesseur en ecriture de Date Echeance
         *
         *  \param d : date a modifer sur notre projet
         */
    void setDateEcheance(const QDate& d);
<<<<<<< HEAD
    friend class ProjetManager;
    Projet(const QString& n, const QString& desc, const QDate& disp):nom(n), description(desc), disponibilite(disp), echeance(QDate()){}


=======

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
>>>>>>> 49d0b2809723ee167f5b8507b9834d9ad6f8cb87
};

#endif // PROJET_H
