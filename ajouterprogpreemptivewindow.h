#ifndef AJOUTERPROGPREEMPTIVEWINDOW_H
#define AJOUTERPROGPREEMPTIVEWINDOW_H

#include <QDialog>

namespace Ui {
class AjouterProgPreemptiveWIndow;
}

class AjouterProgPreemptiveWIndow : public QDialog
{
    Q_OBJECT

public:
    explicit AjouterProgPreemptiveWIndow(QWidget *parent = 0);
    ~AjouterProgPreemptiveWIndow();

private:
    Ui::AjouterProgPreemptiveWIndow *ui;
private slots:
    void envoyerProgrammation();
};

#endif // AJOUTERPROGPREEMPTIVEWINDOW_H
