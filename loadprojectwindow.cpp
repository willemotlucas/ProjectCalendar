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
    for(ProjetManager::contProjet::iterator it = m.begin(); it != m.end(); ++it){
        ui->ProjectList->addItem((*it)->getNom());
    }
    connect(ui->LoadButton, SIGNAL(accepted()), this, SLOT(envoiNomProjet()));
}

LoadProjectWindow::~LoadProjectWindow()
{
    delete ui;
}

void LoadProjectWindow::envoiNomProjet(){
    ProjectWindow& m = MainWindow::getInstanceProjet();
    if (m.getNomProjet().isEmpty()){
        m.chargerDetailsProjet(ui->ProjectList->currentItem()->text());
        this->close();
    }
    else {
        QMessageBox::information(this,"Information","Veuillez fermer le projet actuel si vous voulez ouvrir un autre projet");
    }
}
