#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //histoire de rajouter un truc de merde
    w.show();

    return a.exec();
}
