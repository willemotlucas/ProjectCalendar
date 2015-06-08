#include "tachefactory.h"
#include "tacheunitaire.h"
#include "tacheunitairepreemptive.h"
#include "tachecomposite.h"

TacheFactory::TacheFactory()
{

}

TacheFactory::~TacheFactory()
{

}

Tache& TacheFactory::creerTacheUnitaire(const QString &id, const QString &desc, const QDate &dispo, const QDate &echeance, const QTime &duree, const int& etat){
    Tache* t = new TacheUnitaire(id,desc,dispo,echeance,duree, etat);
    return *t;
}

Tache& TacheFactory::creerTacheUnitairePreemptive(const QString &id, const QString &desc, const QDate &dispo, const QDate &echeance, const QTime& dureeInit, const QTime &dureeRest, const int& etat){
    Tache* t = new TacheUnitairePreemptive(id,desc,dispo,echeance,dureeInit, dureeRest, etat);
    return *t;
}

Tache& TacheFactory::creerTacheComposite(const QString& id, const QString& desc, const QDate& dispo){
    Tache* t = new TacheComposite(id,desc,dispo);
    return *t;
}

TacheFactory::Handler TacheFactory::handler=TacheFactory::Handler();

TacheFactory& TacheFactory::getInstance(){
    if (handler.instance==0) handler.instance=new TacheFactory;
    return *(handler.instance);
}

void TacheFactory::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

