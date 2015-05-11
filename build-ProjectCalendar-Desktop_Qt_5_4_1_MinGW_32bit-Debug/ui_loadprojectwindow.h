/********************************************************************************
** Form generated from reading UI file 'loadprojectwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOADPROJECTWINDOW_H
#define UI_LOADPROJECTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoadProjectWindow
{
public:
    QDialogButtonBox *LoadButton;
    QListWidget *ProjectList;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *LoadProjectWindow)
    {
        if (LoadProjectWindow->objectName().isEmpty())
            LoadProjectWindow->setObjectName(QStringLiteral("LoadProjectWindow"));
        LoadProjectWindow->resize(254, 343);
        LoadButton = new QDialogButtonBox(LoadProjectWindow);
        LoadButton->setObjectName(QStringLiteral("LoadButton"));
        LoadButton->setGeometry(QRect(80, 300, 161, 32));
        LoadButton->setOrientation(Qt::Horizontal);
        LoadButton->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        ProjectList = new QListWidget(LoadProjectWindow);
        ProjectList->setObjectName(QStringLiteral("ProjectList"));
        ProjectList->setGeometry(QRect(10, 20, 231, 261));
        verticalLayoutWidget = new QWidget(LoadProjectWindow);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(40, 90, 160, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(LoadProjectWindow);
        QObject::connect(LoadButton, SIGNAL(accepted()), LoadProjectWindow, SLOT(accept()));
        QObject::connect(LoadButton, SIGNAL(rejected()), LoadProjectWindow, SLOT(reject()));

        QMetaObject::connectSlotsByName(LoadProjectWindow);
    } // setupUi

    void retranslateUi(QDialog *LoadProjectWindow)
    {
        LoadProjectWindow->setWindowTitle(QApplication::translate("LoadProjectWindow", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class LoadProjectWindow: public Ui_LoadProjectWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOADPROJECTWINDOW_H
