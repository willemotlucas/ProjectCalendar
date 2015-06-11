#include "programmationmanager.h"
#include "projetmanager.h"
#include "tachefactory.h"
#include "tacheunitaire.h"
#include "tacheunitairepreemptive.h"
#include "mainwindow.h"
#include "tache.h"
#include "global.h"
#include <QDebug>
#include <QtXml>
#include <typeinfo>
#include <QMessageBox>
#include <algorithm>

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

bool ProgrammationManager::ajoutPossible(const Tache &t, const QDate& d, const QTime& h, const QTime& dur){
    if(d < t.getDateDisponibilite() || d > t.getDateEcheance())
        return false;

    for(std::vector<Programmation*>::iterator it = programmations.begin(); it != programmations.end(); ++ it){
        //La tache testée est une tache unitaire, on peut maintenant accéder à sa durée
        if(typeid((*it)->getTache()) == typeid(TacheUnitaire))
        {
            if((*it)->getDate() == d)
            {
                if((*it)->getHoraire() == h)
                    return false;
                if( ((h.addSecs(dur.hour()*3600 + dur.minute()*60)) > (*it)->getHoraire())
                && ((h.addSecs(dur.hour()*3600 + dur.minute()*60)) < ((*it)->getHoraire().addSecs((*it)->getDuree().hour()*3600 + (*it)->getDuree().minute()*60))) )
                    return false;
                if( (h > (*it)->getHoraire())
                && (h < ((*it)->getHoraire().addSecs((*it)->getDuree().hour()*3600 + (*it)->getDuree().minute()*60))) )
                    return false;
                if( ((*it)->getHoraire() > h)
                && ((*it)->getHoraire() < (h.addSecs(dur.hour()*3600 + dur.minute()*60)))
                && (((*it)->getHoraire().addSecs((*it)->getDuree().hour()*3600 + (*it)->getDuree().minute()*60)) < (h.addSecs(dur.hour()*3600 + dur.minute()*60))) )
                    return false;
            }
        }
    }
    return true;
}

void ProgrammationManager::ajouterProgrammation(const Projet& p, const Tache& t, const QDate& d, const QTime& h, const QTime& duree){
    if(!ajoutPossible(t,d,h, duree)) throw CalendarException("Erreur. Une tâche est déjà programmée ou la tâche n'est plus disponible à ce moment.");
    if(typeid(t) == typeid(TacheUnitaire)){
        if (trouverProgrammation(t)) throw CalendarException("Erreur. La tache " + t.getId() + " est déjà programmée.");
    }
    Programmation* newt=new Programmation(p,t,d,h, duree);
    addItem(newt);
}

ProgrammationManager::~ProgrammationManager(){
    programmations.clear();
}

QDomElement& ProgrammationManager::writeProgrammation(Programmation* p ,QDomDocument* dom){
    QDomElement* prog = new QDomElement(dom->createElement("programmation"));
    prog->setAttribute("tache", p->getTache().getId());
    prog->setAttribute("projet", p->getProjet().getNom());

    QDomElement date = dom->createElement("date");
    QDomText dateText = dom->createTextNode(p->getDate().toString());
    date.appendChild(dateText);

    QDomElement horaire = dom->createElement("horaire");
    horaire.setAttribute("minute", p->getHoraire().minute());
    horaire.setAttribute("heure", p->getHoraire().hour());

    QDomElement duree = dom->createElement("duree");
    duree.setAttribute("heure", p->getDuree().hour());
    duree.setAttribute("minute", p->getDuree().minute());

    prog->appendChild(date);
    prog->appendChild(horaire);
    prog->appendChild(duree);

    return *prog;
}

void ProgrammationManager::exportWeekXML(const QDate& dateDebut, const QDate& dateFin, const QString& filename){
    //On créé l'arbre DOM
    QDomDocument* dom = new QDomDocument("programmations");
    QDomElement dom_element = dom->documentElement();

    //On créé le noeud <programmations> qui contiendra toutes les programmations
    QDomNode progs = dom->createElement("programmations");

    //On parcourt toutes les programmations du vector
    for(std::vector<Programmation*>::iterator it = programmations.begin(); it != programmations.end(); ++it){
        //A chaque programmation, on créé un noeud <programmation> contenant la tache programmée, la date et l'horaire
        if((*it)->getDate() > dateDebut && (*it)->getDate() < dateFin){
            QDomElement prog = writeProgrammation((*it), dom);
            progs.appendChild(prog);
        }
    }

    dom->appendChild(progs);

    QFile fichier(filename);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fichier.close();
        throw new CalendarException(QString("Erreur lors de l'ouverture du fichier " + filename + " pour écriture."));
    }

    //Ecriture de l'arbre DOM dans le fichier XML
    QString write_doc = dom->toString();
    QTextStream stream(&fichier);
    stream<<write_doc;
    fichier.close();
}

void ProgrammationManager::exportProjectXML(const QString& projectname, const QString& filename){
    //On créé l'arbre DOM
    QDomDocument* dom = new QDomDocument("programmations");
    QDomElement dom_element = dom->documentElement();

    //On créé le noeud <programmations> qui contiendra toutes les programmations
    QDomNode progs = dom->createElement("programmations");

    //On parcourt toutes les programmations du vector
    for(std::vector<Programmation*>::iterator it = programmations.begin(); it != programmations.end(); ++it){
        //A chaque programmation, on créé un noeud <programmation> contenant la tache programmée, la date et l'horaire
        if((*it)->getProjet().getNom() == projectname){
            QDomElement prog = writeProgrammation((*it), dom);
            progs.appendChild(prog);
        }
    }

    dom->appendChild(progs);

    QFile fichier(filename);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        fichier.close();
        throw new CalendarException(QString("Erreur lors de l'ouverture du fichier " + filename + " pour écriture."));
    }

    //Ecriture de l'arbre DOM dans le fichier XML
    QString write_doc = dom->toString();
    QTextStream stream(&fichier);
    stream<<write_doc;
    fichier.close();
}

void ProgrammationManager::save(){
    //On créé l'arbre DOM
    QDomDocument* dom = new QDomDocument("programmations");
    QDomElement dom_element = dom->documentElement();

    //On créé le noeud <programmations> qui contiendra toutes les programmations
    QDomNode progs = dom->createElement("programmations");

    //On parcourt toutes les programmations du vector
    for(int i=0; i < programmations.size(); i++){
        //A chaque programmation, on créé un noeud <programmation> contenant la tache programmée, la date et l'horaire
        QDomElement prog = writeProgrammation(programmations[i],dom);
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
            int hDuree = prog.firstChildElement("duree").toElement().attribute("heure").toInt();
            int mDuree = prog.firstChildElement("duree").toElement().attribute("minute").toInt();
            QTime duree(hDuree,mDuree);

            //On ajoute la programmation dans le vector
            addItem(new Programmation(*p,*t,date,horaire,duree));
        }
    }
}

void ProgrammationManager::supprimerProgrammation(const Tache& t){

    std::vector<Programmation*>::iterator it = programmations.begin();
    while (it != programmations.end()) {
        if((*it)->getTache().getId() == t.getId())
            programmations.erase(it);
        else // <---- THIS IS IMPORTANT
            ++it;
    }
    CalendarWindow& cw = MainWindow::getInstanceAgenda();
    cw.displayTasks();
}
