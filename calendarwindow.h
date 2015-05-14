#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QLineEdit>
#include <QDate>
#include <string>
#include <QString>
#include <QMessageBox>
#include <QDebug>


namespace Ui {
class CalendarWindow;
}

class CalendarWindow : public QMainWindow
{
    Q_OBJECT

    private:
        // Widgets
        Ui::CalendarWindow *ui;
        QTableWidget* agenda_widget;
        QDate today;
        QDate currentDate;

        // Fonctions
        void resizeEvent(QResizeEvent *event) override;
        void closeEvent(QCloseEvent *event) override;
        void changeCurrentWeek(QDate* date, bool isCurrentDay);
        void resizeAgendaTable() const;


    public:
        explicit CalendarWindow(QWidget *parent = 0);
        void showInfo(QString titre, QString description) {
            QMessageBox::information(this, titre, description);
        }
        ~CalendarWindow();

    public Q_SLOTS:
        void show();
        void cellClicked(int row, int column);
        void nextWeek();
        void prevWeek();
        void setWeek(int num);
        void detruireNouvelEvent();
};

#endif // CALENDARWINDOW_H

