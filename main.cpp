#include "mainwindow.h"
#include "calendarexception.h"
#include "duree.h"
#include "programmationmanager.h"
#include "projetmanager.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
//    try{

//    TacheManager& m=TacheManager::getInstance();
//    m.load("taches.dat");
//    m.ajouterTache("AW1","Partage des scenarii",Duree(1,30),QDate(1,1,2015),QDate(1,9,2015));
//    m.ajouterTache("AW2","Identification des competences",Duree(2,30),QDate(1,1,2015),QDate(1,12,2015));
//    m.save("taches.dat");

//    }catch(CalendarException e){
//        //Warning : with QString use .toStdString() to have a string !!
//        cout<<e.getInfo().toStdString()<<endl;
//    }

//    try {
//        ProjetManager& m = ProjetManager::getInstance();
//        m.load("projets.dat");
//        m.ajouterProjet("Projet4", "Test création projet", QDate(1,9,2015));
//        m.save("projets.dat");
//    }catch(CalendarException e){
//        cout<<e.getInfo().toStdString()<<endl;
//    }

//    system("pause");
//    return 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

}
