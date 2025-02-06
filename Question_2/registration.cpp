// 13413120 JBM HERTZOG
#include "registration.h"
#include <QDate>

Registration::Registration(Person a, QObject *parent)
    : QObject{parent}
{
    m_Attendee = a;
    m_BookingDate = QDate::currentDate();
}

Person Registration::getAttendee()
{
    return m_Attendee;
}

QDate Registration::getBookingDate()
{
    return m_BookingDate;
}

QString Registration::getRegisterType()
{
    return m_RegisterType;
}

void Registration::setRegisterType(QString r)
{
    m_RegisterType = r;
}

double Registration::calculateFee()
{
    return STANDARD_FEE;
}

QString Registration::toString()
{
    QString display;
    QTextStream out(&display);

    out << m_Attendee.toString();
    out << getBookingDate().toString("yyyy.MM.dd") << '\n';
    out << calculateFee() << '\n';
    out.flush();

    return display;
}
