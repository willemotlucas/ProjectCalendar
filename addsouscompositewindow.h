#ifndef ADDSOUSCOMPOSOTEWINDOW_H
#define ADDSOUSCOMPOSOTEWINDOW_H


/*!
 * \file AddSousCompositeWindow.h
 * \brief Fenetre d ajout de sous-tache composite
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>


/*! \class AddSousCompositeWindow
   * \brief classe representant la fenetre d'ajout d'une sous-tache composite
   *
   *  La classe gere la reception de tous les elements composants
   *  une sous-tache que ce soit son titre, son identificateur ou autre.
   */

class AddSousCompositeWindow : public QDialog
{
    Q_OBJECT

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe AddCompositeWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit AddSousCompositeWindow(QWidget *parent=0);
    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe AddCompositeWindow
         */
    ~AddSousCompositeWindow(){}

private:
    QLineEdit* identificateur;/*!< Identificateur de la Tache*/
    QTextEdit* titre;/*!< Titre de la Tache*/
    QDateEdit* disponibilite;/*!< Disponibilite de la Tache*/
    QPushButton* ok;/*!< Bouton de validation*/
    QPushButton* annuler;/*!< Bouton d'annulation*/

private slots:
    /*!
         *  \brief Envoi d'une sous-tache composite
         *
         *  Le slot permet de recuperer tous les differents elements
         * composant la nouvelle sous-tache pour que le tache manager puisse ensuite l'enregistrer
         * dans le fichier XML.
         */
    void envoiSousTacheComposite();

};
#endif // ADDSOUSCOMPOSOTEWINDOW_H
