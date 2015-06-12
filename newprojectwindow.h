#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

/*!
 * \file NewProjectWindow.h
 * \brief Fenetre de creation d'un nouveau projet
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QWidget>
#include <QDialog>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>


/*! \class NewProjectWindow
   * \brief Classe representant la fenetre de creation d'un projet
   *
   *  La fenetre permet de renseigner les differents elements
   *  tels que la description , la date de disponibilite , etc
   *  d'un nouveau projet.
   */
class NewProjectWindow : public QDialog
{
    Q_OBJECT
public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe NewProjectWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit NewProjectWindow(QWidget *parent = 0);

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe CalendarWindow
         */
    ~NewProjectWindow(){}

private:
    QLineEdit* nom;/*!< Nom du projet*/
    QDateEdit* dateDispo;/*!< Date Disponibilite du projet*/
    QDateEdit* dateEcheance;/*!< Date d'echeance du projet*/
    QTextEdit* description;/*!< Description du projet*/
    QPushButton* ok;/*!< Bouton de validation */
    QPushButton* annuler;/*!< Bouton d'annulation */

private slots:
    /*!
         *  \brief creationNouveauProjet
         *
         *  Slot permettant l'ajout du projet dans le fichier XML
         */
    void creationNouveauProjet();
};

#endif // NEWPROJECTWINDOW_H
