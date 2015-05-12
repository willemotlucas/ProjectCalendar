#ifndef LOADPROJECTWINDOW_H
#define LOADPROJECTWINDOW_H

#include <QDialog>
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
    const Projet& getLoadedProject();

private:
    Ui::LoadProjectWindow *ui;

};

#endif // LOADPROJECTWINDOW_H
