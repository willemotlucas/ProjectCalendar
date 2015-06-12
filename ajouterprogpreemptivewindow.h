#ifndef AJOUTERPROGPREEMPTIVEWINDOW_H
#define AJOUTERPROGPREEMPTIVEWINDOW_H

/*!
 * \file AjouterProgPreemptiveWIndow.h
 * \brief Onglet de programmation d'une tache preemptive dans l'agenda
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QDialog>

/*! \namespace Ui
 *
 * espace de nommage regroupant les outils composants
 * l'onglet de visionnage de l'agenda
 */
namespace Ui {
class AjouterProgPreemptiveWIndow;
}


/*! \class AjouterProgPreemptiveWindow
   * \brief Classe representant la fenetre de
   *  programmation d'une tache preemptive
   *
   *  La classe gere la programmation d'une tache preemptive
   *  dans l'agenda. Cette tache apparaitra ensuite dans la
   *  fenetre agenda.
   */
class AjouterProgPreemptiveWIndow : public QDialog
{
    Q_OBJECT

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe AjouterProgPreemptiveWIndow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit AjouterProgPreemptiveWIndow(QWidget *parent = 0);

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe AjouterProgPreemptiveWIndow
         */
    ~AjouterProgPreemptiveWIndow();

private:
    Ui::AjouterProgPreemptiveWIndow *ui;/*!< Onglet Programmation*/
private slots:

    /*!
         *  \brief envoyerProgrammation
         *
         *  Permet l'envoie de la programmation
         */
    void envoyerProgrammation();
};

#endif // AJOUTERPROGPREEMPTIVEWINDOW_H
