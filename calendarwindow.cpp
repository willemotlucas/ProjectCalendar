#include "calendarwindow.h"
#include "ui_calendarwindow.h"

CalendarWindow::CalendarWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CalendarWindow)
{
    dialog = NULL;
    ui->setupUi(this);
    agenda_widget = ui->agenda_widget;
    agenda_widget->horizontalHeader()->setStyleSheet("background: white;");
    agenda_widget->verticalHeader()->setStyleSheet("background: white;");
    agenda_widget->verticalHeader()->setDefaultAlignment(Qt::AlignTop);

    today = QDate::currentDate();
    currentDate = QDate::currentDate();

    changeCurrentWeek(&today, true);

    QString formatter = QString("d MMM yyyy");
    for (int i = -500; i < 500; i++) {
        ui->choose_week->addItem(today.addDays(i*7 - (today.dayOfWeek()-1)).toString(formatter)+" - "+today.addDays(i*7 - (today.dayOfWeek()-1) + 6).toString(formatter));
    }
    ui->choose_week->setCurrentIndex(500);
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
    qDebug()<<"added "<<QString::number((num-500)*7)<< " jours";
    changeCurrentWeek(&currentDate, today == currentDate);
}
/*

/**
 * @brief MainWindow::changeCurrentWeek Change la tableau (de la semaine) affiché actuellement
 * @param date
 * @param isCurrentDay
 */


void CalendarWindow::changeCurrentWeek(QDate* date, bool isCurrentDay) {
    int dayOfWeek = date->dayOfWeek();
    int counter = -dayOfWeek;
    QString formatter = QString("ddd d MMM");
    for (int i = 0 ; i<7; i++) {
        counter++;
        QString toShow;
        agenda_widget->horizontalHeaderItem(i)->setText(date->addDays(counter).toString(formatter));
    }
    QFont font;
    if (isCurrentDay)
        font.setBold(true);

    agenda_widget->horizontalHeaderItem(dayOfWeek-1)->setFont(font);
}

void CalendarWindow::resizeEvent(QResizeEvent *event) {
    qDebug()<<"RESIZE EVENT ";
    resizeAgendaTable();

    CalendarWindow::resizeEvent(event);
}

void CalendarWindow::show()
{
    CalendarWindow::show();
    resizeAgendaTable();
}

void CalendarWindow::resizeAgendaTable() const {
    const int width = agenda_widget->width() - agenda_widget->verticalHeader()->width() - 20;
    const int height = agenda_widget->height() - agenda_widget->horizontalHeader()->height() - 10;
    unsigned int columnCount = agenda_widget->columnCount();
    unsigned int rowCount    = agenda_widget->rowCount();
    for (unsigned int i = 0; i < columnCount; ++i)
        agenda_widget->setColumnWidth(i, width/columnCount);

    for (unsigned int i = 0; i < rowCount; ++i)
        agenda_widget->setRowHeight(i, (2*height)/rowCount);
}

void CalendarWindow::cellClicked(int row, int column) {
    qDebug()<<"Click cell "<<row<<" ; "<<column;
    //dialog->setSelectedDate(currentDate.addDays(1-currentDate.dayOfWeek()+column));
    QTime a(row,0);
    //dialog->setStartTime(a);
    connect(dialog, SIGNAL(finished(int)), this, SLOT(detruireNouvelEvent()));
    dialog->show();
}


void CalendarWindow::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);
}

void CalendarWindow::detruireNouvelEvent() {
    //delete dialog;
    dialog = 0;
}

CalendarWindow::~CalendarWindow()
{
    qDebug()<<"CalendarWindow detruite";
    delete dialog;
    delete ui;
}
