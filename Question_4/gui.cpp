// 13413120 JBM HERTZOG
#include "gui.h"
#include "person.h"
#include "registration.h"
#include "studentregistration.h"
#include "guestregistration.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QDebug>
#include <QInputDialog>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QFileDialog>
#include <QDir>

Gui::Gui(QWidget *parent)
    : QWidget(parent),
    table{new QTableWidget(0, 5, this)},
    nameLineEdit{new QLineEdit},
    nameLabel{new QLabel("Name:")},
    affiliationLineEdit{new QLineEdit},
    affiliationLabel{new QLabel("Affiliation:")},
    emailLineEdit{new QLineEdit},
    emailLabel{new QLabel("Email:")},
    qLabel{new QLabel("Qualification:")},
    qLineEdit{new QLineEdit},
    cLabel{new QLabel("Category")},
    cLineEdit{new QLineEdit},
    registerButton{new QPushButton("Register")},
    searchButton{new QPushButton("Search")},
    calculateButton{new QPushButton("Total Cost")},
    affiliatedButton{new QPushButton("Total Registration")},
    defaultRadio{new QRadioButton("Standard")},
    studentRadio{new QRadioButton("Student")},
    guestRadio{new QRadioButton("Guest")},
    standardFee{new QLabel("Fee: R100")},
    studentFee{new QLabel("Fee: R50")},
    guestFee{new QLabel("Fee: R10")},
    saveButton{new QPushButton("Save")},
    loadButton{new QPushButton("Load")}
{
    // Functions to setup the gui at start
    defaults();
    setup();

    // Connections
    connect(registerButton, &QPushButton::clicked, this, &::Gui::addRegistration);
    connect(searchButton, &QPushButton::clicked, this, &::Gui::searchName);
    connect(calculateButton, &QPushButton::clicked, this, &::Gui::calculateCost);
    connect(affiliatedButton, &QPushButton::clicked, this, &::Gui::affiliatedRegistrations);
    connect(saveButton, &QPushButton::clicked, this, &::Gui::saveFile);
    connect(loadButton, &QPushButton::clicked, this, &::Gui::loadFile);

    connect(defaultRadio, &QRadioButton::clicked, this, &::Gui::defaultClicked);
    connect(studentRadio, &QRadioButton::clicked, this, &::Gui::studentClicked);
    connect(guestRadio, &QRadioButton::clicked, this, &::Gui::guestClicked);
}

Gui::~Gui() {}

void Gui::addRegistration()
{
    // Do not allow the user to submit empty information
    if (nameLineEdit->text() == "" || affiliationLineEdit->text() == "" || emailLineEdit->text() == "") return;

    QString tName = nameLineEdit->text();
    QString tAffiliation = affiliationLineEdit->text();
    QString tEmail = emailLineEdit->text();
    QString tQualification = qLineEdit->text();
    QString tCategory = cLineEdit->text();
    int registrationType = -1;

    if (defaultRadio->isChecked()){
        registrationType = 0;
    }
    else if (studentRadio->isChecked()){
        registrationType = 1;
    }
    else if (guestRadio->isChecked()){
        registrationType = 2;
    }

    // Check if email is duplicated
    if (RegistrationList.checkEmailDupes(tEmail, tName)){
        QMessageBox message;
        message.setText("This email cannot be registered to you multiple times");
        message.exec();
        emailLineEdit->clear();
        return;
    }

    Person tempPerson(tName, tAffiliation, tEmail);

    //RegistrationFactory::getInstance().addRegistration(tempPerson, tQualification, tCategory, registrationType);

    // Creates an appropriate type of registration and adds it to RegistrationList
    // Updates table with new data
    /*
    if (defaultRadio->isChecked()){
        Registration *tempRegister{new Registration(tempPerson)};
        tempRegister->setRegisterType("Standard");
        RegistrationList.addRegistration(tempRegister);
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount()-1,0,new QTableWidgetItem(tempPerson.getName()));
        table->setItem(table->rowCount()-1,1,new QTableWidgetItem(tempPerson.getAffiliation()));
        table->setItem(table->rowCount()-1,2,new QTableWidgetItem(tempPerson.getEmail()));
        table->setItem(table->rowCount()-1,3,new QTableWidgetItem(QString::number(tempRegister->calculateFee())));
        table->setItem(table->rowCount()-1,4,new QTableWidgetItem(tempRegister->getBookingDate().toString("yyyy-MM-dd")));
    } else if(studentRadio->isChecked()){
        Registration *tempRegister{new StudentRegistration(tempPerson, tQualification)};
        tempRegister->setRegisterType("Student");
        RegistrationList.addRegistration(tempRegister);
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount()-1,0,new QTableWidgetItem(tempPerson.getName()));
        table->setItem(table->rowCount()-1,1,new QTableWidgetItem(tempPerson.getAffiliation()));
        table->setItem(table->rowCount()-1,2,new QTableWidgetItem(tempPerson.getEmail()));
        table->setItem(table->rowCount()-1,3,new QTableWidgetItem(QString::number(tempRegister->calculateFee())));
        table->setItem(table->rowCount()-1,4,new QTableWidgetItem(tempRegister->getBookingDate().toString("yyyy-MM-dd")));
    } else if(guestRadio->isChecked()){
        Registration *tempRegister{new GuestRegistration(tempPerson, tCategory)};
        tempRegister->setRegisterType("Guest");
        RegistrationList.addRegistration(tempRegister);
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount()-1,0,new QTableWidgetItem(tempPerson.getName()));
        table->setItem(table->rowCount()-1,1,new QTableWidgetItem(tempPerson.getAffiliation()));
        table->setItem(table->rowCount()-1,2,new QTableWidgetItem(tempPerson.getEmail()));
        table->setItem(table->rowCount()-1,3,new QTableWidgetItem(QString::number(tempRegister->calculateFee())));
        table->setItem(table->rowCount()-1,4,new QTableWidgetItem(tempRegister->getBookingDate().toString("yyyy-MM-dd")));
    }*/

    //RegistrationList.addRegistration(RegistrationFactory::getInstance().addRegistration(tempPerson, tQualification, tCategory, registrationType));

    Registration *tempRegister = RegistrationFactory::getInstance().addRegistration(tempPerson, tQualification, tCategory, registrationType);

    RegistrationList.addRegistration(tempRegister);
    table->insertRow(table->rowCount());
    table->setItem(table->rowCount()-1,0,new QTableWidgetItem(tempPerson.getName()));
    table->setItem(table->rowCount()-1,1,new QTableWidgetItem(tempPerson.getAffiliation()));
    table->setItem(table->rowCount()-1,2,new QTableWidgetItem(tempPerson.getEmail()));
    table->setItem(table->rowCount()-1,3,new QTableWidgetItem(QString::number(tempRegister->calculateFee())));
    table->setItem(table->rowCount()-1,4,new QTableWidgetItem(tempRegister->getBookingDate().toString("yyyy-MM-dd")));

    defaults();

    // Save button is enabled when a successfull registration is added
    saveButton->setEnabled(true);
}

void Gui::searchName()
{
    QString name = QInputDialog::getText(this, "Person to be searched", "Enter a name: ");
    QMessageBox message;
    if (RegistrationList.isRegistered(name)){
        message.setText(name + " is regestired for the conference.");
        message.exec();
    } else{
        message.setText(name + " is not found in our registrations.");
        message.exec();
    }
}

void Gui::calculateCost()
{
    int selection = QInputDialog::getInt(this, "Type the number for the respective category", "All: 0  Standard: 1  Student: 2  Guest: 3", 0, 0, 3);

    QMessageBox message;

    if (selection == 0){
        message.setText("Total Registration fee for everyone is : R" + QString::number(RegistrationList.totalFee("All")));
        message.exec();
    } else if (selection == 1){
        message.setText("Total fee for Standard Registration is : R" + QString::number(RegistrationList.totalFee("Standard")));
        message.exec();
    } else if (selection == 2){
        message.setText("Total fee for Student Registration is : R" + QString::number(RegistrationList.totalFee("Student")));
        message.exec();
    } else {
        message.setText("Total fee for Guest Registration is : R" + QString::number(RegistrationList.totalFee("Guest")));
        message.exec();
    }
}

void Gui::affiliatedRegistrations()
{
    QString institution = QInputDialog::getText(this, "Institution headcount", "Enter an affiliated institution:");

    int institutionHeadcount = RegistrationList.totalRegistrations(institution);

    QMessageBox message;
    message.setText(institution + " has " + QString::number(institutionHeadcount) + " affiliated member/s registered");
    message.exec();
}

void Gui::saveFile()
{

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                    QDir::currentPath(),
                                                    QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);

    RegistrationListWriter.writeXML(RegistrationList.dataParser(), dir);
}

void Gui::loadFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose File", QDir::currentPath(),"*.xml");

    QList<Registration*> tempList = RegistrationListReader.readXml(fileName);

    for(int i = 0; i < tempList.count(); i++){
        RegistrationList.addRegistration(tempList[i]);
        table->insertRow(table->rowCount());
        table->setItem(table->rowCount()-1,0,new QTableWidgetItem(tempList[i]->getAttendee().getName()));
        table->setItem(table->rowCount()-1,1,new QTableWidgetItem(tempList[i]->getAttendee().getAffiliation()));
        table->setItem(table->rowCount()-1,2,new QTableWidgetItem(tempList[i]->getAttendee().getEmail()));
        table->setItem(table->rowCount()-1,3,new QTableWidgetItem(QString::number(tempList[i]->calculateFee())));
        table->setItem(table->rowCount()-1,4,new QTableWidgetItem(tempList[i]->getBookingDate().toString("yyyy-MM-dd")));

    }
}

void Gui::addToTable()
{

}

void Gui::defaultClicked()
{
    clearWidgets();
    qLineEdit->setDisabled(true);
    qLineEdit->clear();
    cLineEdit->setDisabled(true);
    cLineEdit->clear();
}

void Gui::studentClicked()
{
    clearWidgets();
    qLineEdit->setDisabled(false);
    qLineEdit->clear();
    cLineEdit->setDisabled(true);
    cLineEdit->clear();
}

void Gui::guestClicked()
{
    clearWidgets();
    qLineEdit->setDisabled(true);
    qLineEdit->clear();
    cLineEdit->setDisabled(false);
    cLineEdit->clear();
}

void Gui::clearWidgets()
{
    qLineEdit->clear();
    cLineEdit->clear();
    nameLineEdit->setFocus();
}

void Gui::setup()
{
    QHBoxLayout *nameInput{new QHBoxLayout};
    nameInput->addWidget(nameLabel);
    nameInput->addWidget(nameLineEdit);

    QHBoxLayout *affiliationInput{new QHBoxLayout};
    affiliationInput->addWidget(affiliationLabel);
    affiliationInput->addWidget(affiliationLineEdit);

    QHBoxLayout *emailInput{new QHBoxLayout};
    emailInput->addWidget(emailLabel);
    emailInput->addWidget(emailLineEdit);

    QHBoxLayout *qLayout{new QHBoxLayout};
    qLayout->addWidget(qLabel);
    qLayout->addWidget(qLineEdit);

    QHBoxLayout *cLayout{new QHBoxLayout};
    cLayout->addWidget(cLabel);
    cLayout->addWidget(cLineEdit);

    QVBoxLayout *radioStandard{new QVBoxLayout};
    radioStandard->addWidget(defaultRadio);
    radioStandard->addWidget(standardFee);

    QVBoxLayout *radioStudent{new QVBoxLayout};
    radioStudent->addWidget(studentRadio);
    radioStudent->addWidget(studentFee);

    QVBoxLayout *radioGuest{new QVBoxLayout};
    radioGuest->addWidget(guestRadio);
    radioGuest->addWidget(guestFee);

    QHBoxLayout *registrationType{new QHBoxLayout};
    registrationType->addLayout(radioStandard);
    registrationType->addLayout(radioStudent);
    registrationType->addLayout(radioGuest);

    QVBoxLayout *dataInput{new QVBoxLayout};
    dataInput->addLayout(nameInput);
    dataInput->addLayout(affiliationInput);
    dataInput->addLayout(emailInput);
    dataInput->addLayout(qLayout);
    dataInput->addLayout(cLayout);
    dataInput->addLayout(registrationType);

    QVBoxLayout *buttonsVertically{new QVBoxLayout};
    buttonsVertically->addWidget(registerButton);
    buttonsVertically->addWidget(searchButton);
    buttonsVertically->addWidget(calculateButton);
    buttonsVertically->addWidget(affiliatedButton);
    buttonsVertically->addWidget(saveButton);
    buttonsVertically->addWidget(loadButton);


    QHBoxLayout *seperation{new QHBoxLayout};
    seperation->addLayout(dataInput);
    seperation->addLayout(buttonsVertically);

    QVBoxLayout *layout{new QVBoxLayout};
    layout->addLayout(seperation);
    layout->addWidget(table);

    this->setLayout(layout);

    this->setMinimumHeight(500);
    this->setMinimumWidth(525);

    setupTable();
    setNameValidator();
    setAffiliationValidator();
    setEmailValidator();

    saveButton->setEnabled(false);
}

void Gui::setupTable()
{
    table->setHorizontalHeaderLabels({"Name", "Affiliation", "Email", "Fee", "Booking Date"});
}

void Gui::defaults()
{
    qLineEdit->setDisabled(true);
    cLineEdit->setDisabled(true);
    defaultRadio->setChecked(true);
    qLineEdit->clear();
    cLineEdit->clear();
    emailLineEdit->clear();
    affiliationLineEdit->clear();
    nameLineEdit->clear();
    nameLineEdit->setFocus();
}

// Requires 3 alphabet characters before a whitespace is allowed
// Only allows alphabet characters
void Gui::setNameValidator()
{
    QRegularExpression re1("[A-Za-z]{3}[A-Za-z\\s]*");
    QValidator *nameValidator{new QRegularExpressionValidator(re1)};

    nameLineEdit->setValidator(nameValidator);
}

// Requires 3 alphabet characters before a whitespace is allowed
// Alphabet characters and numbers are allowed
// Applied to Affiliation, Category, and Qualification line edits
void Gui::setAffiliationValidator()
{
    QRegularExpression re2("[0-9A-Za-z]{3}[0-9A-Za-z\\s]*");
    QValidator *affiliationValidator = new QRegularExpressionValidator(re2);

    affiliationLineEdit->setValidator(affiliationValidator);
    cLineEdit->setValidator(affiliationValidator);
    qLineEdit->setValidator(affiliationValidator);

}

// Requires a character which could be alphabetical, numerical, or the special symbols !#$ respectively
// After an @ is used no more special characters can be used
// @ and . are required to create a valid emial address
void Gui::setEmailValidator()
{
    QRegularExpression re3("[A-Za-z0-9_!$#]+@[A-Za-z0-9]+.[A-Za-z0-9.]+");
    QValidator *emailValidator = new QRegularExpressionValidator(re3);

    emailLineEdit->setValidator(emailValidator);
}
