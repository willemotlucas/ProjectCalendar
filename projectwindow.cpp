#include "projectwindow.h"
#include "newprojectwindow.h"
#include "addtachewindow.h"
#include "modtachewindow.h"
#include "addpreemptivewindow.h"
#include "loadprojectwindow.h"
#include "mainwindow.h"
#include "projetmanager.h"
#include "tachemanager.h"
#include "tachecomposite.h"
#include "tacheunitaire.h"
#include "tacheunitairepreemptive.h"
#include "global.h"
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <typeinfo>


ProjectWindow::ProjectWindow(QWidget *parent) : QMainWindow(parent)
{
    //Generation des widgets de la fenetre agenda
    creerActions();
    creerBarreOutils();
    creerAffichageProjet();
    projetOuvert = NULL;

    connect(addTacheUnitaire,SIGNAL(clicked()),this,SLOT(fenetreAjouterTacheUnitaire()));
    connect(addTacheUnitairePreemptive,SIGNAL(clicked()),this,SLOT(fenetreAjouterTacheUnitairePreemptive()));
    connect(projectTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(chargerDetailsTache(QTreeWidgetItem*, int)));

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

    //2ieme groupbox permettant de visionner les details d'une tache dans notre projet
    QLabel* idLabel = new QLabel("Identificateur",this);
    QLabel* titreLabel =new QLabel("Titre",this);
    QLabel* preemptiveLabel = new QLabel("Preemptive",this);
    QLabel* dispoLabel=new QLabel("Disponibilite",this);
    QLabel* echeanceLabel= new QLabel("Echéance",this);
    QLabel* dureeLabel= new QLabel("Durée",this);
    idTache=new QLineEdit;
    idTache->setDisabled(true);
    nomTache= new QTextEdit;
    nomTache->setDisabled(true);
    dateDispoTache= new QDateEdit;
    dateDispoTache->setDate(QDate::currentDate());
    dateDispoTache->setDisabled(true);
    dateEcheanceTache = new QDateEdit;
    dateEcheanceTache->setDate(QDate::currentDate());
    dateEcheanceTache->setDisabled(true);
    hDureeTache=new QSpinBox(this);
    hDureeTache->setRange(0,24);hDureeTache->setSuffix("heure(s)");
    hDureeTache->setDisabled(true);
    mDureeTache=new QSpinBox(this);
    mDureeTache->setRange(0,59);mDureeTache->setSuffix("minute(s)");
    mDureeTache->setDisabled(true);
    modifier= new QPushButton("Modifier",this);
    modifier->setDisabled(true);
    programmer= new QPushButton("Programmer",this);
    programmer->setDisabled(true);
    tachePreemtive = new QCheckBox;
    tachePreemtive->setDisabled(true);
   

    QHBoxLayout* coucheH1= new QHBoxLayout;
    coucheH1->addWidget(idLabel);
    coucheH1->addWidget(idTache);
    coucheH1->addWidget(preemptiveLabel);
    coucheH1->addWidget(tachePreemtive);

    QHBoxLayout* coucheH2= new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(nomTache);

    QHBoxLayout* coucheH3= new QHBoxLayout;
    coucheH3->addWidget(dispoLabel);
    coucheH3->addWidget(dateDispoTache);
    coucheH3->addWidget(echeanceLabel);
    coucheH3->addWidget(dateEcheanceTache);
    coucheH3->addWidget(dureeLabel);
    coucheH3->addWidget(hDureeTache);
    coucheH3->addWidget(mDureeTache);

    QHBoxLayout* coucheH4= new QHBoxLayout;
    coucheH4->addWidget(modifier);
    coucheH4->addWidget(programmer);

    ajouterSousTacheUnitaire = new QPushButton("Sous-Tache Unitaire");
    ajouterSousTacheUnitaire->setDisabled(true);
    ajouterSousTachePreemptive = new QPushButton("Sous-Tache Preemptive");
    ajouterSousTachePreemptive->setDisabled(true);
    ajouterSousTacheComposite = new QPushButton("Sous-Tache Composite");
    ajouterSousTacheComposite->setDisabled(true);

    QHBoxLayout* addSousT = new QHBoxLayout;
    addSousT->addWidget(ajouterSousTacheUnitaire);
    addSousT->addWidget(ajouterSousTachePreemptive);
    addSousT->addWidget(ajouterSousTacheComposite);

    QVBoxLayout* couche= new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);
    couche->addLayout(addSousT);

    QGroupBox* detailsTache = new QGroupBox("Details Tache Selectionnée");
    detailsTache->setLayout(couche);

    //3ieme groupbox permettant l'ajout de tache dans notre projet
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
    partieDroite->addWidget(detailsTache);
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
    for(Projet::contTache::iterator it = projetOuvert->begin(); it != projetOuvert->end(); ++it)
    {
        QTreeWidgetItem* tacheTree = new QTreeWidgetItem();
        qDebug()<<"ajout tache arborescence : "<<(*it)->getId()<<"\n";
        qDebug()<<"titre = "<<(*it)->getTitre();
        qDebug()<<"dispo = "<<(*it)->getDateDisponibilite().toString();
        qDebug()<<"echeance = "<<(*it)->getDateEcheance().toString();
        tacheTree->setText(0, (*it)->getId());
        rootTree->addChild(tacheTree);
    }
}

void ProjectWindow::chargerDetailsTache(QTreeWidgetItem* item, int column){
    Tache& tacheSelectionne = projetOuvert->getTache(item->text(column));

    //On recherche la tache ayant le meme id dans ce projet
    idTache->setText(tacheSelectionne.getId());
    nomTache->setPlainText(tacheSelectionne.getTitre());
    dateDispoTache->setDate(tacheSelectionne.getDateDisponibilite());
    dateEcheanceTache->setDate(tacheSelectionne.getDateEcheance());
    modifier->setEnabled(true);
    programmer->setEnabled(true);//Pour le moment

    if(typeid(tacheSelectionne)==typeid(TacheUnitairePreemptive)){
        tachePreemtive->setChecked(true);
    }
    else if(typeid(tacheSelectionne)==typeid(TacheComposite)){
        ajouterSousTacheComposite->setEnabled(true);
        ajouterSousTachePreemptive->setEnabled(true);
        ajouterSousTacheUnitaire->setEnabled(true);
    }
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

void ProjectWindow::fenetreAjouterTacheUnitairePreemptive(){
    AddPreemptiveWindow *newTache = new AddPreemptiveWindow(this);
    newTache->exec();
}

void ProjectWindow::modifierTache(){
    ModTacheWindow *modTache = new ModTacheWindow(this);
    modTache->exec();
}

void ProjectWindow::ajouterTache(Tache &t){
    ProjetManager& m = ProjetManager::getInstance();
    Projet* p = m.getProjet(projetOuvert->getNom());
    p->ajouterTache(t);
    QTreeWidgetItem* tacheTree = new QTreeWidgetItem();
    tacheTree->setText(0, t.getId());
    rootTree->addChild(tacheTree);
    t.save(projetOuvert->getNom());
}






