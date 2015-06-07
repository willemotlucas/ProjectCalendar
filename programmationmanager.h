#ifndef PROGRAMMATIONMANAGER_H
#define PROGRAMMATIONMANAGER_H

/*!
 * \file ProgrammationManager.h
 * \brief Singleton permettant de s'occuper de la programmation des taches
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include "calendarexception.h"
#include "tache.h"
#include "programmation.h"
#include <QTime>
#include <QDate>

/*! \class ProgrammationManager
   * \brief Classe Singleton Programmation Manager
   *
   *  La classe Programmation Manager s'occupe de gerer
   *  les programmations des taches dans l'agenda de
   *  l'utilisateur.
   */
class ProgrammationManager {
private:
    std::vector<Programmation*> programmations;/*!< Vector des programmations enregistrées*/

    /*!
         *  \brief addItem
         *
         *  Ajout d'une programmation
         *
         *  \param t : la programmation que l'on veut ajouter au vector
         */
    void addItem(Programmation* t);

    /*!
         *  \brief trouverProgrammation
         *
         *  Permet de retrouver la programmation d'une tache particuliere
         *
         *  \param t : la tache dont on voudrait retrouver la programmation
         */
    Programmation* trouverProgrammation(const Tache& t) const;

    /*! \class Handler
       * \brief Classe encapsulant l'instance unique du ProgrammationManager
       *
       *  La classe Handler permet de s'occuper automatiquement
       *  de l'instance unique du programmationManager.
       *  Ainsi, lors de la fermeture du programme, le destructeur de Handler
       *  sera appele et celui ci lancera alors la sauvegarde des modifications
       *  dans le fichier XML.
       */
    struct Handler{
        ProgrammationManager* instance;/*!< Instance unique du projet manager*/

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

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe ProgrammationManager
         */
    ProgrammationManager();

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe ProgrammationManager
         */
    ~ProgrammationManager();

    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie de la classe ProgrammationManager
         *
         *  \param um : ProgrammationManager a recopie
         */
    ProgrammationManager(const ProgrammationManager& um);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe ProgrammationManager
         *
         *  \param um : ProgrammationManager a recopie
         */
    ProgrammationManager& operator=(const ProgrammationManager& um);

    /*!
         *  \brief ajouterProgrammation
         *
         *  Fonction permettant d'ajouter une tache dans les programmations
         *
         *  \param t : la tache a ajoute dans la programmation
         *  \param d : la date de programmation de cette tache
         *  \param h : l'heure de programmation de cette tache
         *
         */

public:
    void ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h);

    /*!
         *  \brief getInstance
         *
         *  Fonction statique permettant d'avoir l'instance unique du projet
         *  a n'importe quel endroit du code.
         */
    static ProgrammationManager& getInstance();

    /*!
         *  \brief libererInstanceProjet
         *
         *  Fonction statique permettant de liberer l'instance du projet en cours.
         */
    static void libererInstance();
};

#endif // PROGRAMMATIONMANAGER_H
