// 13413120 JBM HERTZOG
#ifndef GUESTREGISTRATION_H
#define GUESTREGISTRATION_H

#include <QObject>
#include "registration.h"
#include "person.h"

class GuestRegistration : public Registration
{
    Q_OBJECT
    // metaobject system implementation
    Q_PROPERTY(QString m_RegisterType READ getRegisterType)
public:
    explicit GuestRegistration(Person a, QString q, QObject *parent = nullptr);
    // Returns the approprite fee using the constants for the type of registration
    double calculateFee() override;
    QString toString() override;

private:
    QString m_Category;
};

#endif // GUESTREGISTRATION_H
