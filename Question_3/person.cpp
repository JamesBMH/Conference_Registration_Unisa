// 13413120 JBM HERTZOG
#include "person.h"
#include <QTextStream>

Person::Person() : m_Name{""}, m_Affiliation{""}, m_Email{""}
{

}

Person::Person(QString n, QString a, QString e) : m_Name{n}, m_Affiliation{a}, m_Email{e}
{}

QString Person::getName()
{
    return m_Name;
}

QString Person::getAffiliation()
{
    return m_Affiliation;
}

QString Person::getEmail()
{
    return m_Email;
}

QString Person::toString()
{
    QString display;
    QTextStream out(&display);

    out << getName() << '\n';
    out << getAffiliation() << '\n';
    out << getEmail() << '\n';
    out.flush();

    return display;
}
