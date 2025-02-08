#include "registrationfactory.h"
RegistrationFactory* RegistrationFactory::instance = nullptr;

RegistrationFactory &RegistrationFactory::getInstance()
{
    if (instance == nullptr){
        instance = new RegistrationFactory();
    }

    return *instance;
}

Registration* RegistrationFactory::addRegistration(Person tPerson, QString tQualification, QString tCategory, int registrationType)
{
    if (registrationType == 0){
        Registration *tempRegister{new Registration(tPerson)};
        tempRegister->setRegisterType("Standard");
        return tempRegister;
    }
    else if (registrationType == 1){
        Registration *tempRegister{new StudentRegistration(tPerson, tQualification)};
        tempRegister->setRegisterType("Student");
        return tempRegister;
    }
    else if (registrationType == 2){
        Registration *tempRegister{new GuestRegistration(tPerson, tCategory)};
        tempRegister->setRegisterType("Guest");
        return tempRegister;
    }
}

RegistrationFactory::RegistrationFactory(QObject *parent)
    : QObject{parent}
{}

RegistrationFactory::~RegistrationFactory()
{}
