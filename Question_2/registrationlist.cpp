// 13413120 JBM HERTZOG
#include "registrationlist.h"
#include "registration.h"
#include <qDebug>
#include <QMetaProperty>
#include <QMetaObject>
#include <QVariant>

RegistrationList::RegistrationList(QObject *parent)
    : QObject{parent}
{}

bool RegistrationList::addRegistration(Registration* r)
{
    int count = m_AttendeeList.count();
    m_AttendeeList.append(r);

    if (m_AttendeeList.count() == (count + 1)){
        return true;
    } else return false;
}

bool RegistrationList::isRegistered(QString n)
{
    n = n.toLower();

    for(QList<Registration*>::iterator iter = m_AttendeeList.begin(); iter != m_AttendeeList.end(); iter++)
    {
        if ((*iter)->getAttendee().getName().toLower() == n) return true;
    }
    return false;
}

int RegistrationList::totalRegistrations(QString a)
{
    int count = 0;
    a = a.toLower();

    for(QList<Registration*>::iterator iter = m_AttendeeList.begin(); iter != m_AttendeeList.end(); iter++)
    {
        if ((*iter)->getAttendee().getAffiliation().toLower() == a) count++;
    }
    return count;
}

bool RegistrationList::checkEmailDupes(QString mail, QString name)
{
    for(QList<Registration*>::iterator iter = m_AttendeeList.begin(); iter != m_AttendeeList.end(); iter++){
        if ((*iter)->getAttendee().getEmail().toLower() == mail.toLower() && (*iter)->getAttendee().getName().toLower() == name.toLower()) return true;
    }
    return false;
}

QList<QString> RegistrationList::dataParser()
{
    QList<QString> processedData;
    // Data items will be combined in dataItem and added to processedData
    QString dataItem;
    QTextStream out(&dataItem);

    for(int i = 0; i < m_AttendeeList.count(); i++){
        // Use meta object system to obtain registration type
        const QMetaObject *mo{m_AttendeeList[i]->metaObject()};

        const QMetaProperty prop{mo->property(mo->propertyOffset())};
        QVariant value{prop.read(m_AttendeeList[i])};
        QString convertedName{value.toString()};
        out << convertedName << '\n';
        // Use toString to gather other data
        out << m_AttendeeList[i]->toString();

        processedData.append(dataItem);
        dataItem.clear();
    }

    return processedData;
}

double RegistrationList::totalFee(QString t)
{
    double totalCost = 0;    

    // If the client selected All return sumtotal of all fees
    if (t == "All"){
        for(QList<Registration*>::iterator iter = m_AttendeeList.begin(); iter != m_AttendeeList.end(); iter++)
        {
            totalCost += (*iter)->calculateFee();
        }
    }else{
        // Use meta object system to obtain registration type
        for(int i = 0; i < m_AttendeeList.count(); i++){
            const QMetaObject *mo{m_AttendeeList[i]->metaObject()};

            const QMetaProperty prop{mo->property(mo->propertyOffset())};
            QVariant value{prop.read(m_AttendeeList[i])};
            QString convertedName{value.toString()};

            // Add the fee of the registration if the registration type matches
            if (convertedName.toLower() == t.toLower()){
                totalCost += m_AttendeeList[i]->calculateFee();
            }
        }
    }

    return totalCost;
}

RegistrationList::~RegistrationList()
{
    qDeleteAll(m_AttendeeList);
}
