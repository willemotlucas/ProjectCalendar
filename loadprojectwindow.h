#ifndef LOADPROJECTWINDOW_H
#define LOADPROJECTWINDOW_H

/*!
 * \file LoadProjectWindow.h
 * \brief Onglet permettant le chargement d'un projet
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDialog>

/*! \namespace Ui
 *
 * espace de nommage regroupant les outils composants
 * la fenetre ChargerProjet
 */
namespace Ui {
class LoadProjectWindow;
}

/*! \class LoadProjectWindow
   * \brief Classe representant la fenetre de chargement d'un projet
   *
   *  La fenetre va proposer a l'utilisateur tous les projets qu'il a pu
   *  deja crée dans le passé et pour qu'il puisse ainsi rajouter des taches
   *  a l'interieur de celui ci ou en modifier.
   */
class LoadProjectWindow : public QDialog
{
    Q_OBJECT

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe LoadProjectWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit LoadProjectWindow(QWidget *parent = 0);

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe LoadProjectWindow
         */
    ~LoadProjectWindow();

private:
    Ui::LoadProjectWindow *ui;/*!< Fenetre Charger Projet*/

private slots:
    /*!
         *  \brief envoiNomProjet
         *
         *  Slot permettant l'envoi du nom de projet selectionne par
         *  l'utilisateur pour en charger les details.
         */
    void envoiNomProjet();
};

#endif // LOADPROJECTWINDOW_H
