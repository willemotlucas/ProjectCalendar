#ifndef PROJECTWINDOW_H
#define PROJECTWINDOW_H

#include <QMainWindow>
#include <QAction>


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

signals:

private slots:
    void nouveauProjet();
    void ajouterTache();
    void modifierTache();
};

#endif // PROJECTWINDOW_H
