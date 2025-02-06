// 13413120 JBM HERTZOG
#include "studentregistration.h"

StudentRegistration::StudentRegistration(Person a, QString q, QObject *parent)
    : Registration{a, parent}
{
    m_Qualification = q;
}

StudentRegistration::StudentRegistration(Person a, QString q, QString date, QObject *parent)
    : Registration{a, date, parent}
{
    m_Qualification = q;
}

double StudentRegistration::calculateFee()
{
    return STUDENT_FEE;
}

QString StudentRegistration::toString()
{
    QString display;
    QTextStream out(&display);

    out << getAttendee().toString();
    out << m_Qualification << '\n';
    out << getBookingDate().toString("yyyy.MM.dd") << '\n';
    out << calculateFee() << '\n';
    out.flush();

    return display;
}
