#include "addcompositewindow.h"
#include "tachefactory.h"
#include "tache.h"
#include "tachecomposite.h"
#include "projectwindow.h"
#include "mainwindow.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTime>
#include <QMessageBox>


AddCompositeWindow::AddCompositeWindow(QWidget* parent):QDialog(parent){
    this->setWindowTitle("Nouvelle Tache Composite");

    QLabel* idLabel = new QLabel("Identificateur",this);
    QLabel* titreLabel =new QLabel("Titre",this);
    QLabel* dispoLabel=new QLabel("Disponibilite",this);
    identificateur=new QLineEdit;
    titre= new QTextEdit;
    disponibilite= new QDateEdit;
    disponibilite->setDate(QDate::currentDate());
    disponibilite->setMinimumDate(QDate::currentDate());
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

    QHBoxLayout* coucheH4= new QHBoxLayout;
    coucheH4->addWidget(ok);
    coucheH4->addWidget(annuler);

    QVBoxLayout* couche= new QVBoxLayout;
    couche->addLayout(coucheH1);
    couche->addLayout(coucheH2);
    couche->addLayout(coucheH3);
    couche->addLayout(coucheH4);

    setLayout(couche);

    connect(ok,SIGNAL(clicked()),this,SLOT(envoiTacheComposite()));
    connect(annuler,SIGNAL(clicked()),this,SLOT(close()));
}

void AddCompositeWindow::envoiTacheComposite(){
    try{
        ProjectWindow& pwm = MainWindow::getInstanceProjet();
        TacheFactory& tf = TacheFactory::getInstance();
        Tache& t = dynamic_cast<Tache&>(tf.creerTacheComposite(identificateur->text(), titre->toPlainText(), disponibilite->date()));
        pwm.ajouterTache(t);
        this->close();
    }catch(CalendarException e){
        QMessageBox::information(this,"Information",e.getInfo());
    }
}


