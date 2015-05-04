#ifndef PROGRAMMATION_H
#define PROGRAMMATION_H

#include <QDate>
#include <QTime>
#include "calendarexception.h"

class Programmation {
    const Tache* tache;
    QDate date;
    QTime horaire;
public:
    Programmation(const Tache& t, const QDate& d, const QTime& h):tache(&t), date(d), horaire(h){}
    const Tache& getTache() const { return *tache; }
    QDate getDate() const { return date; }
    QTime getHoraire() const { return horaire; }
};

class ProgrammationManager {
private:
    Programmation** programmations;
    unsigned int nb;
    unsigned int nbMax;
    void addItem(Programmation* t);
    Programmation* trouverProgrammation(const Tache& t) const;
public:
    ProgrammationManager();
    ~ProgrammationManager();
    ProgrammationManager(const ProgrammationManager& um);
    ProgrammationManager& operator=(const ProgrammationManager& um);
    void ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h);
};

#endif // PROGRAMMATION_H
