#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H


/*!
 * \file CalendarWindow.h
 * \brief Onglet de visionnage de l'agenda
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QMainWindow>
#include <QDate>
#include <QFileDialog>

/*! \namespace Ui
 *
 * espace de nommage regroupant les outils composants
 * l'onglet de visionnage de l'agenda
 */
namespace Ui {
class CalendarWindow;
}

/*! \class CalendarWindow
   * \brief Classe representant la fenetre de vue de l'agenda
   *
   *  La classe gere la vue sur 7 jours de notre agenda.
   *  Cette vue sur 7 jours se decompose en plusieurs horaires.
   *  Chaque tache programmée lors de cette semaine et alors automatiquement
   *  affichée.
   */
class CalendarWindow : public QMainWindow
{
    friend class MainWindow;
    Q_OBJECT

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe CalendarWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit CalendarWindow(QWidget *parent = 0);

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe CalendarWindow
         */
    ~CalendarWindow();

    /*!
         *  \brief Affichage des tâches
         *
         *  Permet d'afficher les tâches de la semaine
         *
         */
    void displayTasks();

private:
    Ui::CalendarWindow *ui;/*!< Onglet Agenda*/
    QDate today;/*!< Date courante*/
    QDate currentDate;/*!< Date courante de la semaine en cours*/
    QFileDialog* saveWindow;/*!< Fenetre de sauvegarde*/
    QAction* actionExporterSemaine;/*!< Export des programmations de la semaine*/

    /*!
         *  \brief effacerAffichageTaches
         *
         *  Permet d'effacer l'affichage des taches
         *
         */
    void effacerAffichageTaches();

private slots:
    /*!
         *  \brief Affichage de la semaine
         *
         *  Permet l'affichage des 7 jours d'une semaine !
         *
         *  \param date : date de la semaine que l'on veut afficher
         *  \param isCurrentDay : booleen permettant de savoir si l'on est ou
         *  non en train d'afficher le jour actuel ( qui sera mis en gras dans ce cas la)
         */
    void changeCurrentWeek(QDate* date, bool isCurrentDay);

    /*!
         *  \brief Affichage de la semaine prochaine
         *
         *  Permet d'afficher nos programmations de la semaine prochaine
         */
    void nextWeek();

    /*!
         *  \brief Affichage de la semaine derniere
         *
         *  Permet d'afficher nos programmations de la semaine derniere
         */
    void prevWeek();

    /*!
         *  \brief Changement de semaine
         *
         *  Permet de choisir l'affichage d'une semaine specifique
         *
         */
    void setWeek(int num);

    /*!
         *  \brief openQFileDialog
         *
         *  Permet de choisir ou on exportera le fichier XML
         *
         */
    void openQFileDialog();

};

#endif // CALENDARWINDOW_H
