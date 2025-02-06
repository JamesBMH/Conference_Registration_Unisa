// 13413120 JBM HERTZOG
#ifndef REGISTRATIONLIST_H
#define REGISTRATIONLIST_H

#include <QObject>

class Registration;

class RegistrationList : public QObject
{
    Q_OBJECT
public:
    explicit RegistrationList(QObject *parent = nullptr);
    // Adds a registration to m_AttendeeList
    bool addRegistration(Registration* r);
    // Checks if a person in already registered
    bool isRegistered(QString n);
    // Returns the total fee for everyone in a type of registration
    // Uses qt's metaobject system
    double totalFee(QString t);
    // Returns the number of attendees for a specified affiliated institution
    int totalRegistrations(QString a);
    // Additional function that checks if an email is duplicated
    // If an email is a duplication but the names differ then it is valid
    bool checkEmailDupes(QString mail, QString name);
    // Destroys the list
    ~RegistrationList();
private:
    QList<Registration*> m_AttendeeList;

signals:
};

#endif // REGISTRATIONLIST_H
