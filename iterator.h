#ifndef ITERATOR_H
#define ITERATOR_H

#include "tachemanager.h"

/* Mess file as for now ! There is all the iterators used during our tds !
 * At the end, we will have to use the design pattern template method or strategy
 * to create lost of differents iterators based on one abstract iterator */

class Iterator {
    friend class TacheManager;
    Tache** currentTache;
    unsigned int nbRemain;
    Iterator(Tache** u, unsigned nb):currentTache(u),nbRemain(nb){}
public:
    Iterator():nbRemain(0),currentTache(0){}
    bool isDone() const { return nbRemain==0; }
    void next() {
        if (isDone())
            throw CalendarException("error, next on an iterator which is done");
        nbRemain--;
        currentTache++;
    }
    Tache& current() const {
        if (isDone())
            throw CalendarException("error, indirection on an iterator which is done");
        return **currentTache;
    }
};

class ConstIterator {
    friend class TacheManager;
    Tache** currentTache;
    unsigned int nbRemain;
    ConstIterator(Tache** u, unsigned nb):currentTache(u),nbRemain(nb){}
public:
    ConstIterator():nbRemain(0),currentTache(0){}
    bool isDone() const { return nbRemain==0; }
    void next() {
        if (isDone())
            throw CalendarException("error, next on an iterator which is done");
        nbRemain--;
        currentTache++;
    }
    const Tache& current() const {
        if (isDone())
            throw CalendarException("error, indirection on an iterator which is done");
        return **currentTache;
    }
};

class iterator {
    Tache** current;
    iterator(Tache** u):current(u){}
    friend class TacheManager;
public:
    iterator():current(0){}
    Tache& operator*() const { return **current; }
    bool operator!=(iterator it) const { return current!=it.current; }
    iterator& operator++(){ ++current; return *this; }
};

class const_iterator {
    Tache** current;
    const_iterator(Tache** u):current(u){}
    friend class TacheManager;
public:
    const_iterator():current(0){};
    Tache& operator*() const { return **current; }
    bool operator!=(const_iterator it) const { return current!=it.current; }
    const_iterator& operator++(){ ++current; return *this; }
};

class DisponibiliteFilterIterator {
    friend class TacheManager;
    Tache** currentTache;
    unsigned int nbRemain;
    QDate dispo;
    DisponibiliteFilterIterator(Tache** u, unsigned nb, const QDate& d):currentTache(u),nbRemain(nb),dispo(d){
        while(nbRemain>0 && dispo<(*currentTache)->getDateDisponibilite()){
            nbRemain--; currentTache++;
        }
    }
public:
    DisponibiliteFilterIterator():nbRemain(0),currentTache(0){}
    bool isDone() const { return nbRemain==0; }
    void next() {
        if (isDone())
            throw CalendarException("error, next on an iterator which is done");
        do {
            nbRemain--; currentTache++;
        }while(nbRemain>0 && dispo<(*currentTache)->getDateDisponibilite());
    }
    Tache& current() const {
        if (isDone())
            throw CalendarException("error, indirection on an iterator which is done");
        return **currentTache;
    }
};

#endif // ITERATOR_H
