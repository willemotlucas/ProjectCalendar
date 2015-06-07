#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include <QTime>
#include <QDebug>
#include "tache.h"

class TacheUnitaire : public Tache
{
private:
    // Etat de la tache prive ne lui appartient qu'a lui !

    enum Etat {
        PROGRAMMEE,
        NON_COMMENCEE,
        EN_COURS,
        TERMINEE
    };

    friend class TacheManager;
    static const int DUREE_MAX = 12;
    Etat etat;
    void write(const QString& projet) const ;

protected :
            TacheUnitaire(const QString& id, const QString& desc, const QDate& dispo, const QDate& deadline, const QTime& dur, const int& e = 1):Tache(id, desc, dispo, deadline),etat((Etat)e){if(duree < QTime(DUREE_MAX,0)) duree = dur; else throw CalendarException("La durée d'une tâche unitaire ne peut être supérieur à 12h."); }
//    TacheUnitaire(const TacheUnitaire& t);
        const TacheUnitaire& operator=(const TacheUnitaire& f);
        QTime duree;

public:
    virtual ~TacheUnitaire(){}

    //GETTERS AND SETTERS
    const QTime& getDuree() const { return duree; }
    void setEtat(const Etat& e) { etat = e; }
    const Etat& getEtat() const { return etat; }

    //STATES METHODS
    virtual bool isCommencee() const { return etat == EN_COURS; }
    virtual bool isTerminee() const { return etat == TERMINEE; }
    virtual bool isProgrammee() const { return etat == PROGRAMMEE; }
    virtual TacheUnitaire* clone() const {return new TacheUnitaire(*this);}

    virtual void setDateEcheance(const QDate& e){}

};

#endif // TACHEUNITAIRE_H
