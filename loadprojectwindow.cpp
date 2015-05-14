#include "loadprojectwindow.h"
#include "ui_loadprojectwindow.h"
#include "projetmanager.h"
#include "mainwindow.h"
#include "projectwindow.h"
#include "projet.h"
#include <QDebug>

LoadProjectWindow::LoadProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadProjectWindow)
{
    ui->setupUi(this);
    ProjetManager& m = ProjetManager::getInstance();
    for(ProjetManager::contProjet::const_iterator it = m.getProjets().begin(); it != m.getProjets().end(); ++it){
        ui->ProjectList->addItem((*it)->getNom());
    }
    connect(ui->LoadButton, SIGNAL(accepted()),this, SLOT(envoiNomProjet()));
    //connect(ui->LoadButton,SIGNAL(accepted()),&MainWindow::getInstanceProjet(),SLOT(chargerDetailsProjet(ui->ProjectList->currentItem()->text())));
}
/*
 * Au final faire ce slot ne sert absolument a rien
 * On veut pouvoir savoir quel projet charge alors pk ne
 * pas tout simplement modifier la fonction
 * getinstanceprojet(), en getinstanceprojet(Qstring nomProjet)
 * Ainsi il sera quel projet charge au clic du bouton ok !*/

void LoadProjectWindow::envoiNomProjet(){
    qDebug()<<ui->ProjectList->currentItem()->text();
    MainWindow::getInstanceProjet().chargerDetailsProjet(ui->ProjectList->currentItem()->text());
}



LoadProjectWindow::~LoadProjectWindow()
{
    delete ui;
}
