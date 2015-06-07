#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H


/*!
 * \file ProjectWindow.h
 * \brief Onglet de visionnage de la gestion Projet
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QMainWindow>
#include <QAction>
#include <QTreeWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QCheckBox>

#include "projet.h"

/*! \class ProjectWindow
   * \brief Classe representant la fenetre de vue de Gestion de Projet
   *
   *  La classe gere l'onglet de gestion de projet.
   *  Celui ci se compose d'un tree view pour voir l'arborescence du projet,
   *  de la description du projet en cours ainsi que des boutons d'ajouts de taches
   */
class ProjectWindow : public QMainWindow
{
    friend class MainWindow;
    Q_OBJECT
public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe ProjectWindow
         *
         *  \param parent : on renseigne son parent s'il en a un
         */
    explicit ProjectWindow(QWidget *parent = 0);

    /*!
         *  \brief getNomProjet
         *
         *  Accesseur en lecture du nom du projet
         */
    QString getNomProjet() const{
        return nom->text();
    }

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe ProjectWindow
         */
    ~ProjectWindow(){}

private:
    /*!
         *  \brief creerBarreOutils
         *
         *  Fonction permettant de creer la barre outils de l'onglet
         */
    void creerBarreOutils();

    /*!
         *  \brief creerActions
         *
         *  Fonction permettant de creer les actions entre la barre
         *  d'outils et la fenetre
         */
    void creerActions();

    /*!
         *  \brief creerAffichageProjet
         *
         *  Fonction permettant l'affichage de l'onglet
         */
    void creerAffichageProjet();


private:
    //boutons barre outils
    QAction* actionNouveauProjet;/*!< Action nouveau projet*/
    QAction* actionChargerProjet;/*!< Action chargement d'un projet*/
    QAction* actionFermerProjet;/*!< Action fermeture d'un projet*/
    QAction* actionImprimer;/*!< Action Imprimer le projet actuel*/
    QAction* actionPrecedent;/*!< Action retour en arriere*/
    QAction* actionSuivant;/*!< Action retour en avant*/

    //Arbre view et bouton d'ajout de taches
    QTreeWidget* projectTree;/*!< Arborescence du projet*/
    QTreeWidgetItem* rootTree;/*!< Racine de l'arborescence*/
    QPushButton* addTacheComposite;/*!< Bouton Tache Composite*/
    QPushButton* addTacheUnitaire;/*!< Bouton Tache Unitaire*/
    QPushButton* addTacheUnitairePreemptive;/*!< Bouton Tache Unitaire Preemptive*/

    //Description de notre projet
    QLineEdit* nom;/*!< Nom du projet*/
    QTextEdit* description;/*!< Description du projet*/
    QDateEdit* dateDispo;/*!< Date Disponibilite du projet*/
    QDateEdit* dateEcheance;/*!< Date Echeance du projet*/

    Projet* projetOuvert;/*!< Pointeur sur le projet ouvert*/

    //Description de notre tache
    QLineEdit* idTache;/*!< identificateur de la Tache*/
    QTextEdit* nomTache;/*!< titre de la Tache*/
    QDateEdit* dateDispoTache;/*!< Date de disponibilite de la Tache*/
    QDateEdit* dateEcheanceTache;/*!< Date d'echeance de la Tache*/
    QCheckBox* tachePreemtive;/*!< Boolen pour savoir si la tache est preemptive*/
    QSpinBox* hDureeTache;/*!< Duree en Heure de la Tache*/
    QSpinBox* mDureeTache;/*!< Duree en Minute de la Tache*/
    QPushButton* modifier;/*!< Bouton de modification de la Tache*/
    QPushButton* programmer;/*!< Bouton de modification de la Tache*/
    QPushButton* ajouterSousTache;/*!< Bouton de modification de la Tache*/

signals:

private slots:
    /*!
         *  \brief nouveauProjet
         *
         *  Appel de la fenetre de creation d'un projet
         */
    void nouveauProjet();

    /*!
         *  \brief chargerProjet
         *
         *  Appel de la fenetre de chargement d'un projet
         */
    void chargerProjet();

    /*!
         *  \brief fenetreAjouterTacheComposite
         *
         *  Appel la fenetre d'ajout d'une tache composite
         */
    void fenetreAjouterTacheComposite(){}

    /*!
         *  \brief fenetreAjouterTacheUnitaire
         *
         *  Appel la fenetre d'ajout d'une tache unitaire simple
         */
    void fenetreAjouterTacheUnitaire();

    /*!
         *  \brief fenetreAjouterTacheUnitairePreemptive
         *
         *  Appel la fenetre d'ajout d'une tache unitaire preemptive
         */
    void fenetreAjouterTacheUnitairePreemptive();

    /*!
         *  \brief modifierTache
         *
         *  Permet de modifier une tache du projet
         */
    void modifierTache();

    /*!
         *  \brief fermetProjet
         *
         *  Permet de fermer le projet actuel
         */
    void fermerProjet();

    /*!
         *  \brief chargerDetailsTache
         *
         *  Permet de charger les details d'une tache du projet
         *
         *  \param identifiantTache : nom de la Tache Selectionnée
         */
    void chargerDetailsTache(QTreeWidgetItem* item, int column);

public:
    /*!
         *  \brief chargerDetailsProjet
         *
         *  Permet de charger les details d'un projet deja existant
         *
         *  \param nomProjet : nom du projet que l'on veut charger
         */
    void chargerDetailsProjet(const QString& nomProjet);

    /*!
         *  \brief ajouterTache
         *
         *  Permet d'ajouter une tache dans le projet actuel
         *
         *  \param t : tache que l'on veut ajouter au projet
         */
    void ajouterTache(Tache& t);
};

#endif // PROJECTWINDOW_H
