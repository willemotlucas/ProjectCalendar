#ifndef LOADPROJECTWINDOW_H
#define LOADPROJECTWINDOW_H

#include <QDialog>

namespace Ui {
class LoadProjectWindow;
}

class LoadProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadProjectWindow(QWidget *parent = 0);
    ~LoadProjectWindow();
<<<<<<< HEAD
=======

>>>>>>> 853b5e1a054e66e3f789551a22caf38ac12e530d
private:
    Ui::LoadProjectWindow *ui;

private slots:
    void envoiNomProjet();
};

#endif // LOADPROJECTWINDOW_H
