#ifndef MODTACHEWINDOW_H
#define MODTACHEWINDOW_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QCheckBox>
#include <QDateEdit>
#include <QPushButton>

class ModTacheWindow : public QDialog
{
public:
    explicit ModTacheWindow(QWidget *parent=0);
    ~ModTacheWindow(){}

private :
    Q_OBJECT
    //Tache& tache;

    QLineEdit* identificateur;
    QTextEdit* titre;
    QCheckBox* preemptive;
    QDateEdit* disponibilite;
    QDateEdit* echeance;
    QSpinBox* hDuree;
    QSpinBox* mDuree;
    QPushButton* sauver;
    QPushButton* annuler;

private slots :
    void sauverTache();
};

#endif // MODTACHEWINDOW_H
