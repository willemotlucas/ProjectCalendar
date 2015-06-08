#ifndef TACHE_H
#define TACHE_H

#include <QDate>
#include <QString>
#include <QTextStream>

#include "calendarexception.h"
#include "duree.h"

class Tache {

protected:
    friend class TacheManager;
    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;
//    std::vector<Tache*> precedence;

    Tache(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline):
            identificateur(id),titre(t),disponibilite(dispo),echeance(deadline){}
    //Constructeur de tache sans deadline pour les taches composites : la deadline est la borne supérieur des sous-tâches de la tache composite.
    Tache(const QString& id, const QString& t, const QDate& dispo):
            identificateur(id),titre(t),disponibilite(dispo){}
//    Tache(const Tache& t);
    Tache& operator=(const Tache&);


    virtual void write(const QString& type, const QString& id) const  = 0;

public:
        void save(const QString& type, const QString& id) const {write(type, id);}
    //DESTRUCTOR
    virtual ~Tache(){}

    //GETTERS et SETTERS
    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    void setDateDisponibiltie(QDate dispo) { disponibilite = dispo; }
    QDate getDateEcheance() const {  return echeance; }


    //ABSTRACT METHODS
    virtual bool isCommencee() const = 0;
    virtual bool isTerminee() const = 0;

    //Peut-être mettre en privée pour que seul le TacheManager puisse gérer la date d'échéance d'une tache composite en fonction
    //De ses sous-taches. Mettre en abstrait pour changer le fonctionnement en fonction de la classe fille
//        if (e<disp) throw CalendarException("erreur T�che : date ech�ance < date disponibilit�");
//        disponibilite=disp; echeance=e;
    virtual void setDateEcheance(const QDate& e) = 0;


};

QTextStream& operator<<(QTextStream& f, const Tache& t);

#endif // TACHE_H
