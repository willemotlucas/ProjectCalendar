#include "programmationmanager.h"


ProgrammationManager::ProgrammationManager():programmations(0){}
void ProgrammationManager::addItem(Programmation* prog){
    programmations.push_back(prog);
}

Programmation* ProgrammationManager::trouverProgrammation(const Tache& t)const{
    for(unsigned int i=0; i<programmations.size(); i++)
        if (&t==&programmations[i]->getTache()) return programmations[i];
    return 0;
}

void ProgrammationManager::ajouterProgrammation(const Tache& t, const QDate& d, const QTime& h){
    if (trouverProgrammation(t)) throw CalendarException("Erreur. La tache " + t.getId() + " est déjà programmée.");
    Programmation* newt=new Programmation(t,d,h);
    addItem(newt);
}

ProgrammationManager::~ProgrammationManager(){
    programmations.clear();
}
