#ifndef REGISTRATIONLISTREADER_H
#define REGISTRATIONLISTREADER_H

#include "registration.h"
#include <QObject>

class RegistrationListReader : public QObject
{
    Q_OBJECT
public:
    explicit RegistrationListReader(QObject *parent = nullptr);
    // Use the given xml file to parse the data into a list of registration items
    QList<Registration*> readXml(QString fileName);

signals:
};

#endif // REGISTRATIONLISTREADER_H
