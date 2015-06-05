#ifndef TACHEMANAGER_H
#define TACHEMANAGER_H

#include <QString>
#include <QDate>
#include "calendarexception.h"
#include "tache.h"
#include "iterator.h"


class TacheManager {
private:
    typedef std::vector<Tache*> contTache;
    contTache taches;
    void addItem(Tache* t);
    Tache* trouverTache(const QString& id) const;
    QString file;
    TacheManager();
    ~TacheManager();
    TacheManager(const TacheManager& um);
    TacheManager& operator=(const TacheManager& um);
    struct Handler{
        TacheManager* instance;
        Handler():instance(0){}
        // destructeur appelé à la fin du programme
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;
public:
    Tache& ajouterTache(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline);
    Tache& getTache(const QString& id);
    bool isTacheExistante(const QString& id) const { return trouverTache(id)!=0; }
    const Tache& getTache(const QString& code) const;
    void load(const QString& f);
    void save(const QString& f);
    static TacheManager& getInstance();
    static void libererInstance();
    contTache::iterator begin(){return taches.begin();}
    contTache::iterator end(){return taches.end();}

/*
    Iterator getIterator() {
        return Iterator(taches,nb);
    }
    ConstIterator getIterator() const{
        return ConstIterator(taches,nb);
    }    
    iterator begin() { return iterator(taches); }
    iterator end() { return iterator(taches+nb); }    
    const_iterator begin() const { return const_iterator(taches); }
    const_iterator end() const { return const_iterator(taches+nb); }    
    DisponibiliteFilterIterator getDisponibiliteFilterIterator(const QDate& d) {
        return DisponibiliteFilterIterator(taches,nb,d);
    }*/
};

#endif // TACHEMANAGER_H
