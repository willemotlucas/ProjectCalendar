#include "projectwindow.h"
#include "newprojectwindow.h"
#include "addtachewindow.h"
#include "modtachewindow.h"
#include "loadprojectwindow.h"
#include "mainwindow.h"
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
    projetOuvert = NULL;

    connect(addTacheUnitaire,SIGNAL(clicked()),this,SLOT(fenetreAjouterTacheUnitaire()));
}


void ProjectWindow::creerActions(){
    actionNouveauProjet = new QAction("Nouveau",this);
    connect(actionNouveauProjet,SIGNAL(triggered()),this,SLOT(nouveauProjet()));

    actionChargerProjet = new QAction("Charger",this);
    connect(actionChargerProjet, SIGNAL(triggered()), this, SLOT(chargerProjet()));
    actionFermerProjet = new QAction("Fermer",this);
    connect(actionFermerProjet,SIGNAL(triggered()),this,SLOT(fermerProjet()));
    /*actionModifierTache = new QAction("Modifier Tache",this);
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
    projectTree->setFixedWidth(225);
    QVBoxLayout* partieGauche = new QVBoxLayout;
    partieGauche->addWidget(projectTree);
    projectTree->setDisabled(true);
    projectTree->setHeaderLabel("Arborescence du projet");

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

    //On garde le projet ouvert en mémoire grâce à un attribut de la projectWindow
    //Afin de retrouver facilement le projet en cours de modification pour lui ajouter des tâches
    projetOuvert = m.getProjet(nomProjet);

    nom->setText(projetOuvert->getNom());
    description->setPlainText(projetOuvert->getDescription());
    dateDispo->setDate(projetOuvert->getDisponibilite());
    dateEcheance->setDate(projetOuvert->getEcheance());
    //Arbre et ajout de tache disponibles dorenavant !
    addTacheUnitaire->setEnabled(true);
    addTacheUnitairePreemptive->setEnabled(true);
    addTacheComposite->setEnabled(true);
    projectTree->setEnabled(true);

    //Construction de l'arborescence du projet
    rootTree = new QTreeWidgetItem(projectTree);
    //Ajout de la racine
    rootTree->setText(0,projetOuvert->getNom());
}
void ProjectWindow::fermerProjet(){
    //ce slot va alors faire apparaitre une fenetre qui se chargera de prevenir
    //l'utilisateur qu'il va quitter la gestion du projet en cours
    //CloseProjectWindow *closeProject = new CloseProjectWindow(this);
    //closeProject->exec();
    int reponse = QMessageBox::question(this, "Fermer Projet", "Etes vous sur de vouloir quitter la gestion de ce projet ?", QMessageBox ::Yes | QMessageBox::No);

        if (reponse == QMessageBox::Yes)
        {
            //MainWindow::libererInstanceProjet();
            /* J'arrive pas a trouver une solution en utilisant
             * libererinstanceProjet bien que je pense que ce soit la facon la plus propre de le faire
             * l'astuce que j'utilise c'est de remettre tous les champs a 0 au niveau de notre
             * projectWindow !
             *
             */
            projectTree->clear();
            projectTree->setDisabled(true);
            nom->clear();
            description->clear();
            dateDispo->clear();
            dateEcheance->clear();
            addTacheComposite->setDisabled(true);
            addTacheUnitaire->setDisabled(true);
            addTacheUnitairePreemptive->setDisabled(true);
            projetOuvert = NULL;
        }
}

void ProjectWindow::fenetreAjouterTacheUnitaire(){
    AddTacheWindow *newTache = new AddTacheWindow(this);
    newTache->exec();
}

void ProjectWindow::modifierTache(){
    ModTacheWindow *modTache = new ModTacheWindow(this);
    modTache->exec();
}

void ProjectWindow::ajouterTache(const Tache &t){
    ProjetManager& m = ProjetManager::getInstance();
    m.getProjet(projetOuvert->getNom())->ajouterTache(t);
    qDebug()<<"tache ajouté au projet "<<t.getTitre()<<"\n";
    //QTreeWidgetItem* tacheTree = new QTreeWidgetItem(t.getTitre());
    //rootTree->addChild(tacheTree);
}





