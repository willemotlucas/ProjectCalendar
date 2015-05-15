#include "calendarwindow.h"
#include "ui_calendarwindow.h"

#include <QDebug>
#include <QDate>

CalendarWindow::CalendarWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalendarWindow)
{
    ui->setupUi(this);
    today = QDate::currentDate();
    currentDate = QDate::currentDate();
    changeCurrentWeek(&today, true);

    QString formatter = QString("d MMM yyyy");
    for (int i = -500; i < 500; i++) {
        ui->choose_week->addItem(today.addDays(i*7 - (today.dayOfWeek()-1)).toString(Qt::TextDate)+" - "+today.addDays(i*7 - (today.dayOfWeek()-1) + 6).toString(Qt::TextDate));
    }
    ui->choose_week->setCurrentIndex(500);


    connect(ui->next_week, SIGNAL(clicked()), this, SLOT(nextWeek()));
    connect(ui->previous_week, SIGNAL(clicked()), this, SLOT(prevWeek()));
    connect(ui->choose_week, SIGNAL(currentIndexChanged(int)), this, SLOT(setWeek(int)));
}

CalendarWindow::~CalendarWindow()
{
    delete ui;
}

void CalendarWindow::changeCurrentWeek(QDate* date, bool isCurrentDay){
    int dayOfWeek = QDate::currentDate().dayOfWeek();
    int counter = -dayOfWeek;
    QString formatter = QString("ddd d MMM");
    for (int i = 0 ; i<7; i++) {
        counter++;
        QString toShow;
        ui->agenda_widget->horizontalHeaderItem(i)->setText(date->addDays(counter).toString(Qt::TextDate));
    }
    QFont font;
    if (isCurrentDay)
        font.setBold(true);

    ui->agenda_widget->horizontalHeaderItem(dayOfWeek-1)->setFont(font);
}

void CalendarWindow::nextWeek() {
    currentDate = currentDate.addDays(7);
    changeCurrentWeek(&currentDate, today == currentDate);
    ui->choose_week->setCurrentIndex(ui->choose_week->currentIndex()+1);
}

void CalendarWindow::prevWeek() {
    currentDate = currentDate.addDays(-7);
    changeCurrentWeek(&currentDate, today == currentDate);
    ui->choose_week->setCurrentIndex(ui->choose_week->currentIndex()-1);
}

void CalendarWindow::setWeek(int num) {
    currentDate = today.addDays((num-500)*7);
    changeCurrentWeek(&currentDate, today == currentDate);
}

