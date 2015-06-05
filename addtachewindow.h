#ifndef ADDTACHEWINDOW_H
#define ADDTACHEWINDOW_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QCheckBox>
#include <QDateEdit>
#include <QTextEdit>
#include <QSpinBox>


class AddTacheWindow : public QDialog
{
public:
    explicit AddTacheWindow(QWidget *parent=0);
    ~AddTacheWindow(){}

private:
    QLineEdit* identificateur;
    QTextEdit* titre;
    QDateEdit* disponibilite;
    QDateEdit* echeance;
    QSpinBox* hDuree;
    QSpinBox* mDuree;
    QPushButton* ok;
    QPushButton* annuler;

private slots:
    void envoiTacheUnitaire();

};

#endif // ADDTACHEWINDOW_H
