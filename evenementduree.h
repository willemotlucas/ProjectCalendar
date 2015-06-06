#ifndef EVENEMENTDUREE_H
#define EVENEMENTDUREE_H

/*!
 * \file EvenementDuree.h
 * \brief Evenement ayant une duree et un horaire
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDate>
#include <QTime>
#include "duree.h"
#include "evenement.h"

/*! \class EvenementDuree
   * \brief classe representant un evenement special
   *
   *  La classe EvenementDuree est une classe ayant une duree
   *  specifiee ainsi qu'un horaire.
   */

class EvenementDuree : public Evenement
{
    QTime horaire;/*!< Horaire de l'evenement*/
    Duree duree;/*!< Duree de l'evenement*/
public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe EvenementDuree
         *
         *  \param d : Date de l'evenement
         *  \param desc : Description de l'evenement
         *  \param h : Horaire de l'evenement
         *  \param dur : Duree de l'evenement
         */
    EvenementDuree(const QDate& d, const QString desc, const QTime& h, const Duree& dur):Evenement(d,desc),horaire(h), duree(dur){}

    /*!
         *  \brief getHoraire
         *
         *  Accesseur en lecture de l'horaire de l'evenement
         */
    const QTime& getHoraire() const { return horaire; }

    /*!
         *  \brief getDuree
         *
         *  Accesseur en lecture de la durée de l'evenement
         */
    const Duree& getDuree() const { return duree; }

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe EvenementDuree
         */
    virtual ~EvenementDuree();
};

#endif // EVENEMENTDUREE_H
