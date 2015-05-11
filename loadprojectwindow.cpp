#include "loadprojectwindow.h"
#include "ui_loadprojectwindow.h"
#include "projetmanager.h"

LoadProjectWindow::LoadProjectWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoadProjectWindow)
{
    ui->setupUi(this);
    ProjetManager& m = ProjetManager::getInstance();
    for(ProjetManager::contProjet::const_iterator it = m.getProjets().begin(); it != m.getProjets().end(); ++it){
        ui->ProjectList->addItem((*it)->getNom());
    }
}

LoadProjectWindow::~LoadProjectWindow()
{
    delete ui;
}
