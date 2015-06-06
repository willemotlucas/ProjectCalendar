#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include <QTime>
#include <QDebug>
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

    ~TacheUnitaire(){}

    //GETTERS AND SETTERS
    const QTime& getDuree() const { return duree; }
    void setEtat(const Etat& e) { etat = e; }
    const Etat& getEtat() const { return etat; }

    //STATES METHODS
    bool isCommencee() const { return etat == EN_COURS; }
    bool isTerminee() const { return etat == TERMINEE; }
    bool isProgrammee() const { return etat == PROGRAMMEE; }
    TacheUnitaire* clone() const {return new TacheUnitaire(*this);}

    void setDateEcheance(const QDate& e){}
private:
    friend class TacheManager;
    static const int DUREE_MAX = 12;
    Etat etat;
    QTime duree;

    TacheUnitaire(const QString& id, const QString& desc, const QDate& dispo, const QDate& deadline, const QTime& dur):Tache(id, desc, dispo, deadline),etat(NON_COMMENCEE){if(duree < QTime(DUREE_MAX,0)) duree = dur; else throw CalendarException("La durée d'une tâche unitaire ne peut être supérieur à 12h."); }
//    TacheUnitaire(const TacheUnitaire& t);
    const TacheUnitaire& operator=(const TacheUnitaire& f);
    void write(const QString& projet) const ;
};

#endif // TACHEUNITAIRE_H
