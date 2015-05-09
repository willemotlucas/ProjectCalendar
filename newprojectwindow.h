#ifndef NEWPROJECTWINDOW_H
#define NEWPROJECTWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QDateEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class NewProjectWindow : public QDialog
{
    Q_OBJECT
public:
    explicit NewProjectWindow(QWidget *parent = 0);
    ~NewProjectWindow(){}

private:
    QLineEdit* nom;
    QDateEdit* dateDispo;
    QDateEdit* dateEcheance;
    QTextEdit* description;
    QPushButton* ok;
    QPushButton* annuler;

signals:

public slots:
private slots:
    void creationNouveauProjet();
};

#endif // NEWPROJECTWINDOW_H
