#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*!
 * \file MainWindow.h
 * \brief Fenetre Principale de l'application
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QMainWindow>
#include <QWidget>
#include <QKeySequence>
#include <QTabWidget>
#include <QAction>
#include "projectwindow.h"


/*! \class MainWindow
   * \brief Classe representant la fenetre principale de l'application
   *
   *  La fenetre principale a une barre de menu ainsi que 2 onglets :
   *  Agenda et Gestion Projet
   */
class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe MainWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
        explicit MainWindow(QWidget *parent = 0);

    /*!
         *  \brief getInstanceProjet
         *
         *  Fonction statique permettant d'avoir l'instance unique du projet
         *  a n'importe quel endroit du code.
         */
        static ProjectWindow& getInstanceProjet();

    /*!
         *  \brief libererInstanceProjet
         *
         *  Fonction statique permettant de liberer l'instance du projet en cours.
         */
        static void libererInstanceProjet();

    private:
        /*!
             *  \brief creerMenus
             *
             *  Permet de construire la barre de menus de la fenetre principale
             */
        void creerMenus();

        /*!
             *  \brief creerActions
             *
             * Permet de construire les differentes actions a l'interieur du menu
             * et de les relier au onglet de notre application
             */
        void creerActions();

        /*!
             *  \brief creerBarreNavigation
             *
             *  Generation des onglets et chargement de la page d'accueil
             */
        void creerBarreNavigation();

        static ProjectWindow* projet;/*!< attribut statique : projet*/
        QWidget* pageCalendar;/*!< Onglet Agenda*/
        QWidget* pageProjet;/*!< Onglet Gestion de projet*/


    private:
        QTabWidget* onglets;/*!< Onglets*/

        QAction* actionNouveauProjet;/*!< Action creation nouveau projet*/
        QAction* actionChargerProjet;/*!< Action chargement projet*/
        QAction* actionFermerProjet;/*!< Action fermer projet*/
        QAction* actionAfficherAgenda;/*!< Action afficher l'agenda*/
        QAction* actionImprimerProjet;/*!< Action imprimer le projet */
        QAction* actionImprimerAgenda;/*!< Action imprimer la semaine de l'agenda*/
        QAction* actionQuitter;/*!< Action quitter l'application*/
        QAction* actionAPropos;/*!< Action a propos de l'application */
        QAction* actionAProposQt;/*!< Action a propos de Qt*/
        QAction* actionPrecedente;/*!< Action pour revenir en arriere*/
        QAction* actionSuivante;/*!< Action pour revenir en avant*/



    private slots:
        /*!
             *  \brief aPropos
             *
             *  Appel la fenetre aPropos qui donne des informations
             *  sur l'application
             */
        void aPropos();

};

#endif // MAINWINDOW_H
