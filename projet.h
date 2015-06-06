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
public:
    typedef std::vector<Tache*> contTache;
    ~Projet();
    const QString& getNom() const { return nom; }
    const QString& getDescription() const { return description; }
    const QDate& getDisponibilite() const { return disponibilite; }
    const QDate& getEcheance() const { return echeance; }

    void ajouterTache(const Tache& t);

    contTache::iterator begin(){return taches.begin();}
    contTache::iterator end(){return taches.end();}

private:
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
    contTache taches;

    Projet(const Projet& p);
    Projet& operator=(const Projet&);

    //Appelé par la méthode ajouterTache seulement
    void setDateEcheance(const QDate& d);
    friend class ProjetManager;
    Projet(const QString& n, const QString& desc, const QDate& disp):nom(n), description(desc), disponibilite(disp), echeance(QDate()){}


};

#endif // PROJET_H
