/********************************************************************************
** Form generated from reading UI file 'calendarwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CALENDARWINDOW_H
#define UI_CALENDARWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CalendarWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *previous_week;
    QComboBox *choose_week;
    QPushButton *next_week;
    QTableWidget *agenda_widget;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *CalendarWindow)
    {
        if (CalendarWindow->objectName().isEmpty())
            CalendarWindow->setObjectName(QStringLiteral("CalendarWindow"));
        CalendarWindow->resize(1006, 605);
        centralwidget = new QWidget(CalendarWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 50, 981, 501));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        previous_week = new QPushButton(layoutWidget);
        previous_week->setObjectName(QStringLiteral("previous_week"));

        horizontalLayout->addWidget(previous_week);

        choose_week = new QComboBox(layoutWidget);
        choose_week->setObjectName(QStringLiteral("choose_week"));

        horizontalLayout->addWidget(choose_week);

        next_week = new QPushButton(layoutWidget);
        next_week->setObjectName(QStringLiteral("next_week"));

        horizontalLayout->addWidget(next_week);


        verticalLayout->addLayout(horizontalLayout);

        agenda_widget = new QTableWidget(layoutWidget);
        if (agenda_widget->columnCount() < 7)
            agenda_widget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        agenda_widget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        agenda_widget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        agenda_widget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        agenda_widget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        agenda_widget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        agenda_widget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        agenda_widget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        if (agenda_widget->rowCount() < 23)
            agenda_widget->setRowCount(23);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(6, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(7, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(8, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(9, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(10, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(11, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(12, __qtablewidgetitem19);
        QTableWidgetItem *__qtablewidgetitem20 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(13, __qtablewidgetitem20);
        QTableWidgetItem *__qtablewidgetitem21 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(14, __qtablewidgetitem21);
        QTableWidgetItem *__qtablewidgetitem22 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(15, __qtablewidgetitem22);
        QTableWidgetItem *__qtablewidgetitem23 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(16, __qtablewidgetitem23);
        QTableWidgetItem *__qtablewidgetitem24 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(17, __qtablewidgetitem24);
        QTableWidgetItem *__qtablewidgetitem25 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(18, __qtablewidgetitem25);
        QTableWidgetItem *__qtablewidgetitem26 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(19, __qtablewidgetitem26);
        QTableWidgetItem *__qtablewidgetitem27 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(20, __qtablewidgetitem27);
        QTableWidgetItem *__qtablewidgetitem28 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(21, __qtablewidgetitem28);
        QTableWidgetItem *__qtablewidgetitem29 = new QTableWidgetItem();
        agenda_widget->setVerticalHeaderItem(22, __qtablewidgetitem29);
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        QTableWidgetItem *__qtablewidgetitem30 = new QTableWidgetItem();
        __qtablewidgetitem30->setBackground(brush);
        agenda_widget->setItem(1, 1, __qtablewidgetitem30);
        agenda_widget->setObjectName(QStringLiteral("agenda_widget"));
        agenda_widget->horizontalHeader()->setDefaultSectionSize(131);

        verticalLayout->addWidget(agenda_widget);

        CalendarWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(CalendarWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1006, 21));
        CalendarWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(CalendarWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        CalendarWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(CalendarWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        CalendarWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(CalendarWindow);

        QMetaObject::connectSlotsByName(CalendarWindow);
    } // setupUi

    void retranslateUi(QMainWindow *CalendarWindow)
    {
        CalendarWindow->setWindowTitle(QApplication::translate("CalendarWindow", "MainWindow", 0));
        previous_week->setText(QApplication::translate("CalendarWindow", "Pr\303\251c\303\251dent", 0));
        next_week->setText(QApplication::translate("CalendarWindow", "Suivant", 0));
        QTableWidgetItem *___qtablewidgetitem = agenda_widget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CalendarWindow", "Lundi", 0));
        QTableWidgetItem *___qtablewidgetitem1 = agenda_widget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("CalendarWindow", "Mardi", 0));
        QTableWidgetItem *___qtablewidgetitem2 = agenda_widget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("CalendarWindow", "Mercredi", 0));
        QTableWidgetItem *___qtablewidgetitem3 = agenda_widget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("CalendarWindow", "Jeudi", 0));
        QTableWidgetItem *___qtablewidgetitem4 = agenda_widget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("CalendarWindow", "Vendredi", 0));
        QTableWidgetItem *___qtablewidgetitem5 = agenda_widget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("CalendarWindow", "Samedi", 0));
        QTableWidgetItem *___qtablewidgetitem6 = agenda_widget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("CalendarWindow", "Dimanche", 0));
        QTableWidgetItem *___qtablewidgetitem7 = agenda_widget->verticalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("CalendarWindow", "06h00", 0));
        QTableWidgetItem *___qtablewidgetitem8 = agenda_widget->verticalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("CalendarWindow", "07h00", 0));
        QTableWidgetItem *___qtablewidgetitem9 = agenda_widget->verticalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("CalendarWindow", "08h00", 0));
        QTableWidgetItem *___qtablewidgetitem10 = agenda_widget->verticalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("CalendarWindow", "09h00", 0));
        QTableWidgetItem *___qtablewidgetitem11 = agenda_widget->verticalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("CalendarWindow", "10h00", 0));
        QTableWidgetItem *___qtablewidgetitem12 = agenda_widget->verticalHeaderItem(5);
        ___qtablewidgetitem12->setText(QApplication::translate("CalendarWindow", "11h00", 0));
        QTableWidgetItem *___qtablewidgetitem13 = agenda_widget->verticalHeaderItem(6);
        ___qtablewidgetitem13->setText(QApplication::translate("CalendarWindow", "12h00", 0));
        QTableWidgetItem *___qtablewidgetitem14 = agenda_widget->verticalHeaderItem(7);
        ___qtablewidgetitem14->setText(QApplication::translate("CalendarWindow", "13h00", 0));
        QTableWidgetItem *___qtablewidgetitem15 = agenda_widget->verticalHeaderItem(8);
        ___qtablewidgetitem15->setText(QApplication::translate("CalendarWindow", "14h00", 0));
        QTableWidgetItem *___qtablewidgetitem16 = agenda_widget->verticalHeaderItem(9);
        ___qtablewidgetitem16->setText(QApplication::translate("CalendarWindow", "15h00", 0));
        QTableWidgetItem *___qtablewidgetitem17 = agenda_widget->verticalHeaderItem(10);
        ___qtablewidgetitem17->setText(QApplication::translate("CalendarWindow", "16h00", 0));
        QTableWidgetItem *___qtablewidgetitem18 = agenda_widget->verticalHeaderItem(11);
        ___qtablewidgetitem18->setText(QApplication::translate("CalendarWindow", "17h00", 0));
        QTableWidgetItem *___qtablewidgetitem19 = agenda_widget->verticalHeaderItem(12);
        ___qtablewidgetitem19->setText(QApplication::translate("CalendarWindow", "18h00", 0));
        QTableWidgetItem *___qtablewidgetitem20 = agenda_widget->verticalHeaderItem(13);
        ___qtablewidgetitem20->setText(QApplication::translate("CalendarWindow", "19h00", 0));
        QTableWidgetItem *___qtablewidgetitem21 = agenda_widget->verticalHeaderItem(14);
        ___qtablewidgetitem21->setText(QApplication::translate("CalendarWindow", "20h00", 0));
        QTableWidgetItem *___qtablewidgetitem22 = agenda_widget->verticalHeaderItem(15);
        ___qtablewidgetitem22->setText(QApplication::translate("CalendarWindow", "21h00", 0));
        QTableWidgetItem *___qtablewidgetitem23 = agenda_widget->verticalHeaderItem(16);
        ___qtablewidgetitem23->setText(QApplication::translate("CalendarWindow", "22h00", 0));
        QTableWidgetItem *___qtablewidgetitem24 = agenda_widget->verticalHeaderItem(17);
        ___qtablewidgetitem24->setText(QApplication::translate("CalendarWindow", "00h00", 0));
        QTableWidgetItem *___qtablewidgetitem25 = agenda_widget->verticalHeaderItem(18);
        ___qtablewidgetitem25->setText(QApplication::translate("CalendarWindow", "01h00", 0));
        QTableWidgetItem *___qtablewidgetitem26 = agenda_widget->verticalHeaderItem(19);
        ___qtablewidgetitem26->setText(QApplication::translate("CalendarWindow", "02h00", 0));
        QTableWidgetItem *___qtablewidgetitem27 = agenda_widget->verticalHeaderItem(20);
        ___qtablewidgetitem27->setText(QApplication::translate("CalendarWindow", "03h00", 0));
        QTableWidgetItem *___qtablewidgetitem28 = agenda_widget->verticalHeaderItem(21);
        ___qtablewidgetitem28->setText(QApplication::translate("CalendarWindow", "04h00", 0));
        QTableWidgetItem *___qtablewidgetitem29 = agenda_widget->verticalHeaderItem(22);
        ___qtablewidgetitem29->setText(QApplication::translate("CalendarWindow", "05h00", 0));

        const bool __sortingEnabled = agenda_widget->isSortingEnabled();
        agenda_widget->setSortingEnabled(false);
        agenda_widget->setSortingEnabled(__sortingEnabled);

        toolBar->setWindowTitle(QApplication::translate("CalendarWindow", "toolBar", 0));
    } // retranslateUi

};

namespace Ui {
    class CalendarWindow: public Ui_CalendarWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CALENDARWINDOW_H
