#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T15:01:07
#
#-------------------------------------------------

QT       += core gui xml
QT += xml


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectCalendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    duree.cpp \
    tache.cpp \
    programmation.cpp \
    programmationmanager.cpp \
    tachemanager.cpp \
    iterator.cpp \
    evenement.cpp \
    evenementduree.cpp \
    projet.cpp \
    projetmanager.cpp \
    addtachewindow.cpp \
    agendawindow.cpp \
    modtachewindow.cpp \
    newprojectwindow.cpp \
    projectwindow.cpp

HEADERS  += mainwindow.h \
    duree.h \
    tache.h \
    programmation.h \
    calendarexception.h \
    programmationmanager.h \
    tachemanager.h \
    iterator.h \
    evenement.h \
    evenementduree.h \
    projet.h \
    projetmanager.h \
    addtachewindow.h \
    agendawindow.h \
    modtachewindow.h \
    newprojectwindow.h \
    projectwindow.h \
    global.h

FORMS    += mainwindow.ui
