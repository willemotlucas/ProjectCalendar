/********************************************************************************
** Form generated from reading UI file 'viewprojectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWPROJECTWINDOW_H
#define UI_VIEWPROJECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ViewProjectWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QTreeWidget *projectTree;
    QFrame *line;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *projectNameEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QPlainTextEdit *projectDescriptionEdit;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QDateEdit *dateDIspoEdit;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QDateEdit *dateEcheanceEdit;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *addTacheComposite;
    QPushButton *addTacheUnitaire;
    QPushButton *addTacheUnitairePreemptive;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ViewProjectWindow)
    {
        if (ViewProjectWindow->objectName().isEmpty())
            ViewProjectWindow->setObjectName(QStringLiteral("ViewProjectWindow"));
        ViewProjectWindow->resize(800, 600);
        centralwidget = new QWidget(ViewProjectWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        projectTree = new QTreeWidget(groupBox);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        projectTree->setHeaderItem(__qtreewidgetitem);
        projectTree->setObjectName(QStringLiteral("projectTree"));
        projectTree->setGeometry(QRect(10, 20, 221, 501));
        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(250, 50, 521, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(250, 80, 521, 441));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        projectNameEdit = new QLineEdit(groupBox_2);
        projectNameEdit->setObjectName(QStringLiteral("projectNameEdit"));

        horizontalLayout_2->addWidget(projectNameEdit);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        projectDescriptionEdit = new QPlainTextEdit(groupBox_2);
        projectDescriptionEdit->setObjectName(QStringLiteral("projectDescriptionEdit"));

        horizontalLayout_3->addWidget(projectDescriptionEdit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_4->addWidget(label_3);

        dateDIspoEdit = new QDateEdit(groupBox_2);
        dateDIspoEdit->setObjectName(QStringLiteral("dateDIspoEdit"));

        horizontalLayout_4->addWidget(dateDIspoEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        dateEcheanceEdit = new QDateEdit(groupBox_2);
        dateEcheanceEdit->setObjectName(QStringLiteral("dateEcheanceEdit"));

        horizontalLayout_5->addWidget(dateEcheanceEdit);


        verticalLayout_2->addLayout(horizontalLayout_5);

        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(250, 20, 521, 25));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        addTacheComposite = new QPushButton(widget);
        addTacheComposite->setObjectName(QStringLiteral("addTacheComposite"));

        horizontalLayout->addWidget(addTacheComposite);

        addTacheUnitaire = new QPushButton(widget);
        addTacheUnitaire->setObjectName(QStringLiteral("addTacheUnitaire"));

        horizontalLayout->addWidget(addTacheUnitaire);

        addTacheUnitairePreemptive = new QPushButton(widget);
        addTacheUnitairePreemptive->setObjectName(QStringLiteral("addTacheUnitairePreemptive"));

        horizontalLayout->addWidget(addTacheUnitairePreemptive);


        verticalLayout->addWidget(groupBox);

        ViewProjectWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ViewProjectWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        ViewProjectWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ViewProjectWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ViewProjectWindow->setStatusBar(statusbar);

        retranslateUi(ViewProjectWindow);

        QMetaObject::connectSlotsByName(ViewProjectWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ViewProjectWindow)
    {
        ViewProjectWindow->setWindowTitle(QApplication::translate("ViewProjectWindow", "MainWindow", 0));
        groupBox->setTitle(QApplication::translate("ViewProjectWindow", "Gestion du projet", 0));
        groupBox_2->setTitle(QApplication::translate("ViewProjectWindow", "D\303\251tails du projet", 0));
        label->setText(QApplication::translate("ViewProjectWindow", "Nom :", 0));
        label_2->setText(QApplication::translate("ViewProjectWindow", "Description : ", 0));
        label_3->setText(QApplication::translate("ViewProjectWindow", "Disponibilit\303\251 : ", 0));
        label_4->setText(QApplication::translate("ViewProjectWindow", "Ech\303\251ance :", 0));
        addTacheComposite->setText(QApplication::translate("ViewProjectWindow", "Ajouter une tache composite", 0));
        addTacheUnitaire->setText(QApplication::translate("ViewProjectWindow", "Ajouter une tache unitaire", 0));
        addTacheUnitairePreemptive->setText(QApplication::translate("ViewProjectWindow", "Ajouter une tache unitaire pr\303\251emptive", 0));
    } // retranslateUi

};

namespace Ui {
    class ViewProjectWindow: public Ui_ViewProjectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWPROJECTWINDOW_H
