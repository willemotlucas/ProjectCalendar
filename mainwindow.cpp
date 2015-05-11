#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "projetmanager.h"
#include "global.h"

ProjectWindow* MainWindow::projet= 0;

ProjectWindow& MainWindow::getInstanceProjet(){
    if(projet == 0) projet = new ProjectWindow;
    return *projet;
}

void MainWindow::libererInstanceProjet(){
    delete projet;
    projet = 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Generation des widgets de la fenetre principale
    creerActions();
    creerMenus();
    creerBarreNavigation();

    //Definition de quelques proprietes de le fenetre
    setMinimumSize(500,350);
    setWindowTitle("Project_Calendar");

    //Lire le fichier XML à chaque chargement de l'application
    try{
        ProjetManager& m = ProjetManager::getInstance();
        m.load(fileXML);
    }catch(CalendarException e){
        QMessageBox::warning(this, "Erreur", e.getInfo());
    }

}

void MainWindow::creerMenus(){
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

    menuFichier->addAction(actionNouveauProjet);
    menuFichier->addAction(actionChargerProjet);
    menuFichier->addAction(actionFermerProjet);
    menuFichier->addAction(actionImprimerProjet);
    menuFichier->addAction(actionAfficherAgenda);
    menuFichier->addAction(actionImprimerAgenda);
    menuFichier->addAction(actionQuitter);

    QMenu *menuOutils = menuBar()->addMenu("&Outils");

    menuOutils->addAction(actionPrecedente);
    menuOutils->addAction(actionSuivante);

    QMenu *menuAide = menuBar()->addMenu("&Aide");

    menuAide->addAction(actionAPropos);
    menuAide->addAction(actionAProposQt);
}

void MainWindow::creerActions(){
    //Action du bloc fichier
    actionNouveauProjet = new QAction("Nouveau Projet",this);
    actionNouveauProjet->setShortcut(QKeySequence("Ctrl+N"));
    connect(actionNouveauProjet,SIGNAL(triggered()),this->getInstanceProjet().actionNouveauProjet,SLOT(trigger()));
    actionChargerProjet = new QAction("Ouvrir un Projet",this);
    actionChargerProjet->setShortcut(QKeySequence("Ctrl+O"));
    actionFermerProjet = new QAction("Fermer Projet",this);
    actionFermerProjet->setShortcut(QKeySequence("Ctrl+W"));
    actionImprimerProjet = new QAction("Imprimer Projet",this);
    actionImprimerProjet->setShortcut(QKeySequence("Ctrl+P"));
    actionAfficherAgenda = new QAction("Afficher Agenda",this);
    actionImprimerAgenda = new QAction("Imprimer Agenda",this);
    actionImprimerAgenda->setShortcut(QKeySequence("Ctrl+A"));
    actionQuitter = new QAction("Quitter",this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));

    //Action du bloc outils
    actionPrecedente = new QAction("Precedent",this);
    actionPrecedente->setShortcut(QKeySequence::Back);
    actionSuivante = new QAction("Suivant",this);
    actionSuivante->setShortcut(QKeySequence::Forward);

    //Action du bloc aide
    actionAPropos = new QAction("A propos de ...",this);
    connect(actionAPropos,SIGNAL(triggered()),this,SLOT(aPropos()));
    actionAProposQt = new QAction("A propos de Qt",this);
    connect(actionAProposQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void MainWindow::creerBarreNavigation(){
    //Generation des onglets et chargement de la page d'accueil
    onglets = new QTabWidget(this);

    pageAgenda = new QWidget;
    QVBoxLayout* pAgenda = new QVBoxLayout;
    AgendaWindow* agendaWindow = new AgendaWindow;
    pAgenda->addWidget(agendaWindow);
    pageAgenda->setLayout(pAgenda);

    pageProjet = new QWidget;
    QVBoxLayout* pProjet = new QVBoxLayout;
    //ProjectWindow* projectWindow = new ProjectWindow;
    pProjet->addWidget(projet);
    pageProjet->setLayout(pProjet);


    onglets->addTab(pageAgenda,"Agenda");
    onglets->addTab(pageProjet,"Gestion Projet");
    setCentralWidget(onglets);
}


void MainWindow::aPropos(){
    QMessageBox::information(this,"A propos ...",
                             "Project_Calendar est une application ayant une double fonctionalite:\n"
                             "En effet, cette application permet a l'utilisateur de mieux gerer son agenda,\n"
                             "mais aussi de pourvoir gerer les projets qu'il a.\n"
                             "Cette application fut developpée par Lucas Willemot et Valentin Paul\n"
                             "etudiants en Genie Informatique à l'UTC dans le cadre de l'UV LO21\n");
}

