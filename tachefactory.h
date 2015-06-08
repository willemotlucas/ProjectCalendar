#ifndef TACHEFACTORY_H
#define TACHEFACTORY_H

#include "tache.h"

class TacheFactory
{
private:
    TacheFactory();
    ~TacheFactory();
    TacheFactory(const TacheFactory& um);
    TacheFactory& operator=(const TacheFactory& um);
    struct Handler{
        TacheFactory* instance;
        Handler():instance(0){}
        // destructeur appelé à la fin du programme
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;

public:
    static TacheFactory& getInstance();
    static void libererInstance();
    Tache& creerTacheUnitaire(const QString& id, const QString& desc, const QDate& dispo, const QDate& echeance, const QTime& duree, const int& etat=1);
    Tache& creerTacheUnitairePreemptive(const QString &id, const QString &desc, const QDate &dispo, const QDate &echeance, const QTime &duree, const int& etat=1);
    Tache& creerTacheComposite(const QString& id, const QString& t, const QDate& dispo);
};

#endif // TACHEFACTORY_H
