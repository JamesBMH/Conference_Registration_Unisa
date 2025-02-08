//13413120 JBM HERTZOG
#include "registrationlistreader.h"
#include "registration.h"
#include "guestregistration.h"
#include "studentregistration.h"
#include "person.h"
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QtXml>

RegistrationListReader::RegistrationListReader(QObject *parent)
    : QObject{parent}
{}

QList<Registration*> RegistrationListReader::readXml(QString fileName)
{
    // Declarations
    QString name, affiliation, email, qualification{""}, category{""}, bookingDate, registrationFee;
    int iRegistrationType;
    QList<Registration*> tempList;
    QFile file(fileName);
    QDomDocument xmlDom;

    // Make sure the file can be opened
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Failed to open file to writing";
    } else {
        // Make sure the DomDocument can accept the data
        if (!xmlDom.setContent(&file)){
            qDebug() << "Failed to load document";
        }
        file.close();
    }

    // Find root element
    QDomElement root = xmlDom.firstChildElement();

    // Get node list of Registration items
    QDomNodeList registrationItems = root.elementsByTagName("registration");

    // Iterate through Registration nodes
    for (int i = 0; i < registrationItems.count(); i++){
        QDomNode itemNode = registrationItems.at(i);

        // Make sure the node is indeed an Element
        if(itemNode.isElement()){
            QDomElement itemElement = itemNode.toElement();

            // Returns the type attribute of itemElement a.k.a. what type of registration
            QString registrationType = itemElement.attribute("type");
            // Get list of child nodes of the Registration node
            QDomNodeList registrationChildren = itemElement.childNodes();

            // Use the child nodes to get the relevant data
            QDomNode bookingDateNode = registrationChildren.at(1);
            QDomElement bookingDateElement = bookingDateNode.toElement();
            bookingDate = bookingDateElement.text();

            QDomNode registrationFeeNode = registrationChildren.at(2);
            QDomElement registrationFeeElement = registrationFeeNode.toElement();
            registrationFee = registrationFeeElement.text();

            QDomNode attendeeNode = registrationChildren.at(0);
            QDomElement attendeeElement = attendeeNode.toElement();

            // Get list of Attendee child nodes
            QDomNodeList attendeeList = attendeeElement.childNodes();

            // Get relevant info from child nodes
            QDomNode nameNode = attendeeList.at(0);
            QDomElement nameElement = nameNode.toElement();
            name = nameElement.text();

            QDomNode affiliationNode = attendeeList.at(1);
            QDomElement affiliationElement = affiliationNode.toElement();
            affiliation = affiliationElement.text();

            QDomNode emailNode = attendeeList.at(2);
            QDomElement emailElement = emailNode.toElement();
            email = emailElement.text();

            // Gets data from the appropriate Registration type
            // Creates a Person object with relevant data
            // Creates a Registration of appropriate type
            // Appends Registration to the QList<Registration*>
            if(registrationType == "Student"){
                QDomNode qualificationNode = attendeeList.at(3);
                QDomElement qualificationElement = qualificationNode.toElement();
                qualification = qualificationElement.text();

                iRegistrationType = 1;
                category = "";

                /*
                Person temp(name, affiliation, email);
                Registration *tempStudent{new StudentRegistration(temp, qualification, bookingDate)};
                tempStudent->setRegisterType("Student");
                tempList.append(tempStudent);*/
            } else if(registrationType == "Guest"){
                QDomNode categoryNode = attendeeList.at(3);
                QDomElement categoryElement = categoryNode.toElement();
                category = categoryElement.text();

                iRegistrationType = 2;
                qualification = "";

                /*
                Person temp(name, affiliation, email);
                Registration *tempGuest{new GuestRegistration(temp, category, bookingDate)};
                tempGuest->setRegisterType("Guest");
                tempList.append(tempGuest);*/
            }else {
                iRegistrationType = 0;

                /*
                Person temp(name, affiliation, email);
                Registration *tempStandard{new Registration(temp, bookingDate)};
                tempStandard->setRegisterType("Standard");
                tempList.append(tempStandard);*/
            }

            Person temp(name, affiliation, email);
            tempList.append(RegistrationFactory::getInstance().addRegistration(temp, qualification, category, iRegistrationType, bookingDate));
        }
    }

    return tempList;
}
