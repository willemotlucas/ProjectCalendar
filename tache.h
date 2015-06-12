#ifndef TACHE_H
#define TACHE_H

/*!
 * \file Tache.h
 * \brief Fichier portant sur les taches
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDate>
#include <QString>
#include <QTextStream>
#include <QDomDocument>
#include <QTreeWidget>

#include "calendarexception.h"

/*! \class Tache
   * \brief classe virtuelle pure representant les taches
   *
   *  La classe gere la creation de toutes les taches de l' utilisateur.
   *  Une nouvelle tache se compose obligatoirement d'un identificateur, un titre,
   *  et d'une date de disponibilité.
   */
class Tache {

protected:
    enum Etat{
        PROGRAMMEE,
        PROGRAMMABLE,
        NON_PROGRAMMABLE
    };

    QString identificateur;/*!< Identificateur du projet*/
    QString titre;/*!< Titre du projet*/
    QDate disponibilite;/*!< Disponibilite du projet*/
    QDate echeance;/*!< Echeance du projet*/
    Etat etat;/*!< Etat du projet*/

    /*!
         *  \brief Constructeur avec l'attribut date d'echeance
         *
         *  Constructeur de la classe Tache
         *
         *  \param id : identificateur de la Tache
         *  \param t : titre de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param deadline : echeance de la Tache
         *  \param e : etat de la Tache
         */
    Tache(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, unsigned int e):
            identificateur(id),titre(t),disponibilite(dispo),echeance(deadline),etat((Etat)e){}

    //Constructeur de tache sans deadline pour les taches composites : la deadline est la borne supérieur des sous-tâches de la tache composite.
    /*!
         *  \brief Constructeur sans l'attribut date d'echeance
         *
         *  Constructeur de la classe Tache
         *
         *  \param id : identificateur de la Tache
         *  \param t : titre de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param e : etat de la Tache
         */
    Tache(const QString& id, const QString& t, const QDate& dispo, unsigned int e):identificateur(id),titre(t),disponibilite(dispo),etat((Etat)e){}

//    Tache(const Tache& t);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe Tache
         *
         *  \param t : tache que l'on veut recopier
         */
    Tache& operator=(const Tache& t);

    /*!
         *  \brief write : fonction virtuelle pure
         *
         *  Ecriture de la tache a l'interieur de notre arborescence
         *
         *  \param dom : arborescence de notre fichier XML
         */
    virtual QDomElement& write(QDomDocument* dom)= 0;

    /*!
         *  \brief chargerTreeTache : fonction virtuelle pure
         *
         *  Chargement de la tache a l'interieur de notre arborescence TreeWidget
         *
         *  \param tree : arborescence de notre treeview
         */
    virtual QTreeWidgetItem& chargerTreeTache(QTreeWidget* tree)=0;

public:
    /*!
         *  \brief save
         *
         *  Sauvegarde de la tache a l'interieur de notre arborescence TreeWidget
         *
         *  \param tree : arborescence de notre fichier XML
         */
    QDomElement& save(QDomDocument* dom) {return write(dom);}

    /*!
         *  \brief chargerTree
         *
         *  Chargement de la tache a l'interieur de notre arborescence TreeWidget
         *
         *  \param tree : arborescence de notre treeview
         */
    QTreeWidgetItem& chargerTree(QTreeWidget* tree){return chargerTreeTache(tree);}
    //DESTRUCTOR

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe Tache
         */
    virtual ~Tache(){};

    //GETTERS et SETTERS

    /*!
         *  \brief getId
         *
         *  Accesseur en lecture de l'identificateur de la Tache
         */
    QString getId() const { return identificateur; }

    /*!
         *  \brief setId
         *
         *  Accesseur en ecriture de l'identificateur de la Tache
         *
         *  \param str : nouvel identificateur de la Tache
         */
    void setId(const QString& str);

    /*!
         *  \brief getTitre
         *
         *  Accesseur en lecture du titre de la Tache
         */
    QString getTitre() const { return titre; }

    /*!
         *  \brief setTitre
         *
         *  Accesseur en ecriture du titre de la Tache
         *
         *  \param str : nouveau Titre de la tache
         */
    void setTitre(const QString& str) { titre=str; }

    /*!
         *  \brief getDateDisponibilite
         *
         *  Accesseur en lecture de la date de Disponibilite de la Tache
         */
    QDate getDateDisponibilite() const {  return disponibilite; }

    /*!
         *  \brief setDateDisponibilite
         *
         *  Accesseur en ecriture de la date de Disponibilite de la Tache
         *
         *  \param dispo : nouvelle date de Disponibilite
         */
    void setDateDisponibilite(QDate dispo) { disponibilite = dispo; }

    /*!
         *  \brief getDateEcheance
         *
         *  Accesseur en lecture de la date d'echeance de la Tache
         */
    QDate getDateEcheance() const {  return echeance; }

    virtual void setEtat(unsigned int e) = 0;
    virtual unsigned int getEtat() const = 0;

    //ABSTRACT METHODS

    //Peut-être mettre en privée pour que seul le TacheManager puisse gérer la date d'échéance d'une tache composite en fonction
    //De ses sous-taches. Mettre en abstrait pour changer le fonctionnement en fonction de la classe fille
//        if (e<disp) throw CalendarException("erreur T�che : date ech�ance < date disponibilit�");
//        disponibilite=disp; echeance=e;

    /*!
         *  \brief setDateEcheance : virtuelle pure
         *
         *  Accesseur en ecriture de la date d'Echeance de la Tache
         *
         *  \param e : nouvelle date d'Echeance
         */
    virtual void setDateEcheance(const QDate& e) = 0;


};

QTextStream& operator<<(QTextStream& f, const Tache& t);

#endif // TACHE_H
