#ifndef AGENDAWINDOW_H
#define AGENDAWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QCalendarWidget>
#include <QTableWidget>


class AgendaWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit AgendaWindow(QWidget *parent = 0);
    ~AgendaWindow(){}

private:
    void creerBarreOutils();
    void creerActions();


private:
    QTableWidget* calendrier;

    QAction* actionAjouterTache;
    QAction* actionAnnulerTache;
    QAction* actionImprimer;
    QAction* actionPrecedent;
    QAction* actionSuivant;


signals:

public slots:
};

#endif // AGENDAWINDOW_H
