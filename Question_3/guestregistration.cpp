// 13413120 JBM HERTZOG
#include "guestregistration.h"

GuestRegistration::GuestRegistration(Person a, QString q, QObject *parent)
    : Registration{a, parent}
{
    m_Category = q;
}

GuestRegistration::GuestRegistration(Person a, QString q, QString booking, QObject *parent)
    : Registration{a, booking, parent}
{
    m_Category = q;
}

double GuestRegistration::calculateFee()
{
    return GUEST_FEE;
}

QString GuestRegistration::toString()
{
    QString display;
    QTextStream out(&display);

    out << getAttendee().toString();
    out << m_Category << '\n';
    out << getBookingDate().toString("yyyy.MM.dd") << '\n';
    out << calculateFee() << '\n';
    out.flush();

    return display;
}
