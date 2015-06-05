#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include <QTime>
#include "tache.h"

class TacheUnitairePreemptive : public Tache
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
    TacheUnitairePreemptive* clone() const {return new TacheUnitairePreemptive(*this);}

    //STATES METHODS
    bool isCommencee() const { return (etat != NON_COMMENCEE && etat != PROGRAMMEE) ; }
    bool isTerminee() const { return etat == TERMINEE; }
    bool isProgrammee() const { return etat == PROGRAMMEE; }
    bool isInterrompue() const { return etat == INTERROMPUE; }
    bool isReprise() const { return etat == REPRISE; }

    void interrompre(); //Enregistrement de la préemption dans le vector
    void reprendre();

    //GETTERS AND SETTERS
    const QTime& getDuree() const { return duree; }
    void setEtat(const Etat& e){ etat = e; }
    const Etat& getEtat() const { return etat; }

    void setDateEcheance(const QDate& e);

private:
    QTime duree;
    Etat etat;

    friend class TacheManager;
    TacheUnitairePreemptive(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, const QTime& dur):
            Tache(id, t, dispo, deadline), duree(dur){ etat = NON_COMMENCEE; }
    TacheUnitairePreemptive(const TacheUnitairePreemptive& t);
    const TacheUnitairePreemptive& operator=(const TacheUnitairePreemptive& t);

    //Une tache préemptive peut être effectuée en plusieurs fois. Les découpages de la tache seront donc
    //enregistrée dans le vector de préemption et ajouté au fur et à mesure de l'avancée de la tâche
//    std::vector<Preemption*> preemptions;
};

#endif // TACHEUNITAIRE_H
