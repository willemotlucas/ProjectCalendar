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
    tachemanager.cpp \
    programmationmanager.cpp

HEADERS  += mainwindow.h \
    calendarexception.h \
    tachemanager.h \
    programmationmanager.h

FORMS    += mainwindow.ui
