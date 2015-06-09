#include "programmationmanager.h"
#include "projetmanager.h"
#include "tachefactory.h"
#include "tacheunitaire.h"
#include "mainwindow.h"
#include "tache.h"
#include "global.h"
#include <QDebug>
#include <QtXml>
#include <typeinfo>
#include <QMessageBox>

ProgrammationManager::Handler ProgrammationManager::handler=ProgrammationManager::Handler();

ProgrammationManager& ProgrammationManager::getInstance(){
    if (handler.instance==0) handler.instance=new ProgrammationManager;
    return *(handler.instance);
}

void ProgrammationManager::libererInstance(){
    if (handler.instance!=0) delete handler.instance;
    handler.instance=0;
}

ProgrammationManager::ProgrammationManager():programmations(0){}

void ProgrammationManager::addItem(Programmation* prog){
    programmations.push_back(prog);
}

Programmation* ProgrammationManager::trouverProgrammation(const Tache& t)const{
    for(std::vector<Programmation*>::const_iterator it = programmations.begin(); it != programmations.end(); ++it){
        if((*it)->getTache().getId() == t.getId()){
            return (*it);
        }
    }
    return 0;
}

bool ProgrammationManager::ajoutPossible(const Tache &t, const QDate& d, const QTime& h){
    //Si la tache reçue est une tache unitaire, on la cast pour accéder à sa durée
    if(typeid(t) == typeid(TacheUnitaire)){
        try{
            const TacheUnitaire& tmp = dynamic_cast<const TacheUnitaire&>(t);
            if(d < tmp.getDateDisponibilite() || d > tmp.getDateEcheance())
                return false;

            for(std::vector<Programmation*>::iterator it = programmations.begin(); it != programmations.end(); ++ it){
                //La tache testée est une tache unitaire, on peut maintenant accéder à sa durée
                if(typeid((*it)->getTache()) == typeid(TacheUnitaire))
                {
                    const TacheUnitaire& tacheprog = dynamic_cast<const TacheUnitaire&>((*it)->getTache());
                    if((*it)->getDate() == d)
                    {
                        if((*it)->getHoraire() == h)
                            return false;
                        if( ((h.addSecs(tmp.getDuree().hour()*3600 + tmp.getDuree().minute()*60)) > (*it)->getHoraire())
                        && ((h.addSecs(tmp.getDuree().hour()*3600 + tmp.getDuree().minute()*60)) < ((*it)->getHoraire().addSecs(tacheprog.getDuree().hour()*3600 + tacheprog.getDuree().minute()*60))) )
                            return false;
                        if( (h > (*it)->getHoraire())
                        && (h < ((*it)->getHoraire().addSecs(tacheprog.getDuree().hour()*3600 + tacheprog.getDuree().minute()*60))) )
                            return false;
                        if( ((*it)->getHoraire() > h)
                        && ((*it)->getHoraire() < (h.addSecs(tmp.getDuree().hour()*3600 + tmp.getDuree().minute()*60)))
                        && (((*it)->getHoraire().addSecs(tacheprog.getDuree().hour()*3600 + tacheprog.getDuree().minute()*60)) < (h.addSecs(tmp.getDuree().hour()*3600 + tmp.getDuree().minute()*60))) )
                            return false;
                    }
                }
            }
            return true;
        }
        catch(std::bad_cast& bc){qDebug()<<"err:"<<bc.what();}
    }
}

void ProgrammationManager::ajouterProgrammation(const Projet& p, const Tache& t, const QDate& d, const QTime& h){
    if (trouverProgrammation(t)) throw CalendarException("Erreur. La tache " + t.getId() + " est déjà programmée.");
    if(!ajoutPossible(t,d,h)) throw CalendarException("Erreur. Une tâche est déjà programmée ou la tâche n'est plus disponible à ce moment.");
    Programmation* newt=new Programmation(p,t,d,h);
    addItem(newt);
}

ProgrammationManager::~ProgrammationManager(){
    programmations.clear();
}

void ProgrammationManager::save(){
    //On créé l'arbre DOM
    QDomDocument* dom = new QDomDocument("programmations");
    QDomElement dom_element = dom->documentElement();

    //On créé le noeud <programmations> qui contiendra toutes les programmations
    QDomNode progs = dom->createElement("programmations");

    //On parcourt toutes les programmations du vector
    for(std::vector<Programmation*>::iterator it = programmations.begin(); it != programmations.end(); ++it){
        //A chaque programmation, on créé un noeud <programmation> contenant la tache programmée, la date et l'horaire
        QDomElement prog = dom->createElement("programmation");
        prog.setAttribute("tache", (*it)->getTache().getId());
        prog.setAttribute("projet", (*it)->getProjet().getNom());

        QDomElement date = dom->createElement("date");
        QDomText dateText = dom->createTextNode((*it)->getDate().toString());
        date.appendChild(dateText);

        QDomElement horaire = dom->createElement("horaire");
        horaire.setAttribute("minute", (*it)->getHoraire().minute());
        horaire.setAttribute("heure", (*it)->getHoraire().hour());

        prog.appendChild(date);
        prog.appendChild(horaire);
        progs.appendChild(prog);
    }

    dom->appendChild(progs);

    QFile fichier(progXML);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fichier.close();
        throw new CalendarException(QString("Erreur lors de l'ouverture du fichier " + progXML + " pour écriture."));
    }

    //Ecriture de l'arbre DOM dans le fichier XML
    QString write_doc = dom->toString();
    QTextStream stream(&fichier);
    stream<<write_doc;
    fichier.close();
}

void ProgrammationManager::load(){
    QDomDocument* dom = new QDomDocument("programmations");
    QFile newfile(progXML);

    if (!newfile.open(QIODevice::ReadOnly | QIODevice::Text))
        throw CalendarException(QString("Erreur. Chargement du fichier " + progXML + " impossible"));
    if(!dom->setContent(&newfile))
        throw CalendarException(QString("Erreur. Impossible de créer l'arbre DOM pour le fichier " + progXML));
    newfile.close();

    QDomElement dom_element = dom->documentElement();
    QDomNode progs = dom_element.firstChild();

    //Sinon on parcout l'arbre DOM pour recréer le vector de programmations
    if(progs.hasChildNodes()){
        ProjetManager& pm = ProjetManager::getInstance();
        //Pour recréer l'objet Tache, on a juste son identifiant, on doit donc charger sa tache grâce au projet
        //On parcourt tous les noeuds <programmation>
        QDomNodeList nl = progs.childNodes();
        QDomNode n = nl.at(0);

        for(QDomNode prog = dom_element.firstChildElement("programmation"); !prog.isNull(); prog = prog.nextSiblingElement("programmation")){
            //On recrée tous les objets nécessaires à la construction d'un objet programmation
            Projet* p = pm.getProjet(prog.toElement().attribute("projet"));
            Tache* t = p->getTache(prog.toElement().attribute("tache"));
            QDate date = QDate::fromString(prog.firstChildElement("date").toElement().text(), Qt::TextDate);
            int heure = prog.firstChildElement("horaire").toElement().attribute("heure").toInt();
            int minute = prog.firstChildElement("horaire").toElement().attribute("minute").toInt();
            QTime horaire(heure,minute);

            //On ajoute la programmation dans le vector
            addItem(new Programmation(*p,*t,date,horaire));
        }
    }
}
