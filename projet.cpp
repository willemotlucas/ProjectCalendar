#include "projet.h"

void Projet::ajouterTache(const Tache &t){
    taches.push_back(t.clone());
}

