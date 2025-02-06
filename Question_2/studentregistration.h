// 13413120 JBM HERTZOG
#ifndef STUDENTREGISTRATION_H
#define STUDENTREGISTRATION_H

#include <QObject>
#include "registration.h"

class StudentRegistration : public Registration
{
    Q_OBJECT
    // metaobject system implementation
    Q_PROPERTY(QString m_RegisterType READ getRegisterType)
public:
    explicit StudentRegistration(Person a, QString q, QObject *parent = nullptr);
    // Returns the approprite fee using the constants for the type of registration
    double calculateFee() override;
    QString toString() override;

private:
    QString m_Qualification;
};

#endif // STUDENTREGISTRATION_H
