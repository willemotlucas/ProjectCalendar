#ifndef TACHE_H
#define TACHE_H

#include <QDate>
#include <QString>
#include <QTextStream>

#include "calendarexception.h"
#include "duree.h"

class Tache {
    QString identificateur;
    QString titre;
    Duree duree;
    QDate disponibilite;
    QDate echeance;
    bool preemptive;
    Tache(const QString& id, const QString& t, const Duree& dur, const QDate& dispo, const QDate& deadline, bool preempt=false):
            identificateur(id),titre(t),duree(dur),disponibilite(dispo),echeance(deadline),preemptive(preempt){}
    Tache(const Tache& t);
    Tache& operator=(const Tache&);
    friend class TacheManager;
public:
    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    Duree getDuree() const { return duree; }
    void setDuree(const Duree& d) { duree=d; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    QDate getDateEcheance() const {  return echeance; }
    void setDatesDisponibiliteEcheance(const QDate& disp, const QDate& e) {
        if (e<disp) throw CalendarException("erreur T�che : date ech�ance < date disponibilit�");
        disponibilite=disp; echeance=e;
    }
    bool isPreemptive() const { return preemptive; }
    void setPreemptive() { preemptive=true; }
    void setNonPreemptive() { preemptive=false; }
};

QTextStream& operator<<(QTextStream& f, const Tache& t);

#endif // TACHE_H
