#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "projetmanager.h"
#include "calendarwindow.h"
#include "global.h"
#include "programmationmanager.h"

ProjectWindow* MainWindow::projet= 0;

ProjectWindow& MainWindow::getInstanceProjet(){
    if(projet == 0) projet = new ProjectWindow;
    return *projet;
}

void MainWindow::libererInstanceProjet(){
    delete projet;
    projet = 0;
}

CalendarWindow* MainWindow::calendar= 0;

CalendarWindow& MainWindow::getInstanceAgenda(){
    if(calendar == 0) calendar = new CalendarWindow;
    return *calendar;
}

void MainWindow::libererInstanceAgenda(){
    delete calendar;
    calendar = 0;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    //Lire le fichier XML à chaque chargement de l'application
    try{
        ProjetManager& m = ProjetManager::getInstance();
        ProgrammationManager& progm = ProgrammationManager::getInstance();
        m.load(fileXML);
        progm.load();
    }catch(CalendarException e){
        QMessageBox::warning(this, "Erreur", e.getInfo());
    }
    //Generation des widgets de la fenetre principale
    creerActions();
    creerMenus();
    creerBarreNavigation();

    //Definition de quelques proprietes de le fenetre
    setMinimumSize(1020,670);
    setWindowTitle("Project_Calendar");

}

void MainWindow::creerMenus(){
    QMenu *menuFichier = menuBar()->addMenu("&Fichier");

    menuFichier->addAction(actionNouveauProjet);
    menuFichier->addAction(actionChargerProjet);
    menuFichier->addAction(actionFermerProjet);
    menuFichier->addAction(actionImprimerProjet);
    menuFichier->addAction(actionImprimerAgenda);
    menuFichier->addAction(actionQuitter);


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
    connect(actionChargerProjet,SIGNAL(triggered()),this->getInstanceProjet().actionChargerProjet,SLOT(trigger()));
    actionFermerProjet = new QAction("Fermer Projet",this);
    actionFermerProjet->setShortcut(QKeySequence("Ctrl+W"));
    connect(actionFermerProjet,SIGNAL(triggered()),this->getInstanceProjet().actionFermerProjet,SLOT(trigger()));

    actionImprimerProjet = new QAction("Imprimer Projet",this);
    actionImprimerProjet->setShortcut(QKeySequence("Ctrl+P"));
    connect(actionImprimerProjet,SIGNAL(triggered()),this->getInstanceProjet().actionImprimer,SLOT(trigger()));
    actionImprimerAgenda = new QAction("Imprimer Agenda",this);
    actionImprimerAgenda->setShortcut(QKeySequence("Ctrl+A"));
    connect(actionImprimerAgenda,SIGNAL(triggered()),this->getInstanceAgenda().actionExporterSemaine,SLOT(trigger()));
    actionQuitter = new QAction("Quitter",this);
    actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
    connect(actionQuitter,SIGNAL(triggered()),qApp,SLOT(quit()));


    //Action du bloc aide
    actionAPropos = new QAction("A propos de ...",this);
    connect(actionAPropos,SIGNAL(triggered()),this,SLOT(aPropos()));
    actionAProposQt = new QAction("A propos de Qt",this);
    connect(actionAProposQt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
}

void MainWindow::creerBarreNavigation(){
    //Generation des onglets et chargement de la page d'accueil
    onglets = new QTabWidget(this);

    pageCalendar = new QWidget;
    QVBoxLayout* pCalendar = new QVBoxLayout;
    pCalendar->addWidget(&getInstanceAgenda());
    pageCalendar->setLayout(pCalendar);

    pageProjet = new QWidget;
    QVBoxLayout* pProjet = new QVBoxLayout;
    pProjet->addWidget(&getInstanceProjet());
    pageProjet->setLayout(pProjet);


    onglets->addTab(pageCalendar,"Agenda");
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

