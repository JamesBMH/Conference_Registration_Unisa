//13413120 JBM Hertzog
#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include "registrationlist.h"
#include "registration.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include "person.h"
#include <QObject>

class RegistrationFactory : public QObject
{
    Q_OBJECT
public:
    //Returns singleton instance
    static RegistrationFactory& getInstance();
    //Creates appropriate Registration object and returns pointer to that object
    Registration* addRegistration(Person tPerson, QString tQualification, QString tCategory, int registrationType);
    //tempPerson, tQualification, tCategory, registrationType
private:
    //Private constructor
    explicit RegistrationFactory(QObject *parent = nullptr);
    //Destructor
    ~RegistrationFactory();
    //Delete copy constructor
    RegistrationFactory(RegistrationFactory const&) = delete;
    //Delete overload assignment opererator
    RegistrationFactory& operator=(RegistrationFactory const&) = delete;
    static RegistrationFactory *instance;
};

#endif // REGISTRATIONFACTORY_H
