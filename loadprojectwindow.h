#ifndef LOADPROJECTWINDOW_H
#define LOADPROJECTWINDOW_H

#include <QDialog>
#include <QString>
#include "projet.h"

namespace Ui {
class LoadProjectWindow;
}

class LoadProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadProjectWindow(QWidget *parent = 0);
    ~LoadProjectWindow();
private:
    Ui::LoadProjectWindow *ui;

private slots:
    void envoiNomProjet();
};

#endif // LOADPROJECTWINDOW_H
