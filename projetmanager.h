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

    /*!
         *  \brief ajouterProjet
         *
         *  Ajout d'un projet
         *
         *  \param nom : nom du nouveau projet
         *  \param desc : description du nouveau projet
         *  \param dispo : date de Disponibilite du nouveau projet
         */
    Projet& ajouterProjet(const QString& nom, const QString& desc, const QDate& dispo);

    /*!
         *  \brief getProjet
         *
         *  Accesseur en lecture d'un projet
         *
         *  \param nom : nom du projet
         */
    Projet* getProjet(const QString& nom) const;

    /*!
         *  \brief getProjetConst
         *
         *  Accesseur en lecture constant d'un projet
         *
         *  \param nom : nom du projet
         */
    const Projet& getProjetConst(const QString& nom) const;

    /*!
         *  \brief isProjetExistant
         *
         *  Fonction booleenne pour savoir si un projet existe deja ou non
         *
         *  \param nom : nom du projet
         */
    bool isProjetExistant(const QString& nom) const { return trouverProjet(nom)!=0; }

    /*!
         *  \brief load
         *
         *  Chargement du projet dans le fichier XML
         *
         *  \param f : nom du fichier XML
         */
    void load(const QString& f);

    /*!
         *  \brief loadTache
         *
         *  Chargement d'une tache dans le fichier XML
         *
         *  \param dom : arborescence du fichier xml
         *  \param tache : noeud de la tache a charger
         */    
    Tache& loadTache(QDomDocument* dom ,QDomNode* tache);

    /*!
         *  \brief save
         *
         *  Sauvegarde du projet dans le fichier XML
         *
         *  \param f : nom du fichier XML
         */
    void save();

    /*!
         *  \brief getInstance
         *
         *  Fonction statique permettant d'avoir l'instance unique du projet
         *  a n'importe quel endroit du code.
         */
    static ProjetManager& getInstance();

    /*!
         *  \brief libererInstanceProjet
         *
         *  Fonction statique permettant de liberer l'instance du projet en cours.
         */
    static void libererInstance();

    /*!
         *  \brief iterator begin
         *
         *  Iterator begin sur le tableau vector de projet
         */
    contProjet::iterator begin(){return projets.begin();}

    /*!
         *  \brief iterator end
         *
         *  Iterator end sur le tableau vector de projet
         */
    contProjet::iterator end(){return projets.end();}

    /*!
         *  \brief Destructeur
         *
         *  Destructeur de la classe ProjetManager
         */
    ~ProjetManager();

private:
    contProjet projets;/*!< Vector contenant les projets*/

    /*!
         *  \brief addITem
         *
         *  Ajout d'un projet dans le vector
         *
         *  \param p : pointeur sur le projet a ajouter
         */
    void addItem(Projet* p);

    /*!
         *  \brief trouverProjet
         *
         *  Fonction permettant de retrouver un fichier dans le XML grace a son nom
         *
         *  \param nom : nom du projet recherche
         */
    Projet* trouverProjet(const QString& nom) const;
//    QString file;/*!< Nom du fichier XML*/

    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe ProjetManager
         */
    ProjetManager();

    /*!
         *  \brief Constructeur de recopie
         *
         *  Constructeur de recopie de la classe ProjetManager
         *
         *  \param um : ProjetManager a recopie
         */
    ProjetManager(const ProjetManager& um);

    /*!
         *  \brief Operateur d'affectation
         *
         *  Operateur d'affectation de la classe ProjetManager
         *
         *  \param um : ProjetManager a recopie
         */
    ProjetManager& operator=(const ProjetManager& um);

    /*! \class Handler
       * \brief Classe encapsulant l'instance unique du ProjetManager
       *
       *  La classe Handler permet de s'occuper automatiquement
       *  de l'instance unique du projetManager.
       *  Ainsi, lors de la fermeture du programme, le destructeur de Handler
       *  sera appele et celui ci lancera alors la sauvegarde des modifications
       *  dans le fichier XML.
       */
    struct Handler{
        ProjetManager* instance;/*!< Instance unique du projet manager*/

        /*!
             *  \brief Constructeur
             *
             *  Constructeur de la classe Handler
             */
        Handler():instance(0){}
        // destructeur appelé à la fin du programme

        /*!
             *  \brief Destructeur
             *
             *  Destructeur de la classe Handler
             */
        ~Handler(){ if (instance) delete instance; }
    };
    static Handler handler;/*!< Handler statique permettant notamment la sauvegarde automatique*/

};

#endif // PROJETMANAGER_H
