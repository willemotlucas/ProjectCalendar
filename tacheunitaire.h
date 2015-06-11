#ifndef TACHEUNITAIRE_H
#define TACHEUNITAIRE_H

#include <QTime>
#include <QDebug>
#include "tache.h"

class TacheUnitaire : public Tache
{
private:
    // Etat de la tache prive ne lui appartient qu'a lui !

    friend class TacheFactory;
    static const int DUREE_MAX = 12;
    QTime duree;
    QDomElement& write(QDomDocument* dom);
    QTreeWidgetItem& chargerTreeTache(QTreeWidget* tree);

protected :
            TacheUnitaire(const QString& id, const QString& desc, const QDate& dispo, const QDate& deadline, const QTime& dur, unsigned int e = 1):Tache(id, desc, dispo, deadline,e){if(duree < QTime(DUREE_MAX,0)) duree = dur; else throw CalendarException("La durée d'une tâche unitaire ne peut être supérieur à 12h."); }
//    TacheUnitaire(const TacheUnitaire& t);
        const TacheUnitaire& operator=(const TacheUnitaire& f);

public:
    virtual ~TacheUnitaire(){}

    //GETTERS AND SETTERS
    const QTime& getDuree() const { return duree; }
    virtual void setEtat(unsigned int e) { etat = (Etat)e; }
    virtual unsigned int getEtat() const { return (unsigned int)etat; }

    //STATES METHODS
    virtual bool isProgrammee() const { return etat == PROGRAMMEE; }

    virtual void setDateEcheance(const QDate& e){}

};

#endif // TACHEUNITAIRE_H
