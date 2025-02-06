// 13413120 JBM HERTZOG
#ifndef PERSON_H
#define PERSON_H

#include <QObject>

class Person
{
public:
    Person();
    Person(QString n, QString a, QString e);
    // Getters for private members
    QString getName();
    QString getAffiliation();
    QString getEmail();
    QString toString();
private:
    QString m_Name;
    QString m_Affiliation;
    QString m_Email;
signals:
};

#endif // PERSON_H
