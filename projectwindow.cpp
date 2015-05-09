#include "projectwindow.h"
#include "newprojectwindow.h"
#include "addtachewindow.h"
#include "modtachewindow.h"
#include <QToolBar>

ProjectWindow::ProjectWindow(QWidget *parent) : QMainWindow(parent)
{
    //Generation des widgets de la fenetre agenda
    creerActions();
    creerBarreOutils();
}


void ProjectWindow::creerActions(){
    actionNouveauProjet = new QAction("Nouveau",this);
    connect(actionNouveauProjet,SIGNAL(triggered()),this,SLOT(nouveauProjet()));

    actionChargerProjet = new QAction("Charger",this);
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

void ProjectWindow::nouveauProjet(){
    NewProjectWindow *newProjet = new NewProjectWindow(this);
    newProjet->exec();
}

void ProjectWindow::ajouterTache(){
    AddTacheWindow *newTache = new AddTacheWindow(this);
    newTache->exec();
}

void ProjectWindow::modifierTache(){
    ModTacheWindow *modTache = new ModTacheWindow(this);
    modTache->exec();
}


