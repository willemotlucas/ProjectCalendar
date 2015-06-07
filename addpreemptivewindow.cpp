#include "addpreemtivewindow.h"
#include "projectwindow.h"
#include "tachefactory.h"
#include "tache.h"
#include "tacheunitairepreemptive.h"
#include "mainwindow.h"

#include <QLabel>
#include <QDebug>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>
#include <QMessageBox>

AddPreemptiveWindow::AddPreemptiveWindow(QWidget* parent):QDialog(parent){
    this->setWindowTitle("Nouvelle Tache Preemptive");

    QLabel* idLabel = new QLabel("Identificateur",this);
    QLabel* titreLabel =new QLabel("Titre",this);
    QLabel* dispoLabel=new QLabel("Disponibilite",this);
    QLabel* echeanceLabel= new QLabel("Echéance",this);
    QLabel* dureeLabel= new QLabel("Durée",this);
    identificateur=new QLineEdit;
    titre= new QTextEdit;
    disponibilite= new QDateEdit;
    disponibilite->setDate(QDate::currentDate());
    echeance = new QDateEdit;
    echeance->setDate(QDate::currentDate());
    hDuree=new QSpinBox(this);
    hDuree->setRange(0,24);hDuree->setSuffix("heure(s)");
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

    connect(ok,SIGNAL(clicked()),this,SLOT(envoiTachePreemtive()));
    connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}

void AddPreemptiveWindow::envoiTachePreemtive(){
    try{
        ProjectWindow& pwm = MainWindow::getInstanceProjet();
        TacheFactory& tf = TacheFactory::getInstance();
        Tache& t = dynamic_cast<Tache&>(tf.creerTacheUnitairePreemptive(identificateur->text(), titre->toPlainText(), disponibilite->date(), echeance->date(), QTime(hDuree->value(), mDuree->value())));
        pwm.ajouterTache(t);
        this->close();
    }catch(CalendarException e){
        QMessageBox::information(this,"Information",e.getInfo());
    }

}

//void AddPreemptiveWindow::envoiPreemptive(){
//    try{
//        ProjectWindow& pwm = MainWindow::getInstanceProjet();
//        TacheFactory& tf = TacheFactory::getInstance();
//        Tache& t = dynamic_cast<Tache&>(tf.creerTacheUnitairePreemptive(identificateur->text(), titre->toPlainText(), disponibilite->date(), echeance->date(), QTime(hDuree->value(), mDuree->value())));
//        pwm.ajouterTache(t);
//        this->close();
//    }catch(CalendarException e){
//        QMessageBox::information(this,"Information",e.getInfo());
//    }
//}



