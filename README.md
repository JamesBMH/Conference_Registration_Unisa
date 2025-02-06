Conference registration program for the second assignment of my third year programming class COS3711

How to build:
Loading the CMakeLists.txt into Qt creator loads the project into Qt.
The project is then able to be built and run.

Program explenation:

Detailed criteria for the program is given in the assignment pdf as provided by Unisa.
Comments are mostly made in header files explaining functions.
cpp file comments explain function specific fuctionality as to avoid confusion.

    Question 1:
        -Users can register for the conference
        -Users can choose a registration type using the checkboxes
        -Users can search if a person is registered for the conference by name
        -Users can search for the cost of the conference (total of all-, standard-, student-, or guest registration fee)
        -Users can search for the amount of people registered for the conference by affiliation (ex. 2 Dell members are attending)
        -Users registered for the conference are displayed in the table widget
        -The registration button is deactivated if there are empty fields
        -The "Qualification" and "Category" text boxes become active when student or guest is selected respectively
        -The registration fee of students and guests are calculated from the standard fee
        -Users can have the same email address only if their names differ (person cannot register twice for the same conference)
        -Regex is used to validate input (no special characters for names or affiliation, email is anything followed by @ then anything followed by dot followed by anything)

    Question 2:
        -All functionality of quesiton 1
        -The registration list can be saved as an XML document "RegistrationList.xml" using the save button
        -Users can choose where to save the file
        -If the file RegistrationList.xml already exists in the directory it is overwritten
        -Saving is disabled until a user registered for the conference

    Question 3:
        -All functionality of question 2
        -Users can load an existing registration list from their chosen directory
        -If there are registered users when a file is loaded the data will be appended to the table
        -Saving is disabled until a new user has been registered for the conference
