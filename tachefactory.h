#ifndef TACHEFACTORY_H
#define TACHEFACTORY_H

/*!
 * \file TacheFactory.h
 * \brief Fichier portant sur la factory de creation de Tache
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include "tache.h"

/*! \class TacheFactory
   * \brief classe representant la factory de creation de tache.
   *
   *  La classe gere la creation de toutes les taches du programme.
   *  Il se chargera lui-meme de choisir quel type de tache il doit crer en fonction
   *  des demandes de l'utilisateur.
   */
class TacheFactory
{
private:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe TacheFactory
         */
    TacheFactory();

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe TacheFactory
         */
    ~TacheFactory();

    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie de la classe TacheFactory
         *
         *  \param um : ProjetManager a recopie
         */
    TacheFactory(const TacheFactory& um);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe TacheFactory
         *
         *  \param um : TacheFactory a recopie
         */
    TacheFactory& operator=(const TacheFactory& um);

    /*! \class Handler
       * \brief Classe encapsulant l'instance unique du TacheFactory
       *
       *  La classe Handler permet de s'occuper automatiquement
       *  de l'instance unique du TacheFactory
       *  Ainsi, lors de la fermeture du programme, le destructeur de Handler
       *  sera appele et celui ci lancera alors la sauvegarde des modifications
       *  dans le fichier XML.
       */
    struct Handler{
        TacheFactory* instance;/*!< Instance unique du TacheFactory*/

        /*!
             *  \brief Constructeur
             *
             *  Constructeur de la classe Handler
             */
        Handler():instance(0){}
        // destructeur appelé à la fin du programme

        /*!
             *  \brief Destructeur
             *
             *  Destructeur de la classe Handler
             */
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;/*!< Handler statique permettant notamment la sauvegarde automatique*/

public:

    /*!
         *  \brief getInstance
         *
         *  Fonction statique permettant d'avoir l'instance unique du TacheFactory
         *  a n'importe quel endroit du code.
         */
    static TacheFactory& getInstance();

    /*!
         *  \brief libererInstance
         *
         *  Fonction statique permettant de liberer l'instance du TacheFactory en cours.
         */
    static void libererInstance();
    /*!
         *  \brief creerTacheUnitaire
         *
         *  Creation d'une tache unitaire non preemptive
         *
         *  \param id : identificateur de la Tache
         *  \param desc : description de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param echeance : echeance de la Tache
         *  \param duree : duree de la Tache
         *  \param etat : etat de la Tache
         */
    Tache& creerTacheUnitaire(const QString& id, const QString& desc, const QDate& dispo, const QDate& echeance, const QTime& duree, unsigned int etat=1);

    /*!
         *  \brief creerTacheUnitairePreemptive
         *
         *  Creation d'une tache unitaire preemptive
         *
         *  \param id : identificateur de la Tache
         *  \param desc : description de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param echeance : echeance de la Tache
         *  \param dureeInit : duree initiale de la Tache
         *  \param dureeRestante : duree restante de la Tache
         *  \param etat : etat de la Tache
         */
    Tache& creerTacheUnitairePreemptive(const QString &id, const QString &desc, const QDate &dispo, const QDate &echeance, const QTime& dureeInit, const QTime &dureeRest, unsigned int etat=1);

    /*!
         *  \brief creerTacheComposite
         *
         *  Creation d'une tache composite
         *
         *  \param id : identificateur de la Tache
         *  \param desc : description de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param etat : etat de la Tache
         */
    Tache& creerTacheComposite(const QString& id, const QString& t, const QDate& dispo);



};

#endif // TACHEFACTORY_H
