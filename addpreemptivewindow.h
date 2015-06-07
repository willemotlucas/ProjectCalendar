#ifndef ADDPREEMPTIVEWINDOW_H
#define ADDPREEMPTIVEWINDOW_H

/*!
 * \file AddPreemptiveWindow.h
 * \brief Fenetre d ajout de tache unitaire preemptive
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QSpinBox>

/*! \class AddPreemptiveWindow
   * \brief classe representant la fenetre d'ajout d'une tache preemtive
   *
   *  La classe gere la reception de tous les elements composants
   *  une tache que ce soit son titre, son identificateur ou autre.
   */

class AddPreemptiveWindow : public QDialog
{
    Q_OBJECT

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe AddPreemtiveWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit AddPreemptiveWindow(QWidget *parent=0);
    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe AddTacheWindow
         */
    ~AddPreemptiveWindow(){}

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
         *  \brief Envoi d'une tache unitaire preemptive
         *
         *  Le slot permet de recuperer tous les diffs elements
         * composant la nouvelle tache pour que le tache manager puisse ensuite l'enregistrer
         * dans le fichier XML.
         */
    void envoiPreemptive(){}

};
#endif // ADDPREEMPTIVEWINDOW_H
