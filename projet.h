#ifndef PROJET_H
#define PROJET_H

#include <QString>
#include <QDate>
#include <vector>
#include "tache.h"

/**
 * @brief Classe Projet
 * Représente un projet
 */
class Projet
{
    /**
     * @brief nom
     * nom du projet
     */
    QString nom;
    /**
     * @brief description
     * description du projet
     */
    QString description;
    /**
     * @brief disponibilite
     * date de disponibilite du projet
     */
    QDate disponibilite;
    /**
     * @brief echeance
     * date d'échéance du projet
     */
    QDate echeance;

    //+Liste des taches du projet
    std::vector<Tache*> taches;

    Projet(const Projet& p);
    Projet& operator=(const Projet&);

    //Appelé par la méthode ajouterTache seulement
    void setDateEcheance(const QDate& d);
public:
    Projet(const QString& n, const QString& desc, const QDate& disp):nom(n), description(desc), disponibilite(disp), echeance(QDate()){}
    ~Projet();
    const QString& getNom() const { return nom; }
    const QString& getDescription() const { return description; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }

    void ajouterTache(const Tache& t);
};

#endif // PROJET_H
