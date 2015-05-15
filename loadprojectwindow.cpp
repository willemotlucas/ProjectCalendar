#include "loadprojectwindow.h"
#include "ui_loadprojectwindow.h"
#include "projetmanager.h"
#include "mainwindow.h"
#include <QMessageBox>

LoadProjectWindow::LoadProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadProjectWindow)
{
    ui->setupUi(this);
    ProjetManager& m = ProjetManager::getInstance();
    for(ProjetManager::contProjet::const_iterator it = m.getProjets().begin(); it != m.getProjets().end(); ++it){
        ui->ProjectList->addItem((*it)->getNom());
    }
    connect(ui->LoadButton, SIGNAL(accepted()), this, SLOT(envoiNomProjet()));
    connect(ui->LoadButton, SIGNAL(accepted()), this, SLOT(close()));
}

LoadProjectWindow::~LoadProjectWindow()
{
    delete ui;
}

void LoadProjectWindow::envoiNomProjet(){
    ProjectWindow& m = MainWindow::getInstanceProjet();
    if (m.getNomProjet().isEmpty()){
        m.chargerDetailsProjet(ui->ProjectList->currentItem()->text());
    }
    else {
        QMessageBox::information(this,"Information","Veuillez fermer le projet actuel si vous voulez ouvrir un autre projet");
    }
}
