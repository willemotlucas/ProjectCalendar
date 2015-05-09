#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDate>
#include <vector>
#include "tache.h"

class Projet
{
    QString nom;
    QString description;
    QDate disponibilite;
    QDate echeance;

    //+Liste des taches du projet
    //std::vector<Tache> taches;

    Projet(const Projet& p);
    Projet& operator=(const Projet&);
public:
    Projet(const QString& n, const QString& desc, const QDate& disp):nom(n), description(desc), disponibilite(disp), echeance(QDate()){}
    ~Projet();
    const QString& getNom() const { return nom; }
    const QString& getDescription() const { return description; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }

    //+Calcul date echance
    //+AjouterTacheProjet()
    //+

};

#endif // PROJET_H
