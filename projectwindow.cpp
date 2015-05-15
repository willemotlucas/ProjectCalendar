#include "projectwindow.h"
#include "newprojectwindow.h"
#include "addtachewindow.h"
#include "modtachewindow.h"
#include "loadprojectwindow.h"
#include "mainwindow.h"
#include "closeprojectwindow.h"
#include "projetmanager.h"
#include "global.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>

ProjectWindow::ProjectWindow(QWidget *parent) : QMainWindow(parent)
{
    //Generation des widgets de la fenetre agenda
    creerActions();
    creerBarreOutils();
    creerAffichageProjet();
}


void ProjectWindow::creerActions(){
    actionNouveauProjet = new QAction("Nouveau",this);
    connect(actionNouveauProjet,SIGNAL(triggered()),this,SLOT(nouveauProjet()));

    actionChargerProjet = new QAction("Charger",this);
    connect(actionChargerProjet, SIGNAL(triggered()), this, SLOT(chargerProjet()));
    actionFermerProjet = new QAction("Fermer",this);
    connect(actionFermerProjet,SIGNAL(triggered()),this,SLOT(fermerProjet()));
    /*actionAjouterTache = new QAction("Ajouter Tache",this);
    connect(actionAjouterTache,SIGNAL(triggered()),this,SLOT(ajouterTache()));
    actionModifierTache = new QAction("Modifier Tache",this);
    connect(actionModifierTache,SIGNAL(triggered()),this,SLOT(modifierTache()));
    actionAnnulerTache = new QAction("Annuler",this);*/
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
    menuAgenda->addAction(actionImprimer);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionPrecedent);
    menuAgenda->addSeparator();
    menuAgenda->addAction(actionSuivant);
    menuAgenda->setMovable(false);
}

void ProjectWindow::creerAffichageProjet(){
    //1ere colonne de notre fenetre gestion projet :
    projectTree = new QTreeWidget;
    projectTree->setFixedWidth(150);
    QVBoxLayout* partieGauche = new QVBoxLayout;
    partieGauche->addWidget(projectTree);
    projectTree->setDisabled(true);

    //2ieme colonne de notre fenetre gestion projet ;
        //1er groupbox permettant l'affichage des données du projet chargé
    //L'affichage est vide au départ et se complètera lorsque l'utilisateur aura chargé un projet
    nom = new QLineEdit;
    QLabel* labelNom = new QLabel("Nom:");
    QHBoxLayout* N = new QHBoxLayout;
    N->addWidget(labelNom);
    N->addWidget(nom);

    description =new QTextEdit;
    QLabel* labelDescription = new QLabel("Description:");
    QHBoxLayout* D = new QHBoxLayout;
    D->addWidget(labelDescription);
    D->addWidget(description);


    dateDispo = new QDateEdit;
    QLabel* labelDispo = new QLabel("Date Début :");
    QHBoxLayout* Disp = new QHBoxLayout;
    Disp->addWidget(labelDispo);
    Disp->addWidget(dateDispo);


    dateEcheance = new QDateEdit;
    QLabel* labelEcheance = new QLabel("Date Echeance :");
    QHBoxLayout* E = new QHBoxLayout;
    E->addWidget(labelEcheance);
    E->addWidget(dateEcheance);

    QVBoxLayout* detProjet = new QVBoxLayout;
    detProjet->addLayout(N);
    detProjet->addLayout(D);
    detProjet->addLayout(Disp);
    detProjet->addLayout(E);

    QGroupBox* detailsProjet = new QGroupBox("Détails du projet");
    detailsProjet->setLayout(detProjet);
    detailsProjet->setDisabled(true);

        //2ieme groupbox permettant l'ajout de tache dans notre projet
    addTacheComposite = new QPushButton("Composite");
    addTacheComposite->setDisabled(true);
    addTacheUnitaire = new QPushButton("Unitaire");
    addTacheUnitaire->setDisabled(true);
    addTacheUnitairePreemptive = new QPushButton("Unitaire Preemptive");
    addTacheUnitairePreemptive->setDisabled(true);

    QHBoxLayout* addT = new QHBoxLayout;
    addT->addWidget(addTacheUnitaire);
    addT->addWidget(addTacheUnitairePreemptive);
    addT->addWidget(addTacheComposite);

    QGroupBox* addTache = new QGroupBox("Ajout d'une tache au projet");
    addTache->setLayout(addT);

    //Assemblage partie droite
    QVBoxLayout* partieDroite = new QVBoxLayout;
    partieDroite->addWidget(detailsProjet);
    partieDroite->addWidget(addTache);

    //Affichage dans la fenêtre
    //Attention, on est dans une fenetre centrale du coup on doit TOUT mettre dans un widget principale
    //et ENSUITE declarer ce widget comme CentralWidget de notre fenetre

    QHBoxLayout* fenetre = new QHBoxLayout;
    fenetre->addLayout(partieGauche);
    fenetre->addLayout(partieDroite);


    QWidget* fenetreWidget = new QWidget;
    fenetreWidget->setLayout(fenetre);
    setCentralWidget(fenetreWidget);
}

void ProjectWindow::nouveauProjet(){
    NewProjectWindow *newProjet = new NewProjectWindow(this);
    newProjet->exec();
}

void ProjectWindow::chargerProjet(){
    LoadProjectWindow* loadedProject = new LoadProjectWindow(this);
    loadedProject->exec();
}

void ProjectWindow::chargerDetailsProjet(const QString& nomProjet){
    ProjetManager& m = ProjetManager::getInstance();
    Projet* p = m.getProjet(nomProjet);
    nom->setText(p->getNom());
    description->setPlainText(p->getDescription());
    dateDispo->setDate(p->getDisponibilite());
    dateEcheance->setDate(p->getEcheance());
    //Arbre et ajout de tache disponibles dorenavant !
    addTacheUnitaire->setEnabled(true);
    addTacheUnitairePreemptive->setEnabled(true);
    addTacheComposite->setEnabled(true);
    projectTree->setEnabled(true);
}
void ProjectWindow::fermerProjet(){
    //ce slot va alors faire apparaitre une fenetre qui se chargera de prevenir
    //l'utilisateur qu'il va quitter la gestion du projet en cours
    //CloseProjectWindow *closeProject = new CloseProjectWindow(this);
    //closeProject->exec();
    int reponse = QMessageBox::question(this, "Fermer Projet", "Etes vous sur de vouloir quitter la gestion de ce projet ?", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            MainWindow::libererInstanceProjet();
            MainWindow::getInstanceProjet();
        }

}

/*void ProjectWindow::ajouterTache(){
    AddTacheWindow *newTache = new AddTacheWindow(this);
    newTache->exec();
}*/

void ProjectWindow::modifierTache(){
    ModTacheWindow *modTache = new ModTacheWindow(this);
    modTache->exec();
}



