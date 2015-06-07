#include "programmertachewindow.h"
#include "ui_programmertache.h"
#include "mainwindow.h"

ProgrammerTache::ProgrammerTache(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProgrammerTache)
{
    ui->setupUi(this);
    ui->date->setMinimumDate(QDate::currentDate());
    connect(ui->annuler, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(envoyerProgrammation()));
}

ProgrammerTache::~ProgrammerTache()
{
    delete ui;
}

void ProgrammerTache::envoyerProgrammation(){
    ProjectWindow& pw = MainWindow::getInstanceProjet();
    pw.ajouterProgrammation(ui->date->date(), ui->horaire->time());
    this->close();
}
