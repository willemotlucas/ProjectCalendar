#include "ajouterprogpreemptivewindow.h"
#include "projectwindow.h"
#include "ui_ajouterprogpreemptivewindow.h"
#include "mainwindow.h"

AjouterProgPreemptiveWIndow::AjouterProgPreemptiveWIndow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AjouterProgPreemptiveWIndow)
{
    ui->setupUi(this);
    ui->date->setMinimumDate(QDate::currentDate());
    connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(envoyerProgrammation()));
}

AjouterProgPreemptiveWIndow::~AjouterProgPreemptiveWIndow()
{
    delete ui;
}

void AjouterProgPreemptiveWIndow::envoyerProgrammation(){
    ProjectWindow& pw = MainWindow::getInstanceProjet();
    pw.ajouterProgrammationPreemptive(ui->date->date(), ui->horaire->time(), ui->duree->time());
    this->close();
}
