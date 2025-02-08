//13413120 JBM Hertzog
#ifndef REGISTRATIONFACTORY_H
#define REGISTRATIONFACTORY_H

#include <QObject>

class RegistrationFactory : public QObject
{
    Q_OBJECT
public:
    static RegistrationFactory& getInstance();
private:
    //Private constructor
    explicit RegistrationFactory(QObject *parent = nullptr);
    //Copy constructor
    RegistrationFactory(RegistrationFactory const&) = delete;
    //Overload assignment opererator
    RegistrationFactory& operator=(RegistrationFactory const&) = delete;
};

#endif // REGISTRATIONFACTORY_H
