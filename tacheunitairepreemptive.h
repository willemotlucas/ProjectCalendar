#ifndef TACHEUNITAIREPREEMPTIVE_H
#define TACHEUNITAIREPREEMPTIVE_H

#include <QTime>
#include "tacheunitaire.h"

class TacheUnitairePreemptive : public TacheUnitaire
{
public:
    ~TacheUnitairePreemptive(){}
    QDomElement& write(QDomDocument* dom);
    QTreeWidgetItem& chargerTreeTache(QTreeWidget* tree);

    //STATES METHODS
    bool isProgrammee() const { return etat == PROGRAMMEE; }

    //GETTERS AND SETTERS
    const QTime& getDureeInit() const { return dureeInitiale; }
    const QTime& getDureeRestante() const { return dureeRestante; }
    void setDureeRestante(const QTime& duree){
        int hour = dureeRestante.hour() - duree.hour();
        int minute = dureeRestante.minute() - duree.minute();
        dureeRestante = QTime(hour, minute);
        if(hour == 0 && minute == 0)
            etat = (Etat)2;
    }
    void setEtat(const int& e){ etat = (Etat)e; }
    const int& getEtat() const { return (int)etat;}
    void setDateEcheance(const QDate& e){}

private:
    QTime dureeInitiale;
    QTime dureeRestante;

    friend class TacheFactory;
    TacheUnitairePreemptive(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, const QTime& durInit, const QTime& durRest, const int& e = 1):
            TacheUnitaire(id, t, dispo, deadline,QTime(0,0), e),dureeInitiale(durInit),dureeRestante(durRest){}
    TacheUnitairePreemptive(const TacheUnitairePreemptive& t);
    const TacheUnitairePreemptive& operator=(const TacheUnitairePreemptive& t);

};

#endif // TACHEUNITAIREPREEMPTIVE_H
