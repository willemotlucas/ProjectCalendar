#ifndef LOADPROJECTWINDOW_H
#define LOADPROJECTWINDOW_H

#include <QDialog>

namespace Ui {
class LoadProjectWindow;
}

class LoadProjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoadProjectWindow(QWidget *parent = 0);
    ~LoadProjectWindow();

private:
    Ui::LoadProjectWindow *ui;

private slots:
};

#endif // LOADPROJECTWINDOW_H
