#include "mainwindow.h"
#include "calendarexception.h"
#include "programmationmanager.h"
#include "projetmanager.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
