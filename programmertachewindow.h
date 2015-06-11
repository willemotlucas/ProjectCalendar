#ifndef PROGRAMMERTACHE_H
#define PROGRAMMERTACHE_H

/*!
 * \file ProgrammerTache.h
 * \brief Fenetre de programmation dans l'agenda
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
class ProgrammerTache;
}

/*! \class ProgrammerTache
   * \brief Classe representant la fenetre d'ajout de programmation.
   *
   *  La classe gere la recuperation des valeurs de la programmation
   *  d'une tache pour ensuite pouvoir l'afficheer
   *  dans notre agenda au bon endroit.
   */
class ProgrammerTache : public QDialog
{
    Q_OBJECT

public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe ProgrammerTache
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit ProgrammerTache(QWidget *parent = 0);

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe ProgrammerTache
         */
    ~ProgrammerTache();

private:
    Ui::ProgrammerTache *ui;
private slots:

    /*!
         *  \brief envoyerProgrammation
         *
         *  Permet l'envoie de toutes les données
         *  renseignées par l'utilisateur dans le fenetre
         *  au programmation manager
         */
    void envoyerProgrammation();
};

#endif // PROGRAMMERTACHE_H
