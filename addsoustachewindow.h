#ifndef ADDSOUSTACHEWINDOW_H
#define ADDSOUSTACHEWINDOW_H

/*!
 * \file AddSousTacheWindow.h
 * \brief Fenetre d ajout de sous-tache unitaire non preemptive
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QTextEdit>
#include <QSpinBox>

/*! \class AddSousTacheWindow
   * \brief classe representant la fenetre d'ajout d'une sous-tache unitaire
   *
   *  La classe gere la reception de tous les elements composants
   *  une sous-tache que ce soit son titre, son identificateur ou autre.
   */

class AddSousTacheWindow : public QDialog
{
    Q_OBJECT

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe AddSousTacheWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit AddSousTacheWindow(QWidget *parent=0);
    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe AddSousTacheWindow
         */
    ~AddSousTacheWindow(){}

private:
    QLineEdit* identificateur;/*!< Identificateur de la Tache*/
    QTextEdit* titre;/*!< Titre de la Tache*/
    QDateEdit* disponibilite;/*!< Disponibilite de la Tache*/
    QDateEdit* echeance;/*!< Echeance de la Tache*/
    QSpinBox* hDuree;/*!< Duree en Heure de la Tache*/
    QSpinBox* mDuree;/*!< Duree en Minute de la Tache*/
    QPushButton* ok;/*!< Bouton de validation*/
    QPushButton* annuler;/*!< Bouton d'annulation*/

private slots:
    /*!
         *  \brief Envoi d'une sous-tache unitaire non preemptive
         *
         *  Le slot permet de recuperer tous les differents elements
         * composant la nouvelle sous-tache pour que le tache manager puisse ensuite l'enregistrer
         * dans le fichier XML.
         */
    void envoiSousTacheUnitaire();

};

#endif // ADDSOUSTACHEWINDOW_H
