#include "tachefactory.h"

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

