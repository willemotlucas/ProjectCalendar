#ifndef EVENEMENTDUREE_H
#define EVENEMENTDUREE_H

#include <QDate>
#include <QTime>
#include "duree.h"
#include "evenement.h"

class EvenementDuree : public Evenement
{
    QTime horaire;
    Duree duree;
public:
    EvenementDuree(const QDate& d, const QString desc, const QTime& h, const Duree& dur):Evenement(d,desc),horaire(h), duree(dur){}
    const QTime& getHoraire() const { return horaire; }
    const Duree& getDuree() const { return duree; }
    virtual ~EvenementDuree();
};

#endif // EVENEMENTDUREE_H
