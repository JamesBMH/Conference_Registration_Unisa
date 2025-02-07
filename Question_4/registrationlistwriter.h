//13413120 JBM HERTZOG
#ifndef REGISTRATIONLISTWRITER_H
#define REGISTRATIONLISTWRITER_H

#include <QObject>
#include "registrationlist.h"

class QDir;

class RegistrationListWriter : public QObject
{
    Q_OBJECT
public:
    explicit RegistrationListWriter(QObject *parent = nullptr);
    // Splits the QList<QString> received from RegistrationList into their
    // respective data parts using split and a QStringList
    // These individual data components are then used to construct the XML document
    // Saves the xml file to the specified filePath
    void writeXML(QList<QString> processedData, QDir filePath);

signals:
};

#endif // REGISTRATIONLISTWRITER_H
