#ifndef CALENDARWINDOW_H
#define CALENDARWINDOW_H

#include <QMainWindow>
#include <QDate>

namespace Ui {
class CalendarWindow;
}

class CalendarWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CalendarWindow(QWidget *parent = 0);
    ~CalendarWindow();

private:
    Ui::CalendarWindow *ui;
    QDate today;
    QDate currentDate;

private slots:
    void changeCurrentWeek(QDate* date, bool isCurrentDay);
    void nextWeek();
    void prevWeek();
    void setWeek(int num);
};

#endif // CALENDARWINDOW_H
