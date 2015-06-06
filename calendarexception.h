#ifndef CALENDAREXCEPTION_H
#define CALENDAREXCEPTION_H

/*!
 * \file CalendarException.h
 * \brief Comporte la classe permettant de gerer les differentes exceptions
 *  que l' on pourrait avoir lors de l' utilisation de notre application
 * \author Lucas WILLEMOT et Valentin PAUL
 * \version 0.1
 */

#include <QString>

/*! \class CalendarException
   * \brief classe permettant de s'occuper des exceptions
   *
   *  La classe va s'occuper de receptionner et d'afficher les differentes
   *  exceptions sur lesquelles nous pouvons tomber lors de l'utilisation de notre
   *  application.
   */
class CalendarException{
public:
    /*!
         *  \brief Constructeur
         *
         *  Constructeur de la classe CalendarException
         *
         *  \param message : on recupere le message d'info a l'interieur de celui-ci.
         */
    CalendarException(const QString& message):info(message){}

    /*!
         *  \brief Affichage de l'info
         *
         *  Permet d'afficher sur le terminal l'exception que l'on a recu.
         */
    QString getInfo() const { return info; }
private:
    QString info;/*!< Message d'information */

};


#endif // CALENDAREXCEPTION_H
