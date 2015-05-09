#include "modtachewindow.h"
#include <QDebug>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>



ModTacheWindow::ModTacheWindow(/*Tache& tacheToEdit, */QWidget* parent):
    QDialog(parent)/*,tache(tacheToEdit)*/{
    this->setWindowTitle(QString("Edition de la tache")/*+tacheToEdit.getId()*/);

    QLabel* idLabel = new QLabel("Identificateur",this);
    QLabel* titreLabel =new QLabel("Titre",this);
    QLabel* dispoLabel=new QLabel("Disponibilite",this);
    QLabel* echeanceLabel= new QLabel("Echéance",this);
    QLabel* dureeLabel= new QLabel("durée",this);
    identificateur=new QLineEdit();//(tache.getId(),this);
    titre= new QTextEdit;//(tache.getTitre(),this);
    preemptive= new QCheckBox("preemptive",this);
    //preemptive->setChecked(tache.isPreemptive());
    disponibilite= new QDateEdit;//(tache.getDateDisponibilite(),this);
    echeance = new QDateEdit;//(tache.getDateEcheance(),this);
    hDuree=new QSpinBox(this);
    hDuree->setRange(0,24);hDuree->setSuffix("heure(s)");
   //hDuree->setValue(tache.getDuree().getHeure());
    mDuree=new QSpinBox(this);
    mDuree->setRange(0,59);mDuree->setSuffix("minute(s)");
   // mDuree->setValue(tache.getDuree().getMinute());
    sauver= new QPushButton("Sauver",this);
    annuler= new QPushButton("Annuler",this);
    qDebug()<<"Milieu2 Constructeur";

    QHBoxLayout* coucheH1= new QHBoxLayout;
    coucheH1->addWidget(idLabel);
    coucheH1->addWidget(identificateur);
    coucheH1->addWidget(preemptive);

    QHBoxLayout* coucheH2= new QHBoxLayout;
    coucheH2->addWidget(titreLabel);
    coucheH2->addWidget(titre);

    QHBoxLayout* coucheH3= new QHBoxLayout;
    coucheH3->addWidget(dispoLabel);
    coucheH3->addWidget(disponibilite);
    coucheH3->addWidget(echeanceLabel);
    coucheH3->addWidget(echeance);
    coucheH3->addWidget(dureeLabel);
    coucheH3->addWidget(hDuree);
    coucheH3->addWidget(mDuree);

    QHBoxLayout* coucheH4= new QHBoxLayout;
    coucheH4->addWidget(sauver);
    coucheH4->addWidget(annuler);

    QVBoxLayout* couche= new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);
qDebug()<<"fin constructeur";

    connect(sauver,SIGNAL(clicked()),this,SLOT(sauverTache()));
    connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}

void ModTacheWindow::sauverTache(){
    /*if(
            TacheManager::getInstance().isTacheExistante(identificateur->text())
            &&
            &TacheManager::getInstance().getTache(identificateur->text())!=&tache
            ){
        QMessageBox::warning(this,"Sauvegarde impossible",
                             "Identificateur tache deja existante...");
        return;
    }
    tache.setId(identificateur->text());
    if(preemptive->isChecked()) tache.setPreemptive();
    else tache.setNonPreemptive();
    tache.setTitre(titre->toPlainText());
    tache.setDuree(Duree(hDuree->value(),mDuree->value()));
    tache.setDatesDisponibiliteEcheance(disponibilite->date(),
                                        echeance->date());

    QMessageBox::information(this,"Sauvegarde","Tache sauvegardée ...");*/
}
