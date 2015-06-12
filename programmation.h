#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

/*!
 * \file Programmation.h
 * \brief Programmation des taches dans l'agenda
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */


#include <QDate>
#include <QTime>

#include "calendarexception.h"
#include "tache.h"
#include "projet.h"

/*! \class Programmation
   * \brief Classe permettant la programmation des taches dans l'agenda
   *
   *  La classe permet de programmer une tache dans l'agenda
   *  avec une date et un horaire precis.
   */
class Programmation {
    const Projet* projet;/*!< Pointeur sur le projet dont la tache correpond*/
    const Tache* tache;/*!< Pointeur sur la tache a programmer*/
    QDate date;/*!< Date de la programmation*/
    QTime horaire;/*!< Horaire de la programmation*/
    QTime duree;/*!< Duree de la programmation*/
public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Programmation
         *
         *  \param t : pointeur de la tache a programmer
         *  \param d : date de programmation de la tache
         *  \param h : horaire de programmation de la tache
         */
    Programmation(const Projet& p, const Tache& t, const QDate& d, const QTime& h, const QTime& dur):projet(&p), tache(&t), date(d), horaire(h), duree(dur){}

    /*!
         *  \brief getTache
         *
         *  Accesseur en lecture de la Tache
         */
    const Tache& getTache() const { return *tache; }

    /*!
         *  \brief getProjet
         *
         *  Accesseur en lecture du Projet
         */
    const Projet& getProjet() const { return *projet; }

    /*!
         *  \brief getDate
         *
         *  Accesseur en lecture de la Date
         */
    QDate getDate() const { return date; }

    /*!
         *  \brief getHoraire
         *
         *  Accesseur en lecture de l'Horaire
         */
    QTime getHoraire() const { return horaire; }

    /*!
         *  \brief getDuree
         *
         *  Accesseur en lecture de la duree
         */
    QTime getDuree() const { return duree; }

    ~Programmation(){}


};

#endif // PROGRAMMATION_H
