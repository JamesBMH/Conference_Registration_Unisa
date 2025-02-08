// 13413120 JBM HERTZOG
#ifndef GUI_H
#define GUI_H

#include "registrationlist.h"
#include "registrationlistreader.h"
#include "registrationlistwriter.h"
#include "registrationfactory.h"
#include <QWidget>

class QTableWidget;
class QLineEdit;
class QLabel;
class QPushButton;
class QRadioButton;

class Gui : public QWidget
{
    Q_OBJECT

public:
    // Constructor initializes widgets
    // Creates connections between signals and slots
    // Calls functions to setup the GUI
    Gui(QWidget *parent = nullptr);
    ~Gui();

private slots:
    // Disallows empty fields to be submitted when the register button is clicked
    // Uses RegistrationList's email duplication function to check for email duplications
    // Uses RegistrationList's addRegistration to add a registration
    // Adds the registered person the the table widget
    void addRegistration();
    // Shows a input dialog to collect the name to be searched
    // Uses RegistrationList's isRegistered function to search for a given name in the list
    // Shows an appropriate message
    void searchName();
    // Uses an input dialog to collect the registration type you want to check
    // Uses RegistrationList's totalFee function to get the total fee for a type of registration
    // Shows an appropriate message
    void calculateCost();
    // Uses an input dialog to collect the institution you want to check
    // Uses RegistrationList's totalRegistrations function to calculate the answer
    // Shows an appropriate message with the total count of members attending affiliated with an institution
    void affiliatedRegistrations();
    // Gets the directory the user wants to save their XML document to
    // Calls RegistrationListWriter's writeXML function which takes the created RegistrationList as well as
    // the filepath that will be used to save the file to the appropriate place that is obtained with a FileDialog
    // Files are saved as RegistrationList.xml
    void saveFile();
    // Uses a filedialog to let you choose a xml file to use
    // Calls RegistrationListReader.readXml to parse data and return a QList<Registration*>
    // Uses RegistrationList.addRegistration to add the registration items to RegistrationList
    // Manually update the table with the new data
    void loadFile();
    void addToTable();

    // Clears fields and disables LineEdits depending on what radio button is chosen
    void defaultClicked();
    void studentClicked();
    void guestClicked();
    // Clears LineEdits
    void clearWidgets();

private:
    // Creates and sets the layout for the GUI
    // Sets window size default
    // Calls setupTable and the setters for validators
    void setup();
    // Sets the number of columns and column headings for the table
    void setupTable();
    // Sets the default values when the program is started
    void defaults();
    // Input validators for line edits using regular expressions
    void setNameValidator();
    void setAffiliationValidator();
    void setEmailValidator();

    RegistrationList RegistrationList;
    RegistrationListWriter RegistrationListWriter;
    RegistrationListReader RegistrationListReader;

    // Widgets
    QTableWidget *table;
    QLineEdit *nameLineEdit;
    QLineEdit *affiliationLineEdit;
    QLineEdit *emailLineEdit;
    QLineEdit *qLineEdit;
    QLineEdit *cLineEdit;
    QLabel *nameLabel;
    QLabel *affiliationLabel;
    QLabel *emailLabel;
    QLabel *qLabel;
    QLabel *cLabel;
    QLabel *standardFee;
    QLabel *studentFee;
    QLabel *guestFee;
    QPushButton *registerButton;
    QPushButton *searchButton;
    QPushButton *calculateButton;
    QPushButton *affiliatedButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QRadioButton *defaultRadio;
    QRadioButton *studentRadio;
    QRadioButton *guestRadio;

signals:

};
#endif // GUI_H
