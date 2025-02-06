// 13413120 JBM HERTZOG
#include "registrationlistwriter.h"
#include <QtXml>
#include <QDir>
#include <QFile>

RegistrationListWriter::RegistrationListWriter(QObject *parent)
    : QObject{parent}
{}

void RegistrationListWriter::writeXML(QList<QString> processedData, QDir filePath)
{
    QDomDocument document;

    // Get root node
    QDomElement root = document.createElement("registrationlist");
    document.appendChild(root);

    for(int i = 0; i < processedData.count(); i++){
        // Split the data into a qstringlist to work with individual elements
        QStringList list = processedData[i].split("\n");

        //Use data elements to construct xml document
        QDomElement registration = document.createElement("registration");
        registration.setAttribute("type", list[0]);
        root.appendChild(registration);

        QDomElement attendee = document.createElement("Attendee");
        registration.appendChild(attendee);

        QDomElement name = document.createElement("Name");
        name.appendChild(document.createTextNode(list[1]));
        attendee.appendChild(name);

        QDomElement affiliation = document.createElement("Affiliation");
        affiliation.appendChild(document.createTextNode(list[2]));
        attendee.appendChild(affiliation);

        QDomElement email = document.createElement("Email");
        email.appendChild(document.createTextNode(list[3]));
        attendee.appendChild(email);

        // Use the data correlating to the appropriate registration type
        if (list[0] == "Student"){
            QDomElement qualification = document.createElement("Qualification");
            qualification.appendChild(document.createTextNode(list[4]));
            attendee.appendChild(qualification);
            QDomElement bookingDate = document.createElement("Booking_Date");
            bookingDate.appendChild(document.createTextNode(list[5]));
            registration.appendChild(bookingDate);
            QDomElement registrationFee = document.createElement("Registration_Fee");
            registrationFee.appendChild(document.createTextNode(list[6]));
            registration.appendChild(registrationFee);
        } else if(list[0] == "Guest"){
            QDomElement category = document.createElement("Category");
            category.appendChild(document.createTextNode(list[4]));
            attendee.appendChild(category);
            QDomElement bookingDate = document.createElement("Booking_Date");
            bookingDate.appendChild(document.createTextNode(list[5]));
            registration.appendChild(bookingDate);
            QDomElement registrationFee = document.createElement("Registration_Fee");
            registrationFee.appendChild(document.createTextNode(list[6]));
            registration.appendChild(registrationFee);
        }else{
            QDomElement bookingDate = document.createElement("Booking_Date");
            bookingDate.appendChild(document.createTextNode(list[4]));
            registration.appendChild(bookingDate);
            QDomElement registrationFee = document.createElement("Registration_Fee");
            registrationFee.appendChild(document.createTextNode(list[5]));
            registration.appendChild(registrationFee);
        }
    }

    QFile file;
    // File will be saved as RegistrationList.xml
    file.setFileName(filePath.absoluteFilePath("RegistrationList.xml"));

    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file to writing";
    } else
    {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
    }
}
