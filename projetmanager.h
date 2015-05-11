#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H

#include <QString>
#include <QDate>
#include <vector>
#include "projet.h"

class ProjetManager
{
public:
    typedef std::vector<Projet*> contProjet;
    Projet& ajouterProjet(const QString& nom, const QString& desc, const QDate& dispo);
    Projet& getProjet(const QString& nom);
    const Projet& getProjet(const QString& nom) const;
    const contProjet& getProjets() const { return projets;}
    bool isProjetExistante(const QString& nom) const { return trouverProjet(nom)!=0; }
    void load(const QString& f);
    void save(const QString& f);
    static ProjetManager& getInstance();
    static void libererInstance();

private:
    contProjet projets;
    void addItem(Projet* p);
    Projet* trouverProjet(const QString& nom) const;
    QString file;
    ProjetManager();
    ~ProjetManager();
    ProjetManager(const ProjetManager& um);
    ProjetManager& operator=(const ProjetManager& um);
    struct Handler{
        ProjetManager* instance;
        Handler():instance(0){}
        // destructeur appelé à la fin du programme
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;

};

#endif // PROJETMANAGER_H
