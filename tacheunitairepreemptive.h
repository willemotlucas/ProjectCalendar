#ifndef TACHEUNITAIREPREEMPTIVE_H
#define TACHEUNITAIREPREEMPTIVE_H

#include <QTime>
#include "tacheunitaire.h"

class TacheUnitairePreemptive : public TacheUnitaire
{
public:

    enum Etat {
        PROGRAMMEE,
        NON_COMMENCEE,
        COMMENCEE,
        INTERROMPUE,
        REPRISE,
        TERMINEE
    };


    ~TacheUnitairePreemptive(){}
    void write(const QString& type, const QString &id) const;

    //STATES METHODS
    bool isCommencee() const { return (etat != NON_COMMENCEE && etat != PROGRAMMEE) ; }
    bool isTerminee() const { return etat == TERMINEE; }
    bool isProgrammee() const { return etat == PROGRAMMEE; }
    bool isInterrompue() const { return etat == INTERROMPUE; }
    bool isReprise() const { return etat == REPRISE; }

    void interrompre(); //Enregistrement de la préemption dans le vector
    void reprendre();

    //GETTERS AND SETTERS
    const QTime& getDureeInit() const { return dureeInitiale; }
    const QTime& getDureeRestante() const { return dureeRestante; }
    void setEtat(const Etat& e){ etat = e; }
    const Etat& getEtat() const { return etat; }

    void setDateEcheance(const QDate& e){}

private:
    QTime dureeInitiale;
    QTime dureeRestante;
    Etat etat;

    friend class TacheFactory;
    TacheUnitairePreemptive(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, const QTime& dur, const int& e = 1):
            TacheUnitaire(id, t, dispo, deadline,QTime(0,0)),etat((Etat)e),dureeInitiale(dur),dureeRestante(dur){}
    TacheUnitairePreemptive(const TacheUnitairePreemptive& t);
    const TacheUnitairePreemptive& operator=(const TacheUnitairePreemptive& t);

};

#endif // TACHEUNITAIREPREEMPTIVE_H
