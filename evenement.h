#ifndef EVENEMENT_H
#define EVENEMENT_H

#include <QDate>
#include <QTime>

class Evenement
{
    QDate date;
    QString description;
public:
    Evenement(const QDate& d, const QString& desc):date(d), description(desc){}
    virtual ~Evenement();
    const QDate& getDate() const { return date; }
    const QString& getTime() const { return description; }
};

#endif // EVENEMENT_H
