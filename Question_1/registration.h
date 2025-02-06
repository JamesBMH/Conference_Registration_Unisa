// 13413120 JBM HERTZOG
#ifndef REGISTRATION_H
#define REGISTRATION_H

//Constants for fees
const double STANDARD_FEE = 100;
const double STUDENT_FEE = STANDARD_FEE * 0.5;
const double GUEST_FEE = STANDARD_FEE * 0.1;

#include <QObject>
#include "person.h"
#include "qdatetime.h"

class Registration : public QObject
{
    Q_OBJECT
    // metaobject system implementation
    Q_PROPERTY(QString m_RegisterType READ getRegisterType)
public:
    explicit Registration(Person a, QObject *parent = nullptr);
    Person getAttendee();
    QDate getBookingDate();
    QString getRegisterType();
    void setRegisterType(QString r);
    // Returns the approprite fee using the constants for the type of registration
    // Is overloaded by inhereted classes
    virtual double calculateFee();
    virtual QString toString();
private:
    Person m_Attendee;
    QDate m_BookingDate;
    QString m_RegisterType;
signals:
};

#endif // REGISTRATION_H
