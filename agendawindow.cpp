#include "agendawindow.h"
#include <QToolBar>


AgendaWindow::AgendaWindow(QWidget *parent) : QMainWindow(parent)
{
    //Generation des widgets de la fenetre agenda
    creerActions();
    creerBarreOutils();

    //Affichage du calendrier
    calendrier = new QTableWidget(24,7,this);
    //calendrier->alternatingRowColors(true);
    //calendrier->selectionMode(SingleSelection);
    setCentralWidget(calendrier);

}

void AgendaWindow::creerActions(){
    actionAjouterTache = new QAction("Ajouter",this);
    actionAnnulerTache = new QAction("Annuler",this);
    actionImprimer = new QAction("Imprimer",this);


    actionPrecedent = new QAction("Precedent",this);
    actionPrecedent->setShortcut(QKeySequence::Back);
    actionSuivant = new QAction("Suivant",this);
    actionSuivant->setShortcut(QKeySequence::Forward);

}

void AgendaWindow::creerBarreOutils(){
    QToolBar* menuAgenda = addToolBar("outils");
    menuAgenda->addAction(actionAjouterTache);
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

