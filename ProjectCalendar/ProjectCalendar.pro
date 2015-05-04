#-------------------------------------------------
#
# Project created by QtCreator 2015-05-04T15:01:07
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProjectCalendar
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    duree.cpp \
    tache.cpp \
    programmation.cpp \
    programmationmanager.cpp \
    tachemanager.cpp

HEADERS  += mainwindow.h \
    duree.h \
    tache.h \
    programmation.h \
    calendarexception.h \
    programmationmanager.h \
    tachemanager.h

FORMS    += mainwindow.ui
