#include "projectwindow.h"
#include "newprojectwindow.h"
#include "addtachewindow.h"
#include "addcompositewindow.h"
#include "modtachewindow.h"
#include "addpreemptivewindow.h"
#include "programmertachewindow.h"
#include "ajouterprogpreemptivewindow.h"
#include "programmationmanager.h"
#include "loadprojectwindow.h"
#include "addsouscompositewindow.h"
#include "addsouspreemptivewindow.h"
#include "addsoustachewindow.h"
#include "mainwindow.h"
#include "tachecomposite.h"
#include "tacheunitaire.h"
#include "tacheunitairepreemptive.h"
#include "projetmanager.h"
#include "calendarwindow.h"
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
    connect(addTacheComposite,SIGNAL(clicked()),this,SLOT(fenetreAjouterTacheComposite()));
    connect(ajouterSousTacheUnitaire,SIGNAL(clicked()),this,SLOT(fenetreAjouterSousTacheUnitaire()));
    connect(ajouterSousTachePreemptive,SIGNAL(clicked()),this,SLOT(fenetreAjouterSousTacheUnitairePreemptive()));
    connect(ajouterSousTacheComposite,SIGNAL(clicked()),this,SLOT(fenetreAjouterSousTacheComposite()));
    connect(supprimer,SIGNAL(clicked()),this,SLOT(supprimerTache()));
    //connect(modifier,SIGNAL(clicked(),this,SLOT(modifierTache()));
}


void ProjectWindow::creerActions(){
    actionNouveauProjet = new QAction("Nouveau",this);
    connect(actionNouveauProjet,SIGNAL(triggered()),this,SLOT(nouveauProjet()));
    actionChargerProjet = new QAction("Charger",this);
    connect(actionChargerProjet, SIGNAL(triggered()), this, SLOT(chargerProjet()));
    actionFermerProjet = new QAction("Fermer",this);
    connect(actionFermerProjet,SIGNAL(triggered()),this,SLOT(fermerProjet()));
    actionImprimer = new QAction("Exporter le projet ouvert en XML",this);
    connect(actionImprimer,SIGNAL(triggered()),this,SLOT(openQFileDialog()));
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
    nom->setDisabled(true);
    QLabel* labelNom = new QLabel("Nom:");
    QHBoxLayout* N = new QHBoxLayout;
    N->addWidget(labelNom);
    N->addWidget(nom);

    description =new QTextEdit;
    description->setDisabled(true);
    QLabel* labelDescription = new QLabel("Description:");
    QHBoxLayout* D = new QHBoxLayout;
    D->addWidget(labelDescription);
    D->addWidget(description);


    dateDispo = new QDateEdit;
    dateDispo->setDisabled(true);
    QLabel* labelDispo = new QLabel("Date Début :");
    QHBoxLayout* Disp = new QHBoxLayout;
    Disp->addWidget(labelDispo);
    Disp->addWidget(dateDispo);


    dateEcheance = new QDateEdit;
    dateEcheance->setDisabled(true);
    QLabel* labelEcheance = new QLabel("Date Echeance :");
    QHBoxLayout* E = new QHBoxLayout;
    E->addWidget(labelEcheance);
    E->addWidget(dateEcheance);

    QVBoxLayout* detProjet = new QVBoxLayout;
    detProjet->addLayout(N);
    detProjet->addLayout(D);
    detProjet->addLayout(Disp);
    detProjet->addLayout(E);

    //Sous groupbox permettant l'ajout de tache dans notre projet
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

    detProjet->addWidget(addTache);


    QGroupBox* detailsProjet = new QGroupBox("Détails du projet");
    detailsProjet->setLayout(detProjet);

    //2ieme groupbox permettant de visionner les details d'une tache dans notre projet
    QLabel* idLabel = new QLabel("Identificateur",this);
    QLabel* titreLabel =new QLabel("Titre",this);
    QLabel* preemptiveLabel = new QLabel("Preemptive",this);
    QLabel* dispoLabel=new QLabel("Disponibilite",this);
    QLabel* echeanceLabel= new QLabel("Echéance",this);
    QLabel* dureeLabel= new QLabel("Durée",this);
    QLabel* dureeRestanteLabel = new QLabel("Durée restante", this);
    idTache=new QLineEdit;
    nomTache= new QTextEdit;
    dateDispoTache= new QDateEdit;
    dateDispoTache->setDate(QDate::currentDate());
    dateEcheanceTache = new QDateEdit;
    dateEcheanceTache->setDate(QDate::currentDate());
    hDureeTache=new QSpinBox(this);
    hDureeTache->setRange(0,24);hDureeTache->setSuffix("heure(s)");
    mDureeTache=new QSpinBox(this);
    mDureeTache->setRange(0,59);mDureeTache->setSuffix("minute(s)");
    hDureeRestante = new QSpinBox(this);
    hDureeRestante->setRange(0,24); hDureeRestante->setSuffix("heure(s)");hDureeRestante->setDisabled(true);
    mDureeRestante = new QSpinBox(this);
    mDureeRestante->setRange(0,59); mDureeRestante->setSuffix("minute(s)");mDureeRestante->setDisabled(true);
    modifier= new QPushButton("Modifier",this);
    supprimer = new QPushButton("Supprimer",this);
    programmer= new QPushButton("Programmer",this);
    tachePreemtive = new QCheckBox;
   

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
    coucheH3->addWidget(dureeRestanteLabel);
    coucheH3->addWidget(hDureeRestante);
    coucheH3->addWidget(mDureeRestante);

    QHBoxLayout* coucheH4= new QHBoxLayout;
    coucheH4->addWidget(modifier);
    coucheH4->addWidget(programmer);
    coucheH4->addWidget(supprimer);

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
    idTache->setDisabled(true);
    nomTache->setDisabled(true);
    dateDispoTache->setDisabled(true);
    dateEcheanceTache->setDisabled(true);
    hDureeTache->setDisabled(true);
    mDureeTache->setDisabled(true);
    modifier->setDisabled(true);
    supprimer->setDisabled(true);
    programmer->setDisabled(true);
    tachePreemtive->setDisabled(true);


    //Assemblage partie droite
    QVBoxLayout* partieDroite = new QVBoxLayout;
    partieDroite->addWidget(detailsProjet);
    partieDroite->addWidget(detailsTache);

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
    chargerTreeView();

    connect(projectTree,SIGNAL(itemClicked(QTreeWidgetItem*,int)),this,SLOT(chargerDetailsTache(QTreeWidgetItem*, int)));
    connect(programmer, SIGNAL(clicked()), this, SLOT(programmerTache()));
}

void ProjectWindow::chargerDetailsTache(QTreeWidgetItem* item, int column){
    if(item->text(0) != projetOuvert->getNom()){
        if(item->parent()->text(0)==projetOuvert->getNom())
            tacheSelectionnee = projetOuvert->getTache(item->text(column));
        else{
            QTreeWidgetItem* papa = item->parent();
            if(papa->parent()->text(0)==projetOuvert->getNom()){
                TacheComposite* tmp = dynamic_cast<TacheComposite*>(projetOuvert->getTache(papa->text(column)));
                tacheSelectionnee = tmp->getSousTache(item->text(0));
            }
            else {
                QTreeWidgetItem* Grandpapa = papa->parent();
                if(Grandpapa->parent()->text(0)==projetOuvert->getNom()){
                    TacheComposite* tmp2 = dynamic_cast<TacheComposite*>(projetOuvert->getTache(Grandpapa->text(0)));
                    TacheComposite* tmp =dynamic_cast<TacheComposite*>(tmp2->getSousTache(papa->text(0)));
                    tacheSelectionnee = tmp->getSousTache(item->text(0));
               }
            }

        }

        //On recherche la tache ayant le meme id dans ce projet
        idTache->setText(tacheSelectionnee->getId());
        nomTache->setPlainText(tacheSelectionnee->getTitre());
        dateDispoTache->setDate(tacheSelectionnee->getDateDisponibilite());
        dateEcheanceTache->setDate(tacheSelectionnee->getDateEcheance());
        programmer->setEnabled(true);
        modifier->setEnabled(true);
        tachePreemtive->setChecked(false);
        ajouterSousTacheComposite->setEnabled(false);
        ajouterSousTachePreemptive->setEnabled(false);
        ajouterSousTacheUnitaire->setEnabled(false);
        supprimer->setEnabled(true);

        if(tacheSelectionnee->getEtat() != 1)
            programmer->setDisabled(true);

        if(typeid(*tacheSelectionnee) == typeid(TacheUnitairePreemptive)){
            TacheUnitairePreemptive* tmp = dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionnee);
            tachePreemtive->setChecked(true);
            hDureeTache->setValue(tmp->getDureeInit().hour());
            mDureeTache->setValue(tmp->getDureeInit().minute());
            qDebug()<<"preemptive avant hour:"<<tmp->getDuree().hour();
            qDebug()<<"preemptive avant minute:"<<tmp->getDuree().minute();
            hDureeRestante->setValue(tmp->getDureeRestante().hour());
            mDureeRestante->setValue(tmp->getDureeRestante().minute());
        }
        else if(typeid(*tacheSelectionnee) == typeid(TacheUnitaire)){
            TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(tacheSelectionnee);
            qDebug()<<"unitaire avant hour:"<<tmp->getDuree().hour();
            qDebug()<<"unitaire avant minute:"<<tmp->getDuree().minute();
            hDureeTache->setValue(tmp->getDuree().hour());
            mDureeTache->setValue(tmp->getDuree().minute());
            if(tmp->getEtat() == 1){
                qDebug()<<"unitaire apres hour:"<<tmp->getDuree().hour();
                qDebug()<<"unitaire apres minute:"<<tmp->getDuree().minute();
                hDureeRestante->setValue(tmp->getDuree().hour());
                mDureeRestante->setValue(tmp->getDuree().minute());
            }
            else
            {
                hDureeRestante->setValue(0);
                mDureeRestante->setValue(0);
            }

        }
        else if(typeid(*tacheSelectionnee) == typeid(TacheComposite)){
            ajouterSousTacheComposite->setEnabled(true);
            ajouterSousTachePreemptive->setEnabled(true);
            ajouterSousTacheUnitaire->setEnabled(true);
        }
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
            modifier->setDisabled(true);
            programmer->setDisabled(true);
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

void ProjectWindow::fenetreAjouterTacheComposite(){
    AddCompositeWindow *newTache = new AddCompositeWindow(this);
    newTache->exec();
}

void ProjectWindow::fenetreAjouterSousTacheUnitaire(){
    AddSousTacheWindow *newTache = new AddSousTacheWindow(this);
    newTache->exec();
}

void ProjectWindow::fenetreAjouterSousTacheUnitairePreemptive(){
    AddSousPreemptiveWindow *newTache = new AddSousPreemptiveWindow(this);
    newTache->exec();
}

void ProjectWindow::fenetreAjouterSousTacheComposite(){
    AddSousCompositeWindow *newTache = new AddSousCompositeWindow(this);
    newTache->exec();
}

void ProjectWindow::modifierTache(){
    ModTacheWindow *modTache = new ModTacheWindow(this);
    modTache->exec();
}

void ProjectWindow::programmerTache(){
    if(typeid(*tacheSelectionnee) == typeid(TacheUnitaire)){
        ProgrammerTache* progTache = new ProgrammerTache(this);
        progTache->exec();
    }
    else if(typeid(*tacheSelectionnee) == typeid(TacheUnitairePreemptive)){
        AjouterProgPreemptiveWIndow* progTache = new AjouterProgPreemptiveWIndow(this);
        progTache->exec();
    }
}

void ProjectWindow::ajouterTache(Tache &t){
    if(t.getId() == "")
        throw CalendarException("L'enregistrement d'une tache avec un id vide est impossible.");
    if(t.getDateDisponibilite() < projetOuvert->getDisponibilite())
        throw CalendarException("La date de disponibilité de la tâche est inférieure à la date de disponibilité du projet");

    ProjetManager& m = ProjetManager::getInstance();
    Projet* p = m.getProjet(projetOuvert->getNom());
    p->ajouterTache(t);

    QTreeWidgetItem* tacheTree = new QTreeWidgetItem();
    tacheTree->setText(0, t.getId());
    dateEcheance->setDate(p->getEcheance());

    if(typeid(t) == typeid(TacheUnitaire) || typeid(t) == typeid(TacheUnitairePreemptive))
        tacheTree->setTextColor(0, Qt::green);
    rootTree->addChild(tacheTree);
}

void ProjectWindow::ajouterSousTache(Tache& t){
    if(t.getId() == "")
        throw CalendarException("L'enregistrement d'une tache avec un id vide est impossible.");

    TacheComposite* tmp = dynamic_cast<TacheComposite*>(tacheSelectionnee);
    tmp->ajouterSousTaches(t);

    QTreeWidgetItem* tacheTree = new QTreeWidgetItem();
    tacheTree->setText(0, t.getId());
    if(typeid(t) == typeid(TacheUnitaire) || typeid(t) == typeid(TacheUnitairePreemptive))
        tacheTree->setTextColor(0,Qt::green);
    projectTree->currentItem()->addChild(tacheTree);
}

void ProjectWindow::ajouterProgrammation(const QDate &d, const QTime &t){
    TacheUnitaire* tmp = dynamic_cast<TacheUnitaire*>(tacheSelectionnee);
    ProgrammationManager& pm = ProgrammationManager::getInstance();
    try{
        pm.ajouterProgrammation(*projetOuvert,*tacheSelectionnee,d,t,tmp->getDuree());
        tmp->setEtat(0);
        projectTree->currentItem()->setTextColor(0,Qt::blue);
        CalendarWindow& cw = MainWindow::getInstanceAgenda();
        cw.displayTasks();
        hDureeRestante->setValue(0);
        mDureeRestante->setValue(0);
    }catch(CalendarException e){
        QMessageBox::warning(this, "Attention", e.getInfo());
    }
}

void ProjectWindow::ajouterProgrammationPreemptive(const QDate &d, const QTime &t, const QTime& duree){
    TacheUnitairePreemptive* tmp = dynamic_cast<TacheUnitairePreemptive*>(tacheSelectionnee);
    if(duree > tmp->getDureeRestante())
        QMessageBox::warning(this, "Attention", "La durée de programmation doit être inférieur à la durée restante de la tache.");

    ProgrammationManager& pm = ProgrammationManager::getInstance();
    try{
        pm.ajouterProgrammation(*projetOuvert, *tmp, d, t, duree);
        tmp->setDureeRestante(duree);
        projectTree->currentItem()->setTextColor(0,Qt::blue);
        CalendarWindow& cw = MainWindow::getInstanceAgenda();
        cw.displayTasks();
        hDureeRestante->setValue(tmp->getDureeRestante().hour());
        mDureeRestante->setValue(tmp->getDureeRestante().minute());
    }catch(CalendarException e){
        QMessageBox::warning(this, "Attention", e.getInfo());
    }
}

void ProjectWindow::chargerTreeView(){
    // Construction de l'arborescence du projet
        rootTree = new QTreeWidgetItem(projectTree);
        //Ajout de la racine
        rootTree->setText(0,projetOuvert->getNom());
        for(std::vector<Tache*>::iterator i = projetOuvert->begin(); i != projetOuvert->end(); ++i){
            QTreeWidgetItem& m = (*i)->chargerTree(projectTree) ;
            rootTree->addChild(&m);
        }
}

void ProjectWindow::supprimerTache(){
    // on appelle le destructeur de notre tache selectionnee
//    Tache* tmp = tacheSelectionnee;
//    delete tmp;
//    projetOuvert->
//    tacheSelectionnee = NULL;
//    projectTree->clear();
//    chargerTreeView();
}

void ProjectWindow::openQFileDialog(){
    if(projetOuvert == NULL)
        QMessageBox::warning(this, "Attention", "Veuillez ouvrir un projet avant d'exporter en XML");
    else{
        QString filename = QFileDialog::getSaveFileName(this, "Export en XML","",tr("Fichier XML (*.xml)"));
        ProgrammationManager& pm = ProgrammationManager::getInstance();
        pm.exportProjectXML(projetOuvert->getNom() ,filename);
    }
}








