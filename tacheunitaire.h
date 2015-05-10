#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include <QTime>
#include "tache.h"

class TacheUnitaire : public Tache
{

public:

    enum Etat {
        PROGRAMMEE,
        NON_COMMENCEE,
        EN_COURS,
        TERMINEE
    };

    ~TacheUnitaire();

    //GETTERS AND SETTERS
    const QTime& getDuree() const { return duree; }
    void setEtat(const Etat& e) { etat = e; }
    const Etat& getEtat() const { return etat; }

    //STATES METHODS
    bool isCommencee() const { return etat == EN_COURS; }
    bool isTerminee() const { return etat == TERMINEE; }
    bool isProgrammee() const { return etat == PROGRAMMEE; }

    void setDateEcheance(const QDate& e);


private:
    static const int DUREE_MAX = 12;
    Etat etat;
    QTime duree;

    friend class TacheManager;
    TacheUnitaire(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, const QTime& dur):
        Tache(id, t, dispo, deadline){ etat = NON_COMMENCEE; if(duree < QTime(DUREE_MAX,0)) duree = dur; else throw CalendarException("La durée de la tâche ne peut être supérieur à 12h."); }
};

#endif // TACHEUNITAIRE_H
