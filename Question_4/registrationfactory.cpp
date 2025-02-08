#include "registrationfactory.h"

RegistrationFactory &RegistrationFactory::getInstance()
{
    static RegistrationFactory instance;

    return instance;
}

RegistrationFactory::RegistrationFactory(QObject *parent)
    : QObject{parent}
{}
