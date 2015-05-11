#include "projectwindow.h"
#include "newprojectwindow.h"
#include "addtachewindow.h"
#include "modtachewindow.h"
#include "loadprojectwindow.h"
#include "projetmanager.h"
#include "global.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>

ProjectWindow::ProjectWindow(QWidget *parent) : QMainWindow(parent)
{
    //Generation des widgets de la fenetre agenda
    creerActions();
    creerBarreOutils();
//    creerAffichageProjet();
}


void ProjectWindow::creerActions(){
    actionNouveauProjet = new QAction("Nouveau",this);
    connect(actionNouveauProjet,SIGNAL(triggered()),this,SLOT(nouveauProjet()));

    actionChargerProjet = new QAction("Charger",this);
    connect(actionChargerProjet, SIGNAL(triggered()), this, SLOT(chargerProjet()));
    actionFermerProjet = new QAction("Fermer",this);
    actionAjouterTache = new QAction("Ajouter Tache",this);
    connect(actionAjouterTache,SIGNAL(triggered()),this,SLOT(ajouterTache()));
    actionModifierTache = new QAction("Modifier Tache",this);
    connect(actionModifierTache,SIGNAL(triggered()),this,SLOT(modifierTache()));
    actionAnnulerTache = new QAction("Annuler",this);
    actionImprimer = new QAction("Imprimer",this);


    actionPrecedent = new QAction("Precedent",this);
    actionPrecedent->setShortcut(QKeySequence::Back);
    actionSuivant = new QAction("Suivant",this);
    actionSuivant->setShortcut(QKeySequence::Forward);
}

void ProjectWindow::creerBarreOutils(){
    QToolBar* menuAgenda = addToolBar("outils");
    menuAgenda->addAction(actionNouveauProjet);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionChargerProjet);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionFermerProjet);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionAjouterTache);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionModifierTache);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionAnnulerTache);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionImprimer);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionPrecedent);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionSuivant);
    menuAgenda->setMovable(false);
}

void ProjectWindow::creerAffichageProjet(){
    //Creation du premier groupbox avec les boutons d'ajout de taches
    gestionDuProjet = new QGroupBox("Gestion du projet");
    QHBoxLayout* gestion = new QHBoxLayout;
    addTacheComposite = new QPushButton("Ajouter tache composite");
    addTacheComposite->setEnabled(false);
    addTacheUnitaire = new QPushButton("Ajouter tache unitaire");
    addTacheUnitaire->setEnabled(false);
    addTacheUnitairePreemptive = new QPushButton("Ajotuer tache unitaire préemptive");
    addTacheUnitairePreemptive->setEnabled(false);
    gestion->addWidget(addTacheComposite);
    gestion->addWidget(addTacheUnitaire);
    gestion->addWidget(addTacheUnitairePreemptive);
    gestionDuProjet->setLayout(gestion);

    //Creation du deuxième groupbox d'affichage des détails du projet chargé
    //L'affichage est vide au départ et se complètera lorsque l'utilisateur aura chargé un projet
    //Les boutons et les edit sont donc désactivés au début.
    detailsProjet = new QGroupBox("Détails du projet", this);
    QHBoxLayout* nom = new QHBoxLayout;
    QHBoxLayout* desc = new QHBoxLayout;
    QHBoxLayout* dispo = new QHBoxLayout;
    QHBoxLayout* echeance = new QHBoxLayout;
    QVBoxLayout* details = new QVBoxLayout;

    nomProjet = new QLabel("Nom");
    nomProjetEdit = new QLineEdit;
    nomProjetEdit->setReadOnly(true);
    nom->addWidget(nomProjet);
    nom->addWidget(nomProjetEdit);

    descriptionProjet = new QLabel("Description");
    descriptionProjetEdit = new QPlainTextEdit;
    descriptionProjetEdit->setReadOnly(true);
    desc->addWidget(descriptionProjet);
    desc->addWidget(descriptionProjetEdit);

    dateDispoProjet = new QLabel("Date de disponibilité");
    dateDispoProjetEdit = new QDateEdit;
    dateDispoProjetEdit->setReadOnly(true);
    dispo->addWidget(dateDispoProjet);
    dispo->addWidget(dateDispoProjetEdit);

    dateEcheanceProjet= new QLabel("Date d'échéance");
    dateEcheanceProjetEdit = new QDateEdit;
    dateEcheanceProjetEdit->setReadOnly(true);
    echeance->addWidget(dateEcheanceProjet);
    echeance->addWidget(dateEcheanceProjetEdit);

    details->addLayout(nom);
    details->addLayout(desc);
    details->addLayout(dispo);
    details->addLayout(echeance);
    detailsProjet->setLayout(details);

    projectTree = new QTreeWidget;

    //Affichage dans la fenêtre
    QVBoxLayout* partieDroite = new QVBoxLayout;
    partieDroite->addWidget(gestionDuProjet);
    partieDroite->addWidget(detailsProjet);
    QHBoxLayout* fenetre = new QHBoxLayout(this);
    fenetre->addWidget(projectTree);
    fenetre->addLayout(partieDroite);
}

void ProjectWindow::nouveauProjet(){
    NewProjectWindow *newProjet = new NewProjectWindow(this);
    newProjet->exec();
}

void ProjectWindow::chargerProjet(){
    LoadProjectWindow* loadedProject = new LoadProjectWindow(this);
    loadedProject->exec();
}

void ProjectWindow::ajouterTache(){
    AddTacheWindow *newTache = new AddTacheWindow(this);
    newTache->exec();
}

void ProjectWindow::modifierTache(){
    ModTacheWindow *modTache = new ModTacheWindow(this);
    modTache->exec();
}


