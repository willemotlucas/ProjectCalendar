#ifndef PROJETMANAGER_H
#define PROJETMANAGER_H

/*!
 * \file ProjetManager.h
 * \brief Singleton permettant de s'occuper des projets
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QString>
#include <QDate>
#include <vector>
#include "projet.h"

/*! \class ProjetManager
   * \brief Classe Singleton Projet Manager
   *
   *  La classe Projet Manager s'occupe de gerer
   *  les projets que ce soit au niveau de la sauvegarde XML
   *  qu'au niveau de leur creation
   */
class ProjetManager
{
public:
    typedef std::vector<Projet*> contProjet;


    Projet& ajouterProjet(const QString& nom, const QString& desc, const QDate& dispo);
    Projet* getProjet(const QString& nom) const;
    const Projet& getProjetConst(const QString& nom) const;
    bool isProjetExistante(const QString& nom) const { return trouverProjet(nom)!=0; }
    void load(const QString& f);
    void save(const QString& f);
    static ProjetManager& getInstance();
    static void libererInstance();

    contProjet::iterator begin(){return projets.begin();}
    contProjet::iterator end(){return projets.end();}

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
