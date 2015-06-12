#include "addtachewindow.h"
#include "tachefactory.h"
#include "tache.h"
#include "tacheunitaire.h"
#include "projectwindow.h"
#include "mainwindow.h"

#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>
#include <QMessageBox>

AddTacheWindow::AddTacheWindow(QWidget* parent):QDialog(parent){
    this->setWindowTitle("Nouvelle Tache Unitaire");

    QLabel* idLabel = new QLabel("Identificateur",this);
    QLabel* titreLabel =new QLabel("Titre",this);
    QLabel* dispoLabel=new QLabel("Disponibilite",this);
    QLabel* echeanceLabel= new QLabel("Echéance",this);
    QLabel* dureeLabel= new QLabel("Durée (inf a 12h)",this);
    identificateur=new QLineEdit;
    titre= new QTextEdit;
    disponibilite= new QDateEdit;
    disponibilite->setDate(QDate::currentDate());
    disponibilite->setMinimumDate(QDate::currentDate());
    echeance = new QDateEdit;
    echeance->setDate(QDate::currentDate());
    echeance->setMinimumDate(QDate::currentDate());
    connect(disponibilite, SIGNAL(dateChanged(QDate)), echeance, SLOT(setDate(QDate)));
    hDuree=new QSpinBox(this);
    hDuree->setRange(0,12);hDuree->setSuffix("heure(s)");
    mDuree=new QSpinBox(this);
    mDuree->setRange(0,59);mDuree->setSuffix("minute(s)");
    ok= new QPushButton("OK",this);
    annuler= new QPushButton("Annuler",this);

    QHBoxLayout* coucheH1= new QHBoxLayout;
    coucheH1->addWidget(idLabel);
    coucheH1->addWidget(identificateur);

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
    coucheH4->addWidget(ok);
    coucheH4->addWidget(annuler);

    QVBoxLayout* couche= new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);


    connect(ok,SIGNAL(clicked()),this,SLOT(envoiTacheUnitaire()));
    connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}

void AddTacheWindow::envoiTacheUnitaire(){
    try{
        if(disponibilite->date() <= echeance->date()){
            ProjectWindow& pwm = MainWindow::getInstanceProjet();
            TacheFactory& tf = TacheFactory::getInstance();
            Tache& t = dynamic_cast<Tache&>(tf.creerTacheUnitaire(identificateur->text(), titre->toPlainText(), disponibilite->date(), echeance->date(), QTime(hDuree->value(), mDuree->value())));
            pwm.ajouterTache(t);
            this->close();
        }
        else
            QMessageBox::warning(this,"Attention", "La date d'échéance doit être supérieure à la date de disponibilité.");
    }catch(CalendarException e){
        QMessageBox::information(this,"Information",e.getInfo());
    }
}



