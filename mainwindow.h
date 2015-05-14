#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QKeySequence>
#include <QTabWidget>
#include <QAction>
#include "agendawindow.h"
#include "projectwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        static ProjectWindow& getInstanceProjet();
        static void libererInstanceProjet();

    private:
        void creerMenus();
        void creerActions();
        void creerBarreNavigation();
        static ProjectWindow* projet;
        QWidget* pageCalendar;
        QWidget* pageProjet;


    private:
        QTabWidget* onglets;

        QAction* actionNouveauProjet;
        QAction* actionChargerProjet;
        QAction* actionFermerProjet;
        QAction* actionAfficherAgenda;
        QAction* actionImprimerProjet;
        QAction* actionImprimerAgenda;
        QAction* actionQuitter;
        QAction* actionAPropos;
        QAction* actionAProposQt;
        QAction* actionPrecedente;
        QAction* actionSuivante;



    private slots:
        void aPropos();

};

#endif // MAINWINDOW_H
