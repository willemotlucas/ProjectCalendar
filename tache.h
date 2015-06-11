#ifndef TACHE_H
#define TACHE_H

#include <QDate>
#include <QString>
#include <QTextStream>
#include <QDomDocument>
#include <QTreeWidget>

#include "calendarexception.h"
#include "duree.h"

class Tache {

protected:
    enum Etat{
        PROGRAMMEE,
        PROGRAMMABLE,
        NON_PROGRAMMABLE
    };

    QString identificateur;
    QString titre;
    QDate disponibilite;
    QDate echeance;
    Etat etat;

    Tache(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, unsigned int e):
            identificateur(id),titre(t),disponibilite(dispo),echeance(deadline),etat((Etat)e){}
    //Constructeur de tache sans deadline pour les taches composites : la deadline est la borne supérieur des sous-tâches de la tache composite.
    Tache(const QString& id, const QString& t, const QDate& dispo, unsigned int e):
            identificateur(id),titre(t),disponibilite(dispo),etat((Etat)e){}
//    Tache(const Tache& t);
    Tache& operator=(const Tache&);


    virtual QDomElement& write(QDomDocument* dom)= 0;
    virtual QTreeWidgetItem& chargerTreeTache(QTreeWidget* tree)=0;

public:
    QDomElement& save(QDomDocument* dom) {return write(dom);}
    QTreeWidgetItem& chargerTree(QTreeWidget* tree){return chargerTreeTache(tree);}
    //DESTRUCTOR
    virtual ~Tache(){};

    //GETTERS et SETTERS
    QString getId() const { return identificateur; }
    void setId(const QString& str);
    QString getTitre() const { return titre; }
    void setTitre(const QString& str) { titre=str; }
    QDate getDateDisponibilite() const {  return disponibilite; }
    void setDateDisponibiltie(QDate dispo) { disponibilite = dispo; }
    QDate getDateEcheance() const {  return echeance; }
    virtual void setEtat(unsigned int e) = 0;
    virtual unsigned int getEtat() const = 0;

    //ABSTRACT METHODS

    //Peut-être mettre en privée pour que seul le TacheManager puisse gérer la date d'échéance d'une tache composite en fonction
    //De ses sous-taches. Mettre en abstrait pour changer le fonctionnement en fonction de la classe fille
//        if (e<disp) throw CalendarException("erreur T�che : date ech�ance < date disponibilit�");
//        disponibilite=disp; echeance=e;
    virtual void setDateEcheance(const QDate& e) = 0;


};

QTextStream& operator<<(QTextStream& f, const Tache& t);

#endif // TACHE_H
