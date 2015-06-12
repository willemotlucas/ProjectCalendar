#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

/*!
 * \file TacheUnitaire.h
 * \brief Fichier portant sur les taches unitaires
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QTime>
#include "tache.h"

/*! \class TacheUnitaire
   * \brief classe representant les taches unitaires
   *
   *  La classe gere la creation de toutes les taches unitaires de l' utilisateur.
   *  Une tache unitaire est une tache ayant une durée inferieure a 12h.
   */
class TacheUnitaire : public Tache
{
private:
    // Etat de la tache prive ne lui appartient qu'a lui !

    friend class TacheFactory;
    static const int DUREE_MAX = 12;/*!< duree maximale d'une tache*/
    QTime duree;/*!< Duree de la Tache*/

    /*!
         *  \brief write
         *
         *  Ecriture de la tache a l'interieur de notre arborescence
         *
         *  \param dom : arborescence de notre fichier XML
         */
    virtual QDomElement& write(QDomDocument* dom);

    /*!
         *  \brief chargerTreeTache
         *
         *  Chargement de la tache a l'interieur de notre arborescence TreeWidget
         */
    virtual QTreeWidgetItem& chargerTreeTache();

    TacheUnitaire(const TacheUnitaire& t);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe TacheUnitaire
         *
         *  \param t : tache que l'on veut recopier
         */
    const TacheUnitaire& operator=(const TacheUnitaire& f);

protected :
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe TacheUnitaire
         *
         *  \param id : identificateur de la Tache
         *  \param desc : description de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param deadline : echeance de la Tache
         *  \param dur : duree de la Tache
         *  \param e : etat de la Tache
         */
            TacheUnitaire(const QString& id, const QString& desc, const QDate& dispo, const QDate& deadline, const QTime& dur, unsigned int e = 1):Tache(id, desc, dispo, deadline,e){if(duree < QTime(DUREE_MAX,0)) duree = dur; else throw CalendarException("La durée d'une tâche unitaire ne peut être supérieur à 12h."); }

public:
        /*!
             *  \brief Destructeur
             *
             *  Destructeur de la classe TacheUnitaire
             */
    virtual ~TacheUnitaire(){}

      /*!
           *  \brief getDuree
           *
           *  Accesseur en lecture de la duree de la Tache Unitaire
           */
    const QTime& getDuree() const { return duree; }

    /*!
         *  \brief setEtat
         *
         *  Accesseur en écriture de l'état de la Tache Unitaire
         *
         *  \parem e : nouvel etat de la tache
         */
    virtual void setEtat(unsigned int e) { etat = (Etat)e; }

    /*!
         *  \brief getEtat
         *
         *  Accesseur en écriture de l'état de la Tache Unitaire
         *
         */
    virtual unsigned int getEtat() const { return (unsigned int)etat; }

    /*!
         *  \brief setDateEcheance
         *
         *  Accesseur en ecriture de la date d'Echeance de la Tache
         *
         *  \param e : nouvelle date d'Echeance
         */
    virtual void setDateEcheance(const QDate& e){}

};

#endif // TACHEUNITAIRE_H
