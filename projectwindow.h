#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QTreeWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
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
    //boutons barre outils
    QAction* actionNouveauProjet;
    QAction* actionChargerProjet;
    QAction* actionFermerProjet;
    QAction* actionImprimer;
    QAction* actionPrecedent;
    QAction* actionSuivant;


    //Arbre view et bouton d'ajout de taches
    QTreeWidget* projectTree;
    QPushButton* addTacheComposite;
    QPushButton* addTacheUnitaire;
    QPushButton* addTacheUnitairePreemptive;

    //Description de notre tache
    QLineEdit* nom;
    QTextEdit* description;
    QDateEdit* dateDispo;
    QDateEdit* dateEcheance;


signals:

private slots:
    void nouveauProjet();
    void chargerProjet();
    void ajouterTacheComposite(){}
    void ajouterTacheUnitaire(){}
    void ajouterTacheUnitairePreemptive(){}
    void modifierTache();

public:
    void chargerDetailsProjet(QString nomProjet);
};

#endif // PROJECTWINDOW_H
