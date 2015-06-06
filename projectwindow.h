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

#include "projet.h"

class ProjectWindow : public QMainWindow
{
    friend class MainWindow;
    Q_OBJECT
public:
    explicit ProjectWindow(QWidget *parent = 0);
    QString getNomProjet() const{
        return nom->text();
    }
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
    QTreeWidgetItem* rootTree;
    QPushButton* addTacheComposite;
    QPushButton* addTacheUnitaire;
    QPushButton* addTacheUnitairePreemptive;

    //Description de notre tache
    QLineEdit* nom;
    QTextEdit* description;
    QDateEdit* dateDispo;
    QDateEdit* dateEcheance;

    Projet* projetOuvert;
signals:

private slots:
    void nouveauProjet();
    void chargerProjet();
    void fenetreAjouterTacheComposite(){}
    void fenetreAjouterTacheUnitaire();
    void fenetreAjouterTacheUnitairePreemptive(){}
    void modifierTache();
    void fermerProjet();

public:
    void chargerDetailsProjet(const QString& nomProjet);
    void ajouterTache(const Tache& t);
};

#endif // PROJECTWINDOW_H
