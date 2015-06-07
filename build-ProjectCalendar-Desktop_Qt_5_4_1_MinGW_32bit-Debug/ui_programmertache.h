/********************************************************************************
** Form generated from reading UI file 'programmertache.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMMERTACHE_H
#define UI_PROGRAMMERTACHE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgrammerTache
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDateEdit *date;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QTimeEdit *horaire;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *annuler;
    QPushButton *ok;

    void setupUi(QDialog *ProgrammerTache)
    {
        if (ProgrammerTache->objectName().isEmpty())
            ProgrammerTache->setObjectName(QStringLiteral("ProgrammerTache"));
        ProgrammerTache->resize(307, 143);
        widget = new QWidget(ProgrammerTache);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 12, 291, 121));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        date = new QDateEdit(widget);
        date->setObjectName(QStringLiteral("date"));

        horizontalLayout->addWidget(date);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horaire = new QTimeEdit(widget);
        horaire->setObjectName(QStringLiteral("horaire"));

        horizontalLayout_2->addWidget(horaire);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        annuler = new QPushButton(widget);
        annuler->setObjectName(QStringLiteral("annuler"));

        horizontalLayout_3->addWidget(annuler);

        ok = new QPushButton(widget);
        ok->setObjectName(QStringLiteral("ok"));

        horizontalLayout_3->addWidget(ok);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(ProgrammerTache);

        QMetaObject::connectSlotsByName(ProgrammerTache);
    } // setupUi

    void retranslateUi(QDialog *ProgrammerTache)
    {
        ProgrammerTache->setWindowTitle(QApplication::translate("ProgrammerTache", "Dialog", 0));
        label->setText(QApplication::translate("ProgrammerTache", "Date de la programmation :", 0));
        label_2->setText(QApplication::translate("ProgrammerTache", "Heure de d\303\251but :", 0));
        annuler->setText(QApplication::translate("ProgrammerTache", "Annuler", 0));
        ok->setText(QApplication::translate("ProgrammerTache", "OK", 0));
    } // retranslateUi

};

namespace Ui {
    class ProgrammerTache: public Ui_ProgrammerTache {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMMERTACHE_H
