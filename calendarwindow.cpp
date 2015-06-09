#include "calendarwindow.h"
#include "ui_calendarwindow.h"
#include "programmationmanager.h"
#include "tacheunitaire.h"

#include <QDebug>
#include <QDate>
#include "typeinfo"

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

    displayTasks();

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
    effacerAffichageTaches();
    displayTasks();
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

void CalendarWindow::displayTasks(){
    ProgrammationManager& progm = ProgrammationManager::getInstance();

    //On enregistre le premier jour et le dernier jour de la semaine affichée
    QDate premierJour = QDate::fromString(ui->agenda_widget->horizontalHeaderItem(0)->text(), Qt::TextDate);
    QDate dernierJour = QDate::fromString(ui->agenda_widget->horizontalHeaderItem(6)->text(), Qt::TextDate);

    //On parcourt chaque programmation pour choisir lesquelles afficher
    for(std::vector<Programmation*>::iterator it = progm.begin(); it != progm.end(); ++it){
        //Si la programmation est comprise dans la semaine
        if((*it)->getDate() >= premierJour && (*it)->getDate() <= dernierJour)
        {
            int column = (*it)->getDate().day() - premierJour.day();
            if(typeid((*it)->getTache()) == typeid(TacheUnitaire)){
                const TacheUnitaire& tmp = dynamic_cast<const TacheUnitaire&>((*it)->getTache());
                int firstLine = (*it)->getHoraire().hour()-6;
                int nbLine = tmp.getDuree().hour();
                for(int i = firstLine; i < firstLine+nbLine; i++){
                    ui->agenda_widget->setItem(i, column, new QTableWidgetItem((*it)->getTache().getId()));
                    ui->agenda_widget->item(i, column)->setBackgroundColor(Qt::red);
                }
            }
        }
    }
}

void CalendarWindow::effacerAffichageTaches(){
    for(int i = 0; i < ui->agenda_widget->rowCount(); i++){
        for(int j = 0; j < ui->agenda_widget->columnCount(); j++){
            if(ui->agenda_widget->item(i,j) == NULL)
                ui->agenda_widget->setItem(i,j,new QTableWidgetItem());

            ui->agenda_widget->item(i,j)->setBackgroundColor(Qt::white);
            ui->agenda_widget->item(i,j)->setText("");
        }
    }
}

