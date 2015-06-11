/********************************************************************************
** Form generated from reading UI file 'ajouterprogpreemptivewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AJOUTERPROGPREEMPTIVEWINDOW_H
#define UI_AJOUTERPROGPREEMPTIVEWINDOW_H

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

class Ui_AjouterProgPreemptiveWIndow
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QDateEdit *date;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QTimeEdit *horaire;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QTimeEdit *duree;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *ok;
    QPushButton *annuler;

    void setupUi(QDialog *AjouterProgPreemptiveWIndow)
    {
        if (AjouterProgPreemptiveWIndow->objectName().isEmpty())
            AjouterProgPreemptiveWIndow->setObjectName(QStringLiteral("AjouterProgPreemptiveWIndow"));
        AjouterProgPreemptiveWIndow->resize(366, 198);
        layoutWidget = new QWidget(AjouterProgPreemptiveWIndow);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 341, 161));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        date = new QDateEdit(layoutWidget);
        date->setObjectName(QStringLiteral("date"));

        horizontalLayout->addWidget(date);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        horaire = new QTimeEdit(layoutWidget);
        horaire->setObjectName(QStringLiteral("horaire"));

        horizontalLayout_2->addWidget(horaire);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        duree = new QTimeEdit(layoutWidget);
        duree->setObjectName(QStringLiteral("duree"));

        horizontalLayout_3->addWidget(duree);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        ok = new QPushButton(layoutWidget);
        ok->setObjectName(QStringLiteral("ok"));

        horizontalLayout_4->addWidget(ok);

        annuler = new QPushButton(layoutWidget);
        annuler->setObjectName(QStringLiteral("annuler"));

        horizontalLayout_4->addWidget(annuler);


        verticalLayout->addLayout(horizontalLayout_4);


        retranslateUi(AjouterProgPreemptiveWIndow);

        QMetaObject::connectSlotsByName(AjouterProgPreemptiveWIndow);
    } // setupUi

    void retranslateUi(QDialog *AjouterProgPreemptiveWIndow)
    {
        AjouterProgPreemptiveWIndow->setWindowTitle(QApplication::translate("AjouterProgPreemptiveWIndow", "Programmation d'une tache pr\303\251emptive", 0));
        label->setText(QApplication::translate("AjouterProgPreemptiveWIndow", "Date de la programmation :", 0));
        label_2->setText(QApplication::translate("AjouterProgPreemptiveWIndow", "Heure de d\303\251but :", 0));
        label_3->setText(QApplication::translate("AjouterProgPreemptiveWIndow", "Dur\303\251e du d\303\251coupage de la t\303\242che :", 0));
        ok->setText(QApplication::translate("AjouterProgPreemptiveWIndow", "OK", 0));
        annuler->setText(QApplication::translate("AjouterProgPreemptiveWIndow", "Annuler", 0));
    } // retranslateUi

};

namespace Ui {
    class AjouterProgPreemptiveWIndow: public Ui_AjouterProgPreemptiveWIndow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AJOUTERPROGPREEMPTIVEWINDOW_H
