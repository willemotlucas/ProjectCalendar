#ifndef TACHEUNITAIREPREEMPTIVE_H
#define TACHEUNITAIREPREEMPTIVE_H

/*!
 * \file TacheUnitairePreemptive.h
 * \brief Fichier portant sur les taches unitaires preemptives
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QTime>
#include "tacheunitaire.h"

/*! \class TacheUnitairePreemptive
   * \brief classe representant les taches unitaires preemptives
   *
   *  La classe gere la creation de toutes les taches unitaires preemtives de l' utilisateur.
   *  Une tache unitaire preemptive est une tache unitaire pouvant etre programmée en
   *  plusieurs fois et n'a pas de durée limitée .
   */
class TacheUnitairePreemptive : public TacheUnitaire
{
public:
    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe TacheUnitairePreemptive
         */
    virtual ~TacheUnitairePreemptive(){}

    /*!
         *  \brief write
         *
         *  Ecriture de la tache a l'interieur de notre arborescence
         *
         *  \param dom : arborescence de notre fichier XML
         */
    QDomElement& write(QDomDocument* dom);

    /*!
         *  \brief chargerTreeTache
         *
         *  Chargement de la tache a l'interieur de notre arborescence TreeWidget
         *
         *  \param tree : arborescence de notre treeview
         */
    QTreeWidgetItem& chargerTreeTache(QTreeWidget* tree);

    //STATES METHODS
    /*!
         *  \brief isProgrammee
         *
         *  Fonction booleenne permettant de savoir
         *  si la tache est deja programmée
         */
    bool isProgrammee() const { return etat == PROGRAMMEE; }

    //GETTERS AND SETTERS
    /*!
         *  \brief getDureeInit
         *
         *  Accesseur en lecture de duree initiale de la Tache
         */
    const QTime& getDureeInit() const { return dureeInitiale; }

    /*!
         *  \brief getDureeRestante
         *
         *  Accesseur en lecture de duree restante de la Tache
         */
    const QTime& getDureeRestante() const { return dureeRestante; }

    /*!
         *  \brief setDureeRestante
         *
         *  Accesseur en ecriture de duree restante de la Tache
         *
         *  \param duree : duree soustraire de la duree restante
         */
    void setDureeRestante(const QTime& duree){
        int hour = dureeRestante.hour() - duree.hour();
        int minute = dureeRestante.minute() - duree.minute();
        dureeRestante = QTime(hour, minute);
        if(hour == 0 && minute == 0)
            etat = (Etat)1;
    }
    void setEtat(unsigned int e){ etat = (Etat)e; }
    unsigned int getEtat() const { return (unsigned int)etat;}
    void setDateEcheance(const QDate& e){}

private:
    QTime dureeInitiale;/*!< Duree initiale de la Tache*/
    QTime dureeRestante;/*!< Duree restante de la Tache*/

    friend class TacheFactory;
    /*!
         *  \brief Constructeur avec l'attribut date d'echeance
         *
         *  Constructeur de la classe Tache
         *
         *  \param id : identificateur de la Tache
         *  \param t : titre de la Tache
         *  \param dispo : disponibilite de la Tache
         *  \param deadline : echeance de la Tache
         *  \param dureeInit : duree initiale de la Tache
         *  \param dureeRest : duree restante de la Tache
         *  \param e : etat de la Tache
         */
    TacheUnitairePreemptive(const QString& id, const QString& t, const QDate& dispo, const QDate& deadline, const QTime& durInit, const QTime& durRest, unsigned int e = 1):TacheUnitaire(id, t, dispo, deadline,QTime(0,0), e),dureeInitiale(durInit),dureeRestante(durRest){}



    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie de la classe TacheUnitairePreemptive
         *
         *  \param t : tache que l'on veut recopier
         */
    TacheUnitairePreemptive(const TacheUnitairePreemptive& t);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe Tache
         *
         *  \param t : tache que l'on veut recopier
         */
    const TacheUnitairePreemptive& operator=(const TacheUnitairePreemptive& t);

};

#endif // TACHEUNITAIREPREEMPTIVE_H
