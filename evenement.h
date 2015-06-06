#ifndef EVENEMENT_H
#define EVENEMENT_H

/*!
 * \file Evenement.h
 * \brief Fichier gerant les evenements diverses presents dans l'agenda
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDate>
#include <QTime>

/*! \class Evenement
   * \brief classe representant les evenements.
   *
   *  La classe gere la creation d'evenements diverses et que l'on pourrait avoir a l'interieur de notre agenda.
   *  Cela pourrait etre aussi bien une seance de sport, un rdv ou autre.
   *  Il faut juste que ce soit qquechose de different d'une tache.
   */

class Evenement
{
    QDate date;/*!< Date de l'evenement*/
    QString description;/*!< Description de l'evenement*/
public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe Evenement
         *
         *  \param d : on renseigne la date de l'evenement obligatoirement
         *  \param desc : on renseigne la description de l'evenement.
         */
    Evenement(const QDate& d, const QString& desc):date(d), description(desc){}

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Evenement
         */
    virtual ~Evenement();

    /*!
         *  \brief getDate
         *
         *  Accesseur en lecture la date d'un evenement precis
         */
    const QDate& getDate() const { return date; }

    /*!
         *  \brief getTime
         *
         *  Accesseur en lecture de la description d'un evenement precis
         */
    const QString& getTime() const { return description; }
};

#endif // EVENEMENT_H
