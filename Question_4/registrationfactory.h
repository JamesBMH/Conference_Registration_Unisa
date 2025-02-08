//13413120 JBM Hertzog
#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "person.h"
#include <QObject>

class Registration;

class RegistrationFactory : public QObject
{
    Q_OBJECT
public:
    // Returns singleton instance
    static RegistrationFactory& getInstance();
    // Creates appropriate Registration object and returns pointer to that object
    Registration* addRegistration(Person tPerson, QString tQualification, QString tCategory, int registrationType);
    // Overloaded addRegistration for RegistrationListReader due to extra date requirement
    Registration* addRegistration(Person tPerson, QString tQualification, QString tCategory, int registrationType, QString tDate);
private:
    // Private constructor
    explicit RegistrationFactory(QObject *parent = nullptr);
    // Destructor
    ~RegistrationFactory();
    // Delete copy constructor
    RegistrationFactory(RegistrationFactory const&) = delete;
    // Delete overload assignment opererator
    RegistrationFactory& operator=(RegistrationFactory const&) = delete;
    // Singleton instance
    static RegistrationFactory *instance;
};

#endif // REGISTRATIONFACTORY_H
