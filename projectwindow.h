#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTreeWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QDateEdit>
#include <QGroupBox>


class ProjectWindow : public QMainWindow
{
    friend class MainWindow;
    Q_OBJECT
public:
    explicit ProjectWindow(QWidget *parent = 0);
    ~ProjectWindow(){}

private:
    void creerBarreOutils();
    void creerActions();
    void creerAffichageProjet();

private:
    QAction* actionNouveauProjet;
    QAction* actionChargerProjet;
    QAction* actionFermerProjet;
    QAction* actionAjouterTache;
    QAction* actionModifierTache;
    QAction* actionAnnulerTache;
    QAction* actionImprimer;
    QAction* actionPrecedent;
    QAction* actionSuivant;

    QGroupBox* gestionDuProjet;
    QTreeWidget* projectTree;
    QPushButton* addTacheComposite;
    QPushButton* addTacheUnitaire;
    QPushButton* addTacheUnitairePreemptive;
    QGroupBox* detailsProjet;
    QLabel* nomProjet;
    QLineEdit* nomProjetEdit;
    QLabel* descriptionProjet;
    QPlainTextEdit* descriptionProjetEdit;
    QLabel* dateDispoProjet;
    QDateEdit* dateDispoProjetEdit;
    QLabel* dateEcheanceProjet;
    QDateEdit* dateEcheanceProjetEdit;


signals:

private slots:
    void nouveauProjet();
    void chargerProjet();
    void ajouterTache();
    void modifierTache();
};

#endif // PROJECTWINDOW_H
