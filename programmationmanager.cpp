#include "programmationmanager.h"
#include "global.h"
#include <QDebug>
#include <QtXml>

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
    for(unsigned int i=0; i<programmations.size(); i++)
        if (&t==&programmations[i]->getTache()) return programmations[i];
    return 0;
}

void ProgrammationManager::ajouterProgrammation(const Projet& p, const Tache& t, const QDate& d, const QTime& h){
    if (trouverProgrammation(t)) throw CalendarException("Erreur. La tache " + t.getId() + " est déjà programmée.");
    Programmation* newt=new Programmation(p,t,d,h);
    qDebug()<<"date = "<<d<<" | horaire = "<<h;
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
    for(programmations::iterator it = programmations.begin(); i != programmations.end(); ++it){
        //A chaque programmation, on créé un noeud <programmation> contenant la tache programmée, la date et l'horaire
        QDomElement prog = dom->createElement("programmation");
        prog.setAttribute("tache", (*it)->getTache()->getId());

        QDomElement date = dom->createElement("date");
        QDomElement dateText = dom->createElement((*it)->getDate()->toString());
        date.appendChild(dateText);

        QDomElement horaire = dom->createElement("horaire");
        horaire.setAttribute("minute", (*it)->getHoraire()->minutes());
        horaire.setAttribute("heure", (*it)->getHoraire()->hours());

        prog.appendChild(date);
        prog.appendChild(horaire);
        progs.appendChild(prog);
    }

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
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture fichier xml"));
    if(!dom->setContent(&newfile))
        throw CalendarException(QString("erreur sauvegarde tâches : ouverture objet dom"));
    newfile.close();

    QDomElement dom_element = dom->documentElement();
    QDomNode progs = dom_element.firstChildElement("programmations");

    //Si le fichier ne contient aucune programmation, on ne fait rien
    if(progs.isNull()){
        return;
    }
    //Sinon on parcout l'arbre DOM pour recréer le vector de programmations
    else{
        //Pour recréer l'objet Tache, on a juste son identifiant, on doit donc charger sa tache grâce au projet
    }
}
