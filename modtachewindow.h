#ifndef MODTACHEWINDOW_H
#define MODTACHEWINDOW_H

/*!
 * \file ModTacheWindow.h
 * \brief Fenetre de modification d'une tache
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QPushButton>


/*! \class ModTacheWindow
   * \brief Classe representant la fenetre de modification d'une tache
   *
   *  La classe affiche une tache selectionnée deja existante
   *  ainsi que les details de celle-ci pour pouvoir ensuite
   *  les modifier.
   */
class ModTacheWindow : public QDialog
{
public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe ModTacheWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit ModTacheWindow(QWidget *parent=0);

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe CalendarWindow
         */
    ~ModTacheWindow(){}

private :
    Q_OBJECT

    QLineEdit* identificateur;/*!< Identificateur de la tache a modifier*/
    QTextEdit* titre;/*!< Titre de la tache a modifier*/
    QCheckBox* preemptive;/*!< Checkbox pour savoir si la tache a modifier est preemtive ou non*/
    QDateEdit* disponibilite;/*!< Disponibilite de la tache a modifier*/
    QDateEdit* echeance;/*!< Echeance de la tache a modifier*/
    QSpinBox* hDuree;/*!< Duree ( en heures) de la tache a modifier*/
    QSpinBox* mDuree;/*!< Duree ( en minutes) de la tache a modifier*/
    QPushButton* sauver;/*!< Sauver les modifications de la tache*/
    QPushButton* annuler;/*!< Annuler les modifications de la tache*/

private slots :
    /*!
         *  \brief sauverTache
         *
         *  Slot de sauvegarde des modifications faites sur la tache
         */
    void sauverTache();
};

#endif // MODTACHEWINDOW_H
