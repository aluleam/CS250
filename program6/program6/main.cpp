//**************************************************************************
//**************************************************************************
// Program:    rec_activity_MA.cpp
// Name:       Masumbuko Alulea
// Instructor: Kurtenbach Paula
// Due Date:   Nov 06, 2023
// Description: This program manages recruitment activities with options to
//              add, view, edit, and exit. Activity data is stored in a binary
//              file.
//**************************************************************************
//**************************************************************************

#include <iostream>
#include <iomanip>
#include <cstring>
#include <fstream>
using namespace std;

// Activity locations
enum Location { GYM, PARK, CLASSROOM };
// Operations
enum Operation { ADD, PRINT, EDIT, EXIT };

const int MAX_SIZE = 51;

struct recCenter {
    char activities[MAX_SIZE]; // Activity name
    Location location;         // Activity location
    int max_enroll;            // Maximum participants
};
// Function prototypes
void addRecord(fstream &activitiesFile);       // Add a new record to the file
void printActivities(fstream &activitiesFile); // Print all activity from the file
void editItem(fstream &activitiesFile);        // Edit an activity
void exitProgram();                            // Exit the program with a message
int handleMenu();                              // Display the menu and get the user's choice

int main() {
    int choice;

    // Open or create the activities file in binary mode
    fstream activitiesFile("/Users/makingaberto/Desktop/CS250/MK C++/ActivitiesDataMK.txt", ios::in | ios::out | ios::binary);

    // Check if the file opened
    if (activitiesFile.fail())
    {
        cout << "Unable to open the file" << endl;
        activitiesFile.clear(); // Clear error flags

        // Create the file for writing if it doesn't exist
        activitiesFile.open("/Users/makingaberto/Desktop/CS250/MK C++/ActivitiesDataMK.txt", ios::out | ios::binary);

        // Check if it failed creating the file
        if (!activitiesFile) {
            cout << "Failed to create the file." << endl;
            exit(102); // Exit with a code
        } else {
            cout << "File created successfully." << endl;
        }
    } else {
        cout << "File opened successfully" << endl;
    }

    do {
        choice = handleMenu();

        switch (choice) {
        case ADD:
            addRecord(activitiesFile);
            break;
        case PRINT:
            printActivities(activitiesFile);
            break;
        case EDIT:
            editItem(activitiesFile);
            break;
        case EXIT:
            exitProgram();
            break;
        }
    } while (choice != EXIT);

    activitiesFile.close(); // Close the file (good practice)
    return 0;
}


void addRecord(fstream &activitiesFile) {
    recCenter activity; //This will hold the information of the new activity
    int loc;
    
    cout << "Enter activity name: ";
    cin.ignore(); // Ignore any newline character in the input buffer
    cin.getline(activity.activities, MAX_SIZE); //Read the activity name

    cout << "Select location (0 for GYM, 1 for PARK, 2 for CLASSROOM): ";
    cin >> loc;
    activity.location = static_cast<Location>(loc); // Convert the integer to enum

    cout << "Enter maximum enrollment: ";
    cin >> activity.max_enroll;

    // Seek to the end of the file and write the new record
    activitiesFile.seekp(0L, ios::end);
    activitiesFile.write(reinterpret_cast<char *>(&activity), sizeof(activity));

    cout << "Record added successfully." << endl;
}

void printActivities(fstream& activitiesFile) {
    string mylocation;
    recCenter activity;
    activitiesFile.clear(); // Clear error flags
    activitiesFile.seekg(0L); // Go to the beginning of the file
    cout<<endl<<"Displaying the Activities"<<endl;
    cout<<"-----------------------------------------------------"<<endl;
    cout << left << setw(20) << "|Name" << setw(15) << "|Location "<< setw(15) <<" |Max Enrollment |" << endl;
    cout << "--------------------|--------------------------------" << endl;

    while (activitiesFile.read(reinterpret_cast<char*>(&activity), sizeof(activity))) {
        cout << left << setw(20) << activity.activities<<"|";

        // Convert the location enum to a string
        switch (activity.location)
        {
            case GYM:
                mylocation = "GYM";
                break;
            case PARK:
                mylocation = "PARK";
                break;
            case CLASSROOM:
                mylocation= "CLASSROOM";
                break;
            default:
                mylocation = "Unknown";
                break;
        }

        cout << setw(15) << mylocation<<"|";
        cout << setw(15) << activity.max_enroll <<"|"<<endl;
    }
    cout<<"----------------------------------------------------"<<endl;
}
 


//Allowing the user to edit the file
void editItem(fstream &activitiesFile) {
    int activityNumber,loc,record = 1;
    recCenter activity;

    // Clear error flags and move to the beginning of the file
    activitiesFile.clear();
    activitiesFile.seekg(0L,ios::beg);

    cout << "Activities:" << endl;

    // Read and display activity names
    while (activitiesFile.read(reinterpret_cast<char *>(&activity), sizeof(activity))) {
        cout << record << ". " << activity.activities << endl;
        record++;
    }

    // Ask the user to choose the activity to edit
    cout << "Enter the number of the activity to edit 0 to cancel: ";
    cin >> activityNumber;

    if (activityNumber == 0) {
        cout << "Canceled." << endl;
        return;
    }

    // Validate what the user entered
    if (activityNumber < 1 || activityNumber >= record) {
        cout << "Invalid activity number." << endl;
        return;
    }

    // Move to the selected activity's position in the file
    activitiesFile.seekg((activityNumber - 1) * sizeof(activity));
    // Read the selected activity from the file
    activitiesFile.read(reinterpret_cast<char *>(&activity), sizeof(activity));

    // Display the content of the selected activity
    cout << "Editing activity: " << activity.activities << endl;

    // Display the location
    cout << "Current location: ";
    switch (activity.location) {
    case GYM:
        cout << "GYM";
        break;
    case PARK:
        cout << "PARK";
        break;
    case CLASSROOM:
        cout << "CLASSROOM";
        break;
    default:
        cout << "Unknown";
        break;
    }
    cout << endl;

    cout << "Max enrollment: " << activity.max_enroll << endl;

    // Ask the user for new information
    cout << "Enter new location 0 for GYM, 1 for PARK, 2 for CLASSROOM: ";
    cin >> loc;
    activity.location = static_cast<Location>(loc);

    cout << "Enter new max enrollment: ";
    cin >> activity.max_enroll;

    // Move the file pointer to the selected activity's position
    activitiesFile.seekp((activityNumber - 1) * sizeof(activity));
    // Write the new information to the file
    activitiesFile.write(reinterpret_cast<char *>(&activity), sizeof(activity));
    cout << "Activity updated." << endl;
}

int handleMenu() {
    int choice;

    do {
        // Display menu options
        cout << endl <<"Menu" << endl;
        cout<<"------------------"<<endl;
        cout << "0. Add a record" << endl;
        cout << "1. View Activities" << endl;
        cout << "2. Edit an item" << endl;
        cout << "3. Exit" << endl;
        //Promt for the desired choice
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate the choice is between 0 and 3
        if (choice < 0 || choice > 3) {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice < 0 || choice > 3); // Repeat until the user enters a valid choice

    return choice;
}

void exitProgram() {
    
    // Display a thank you message
    cout << "Thank you for using the Recruitment Activities Program!" << endl;
    cout << "We hope it has been helpful for managing the activities." << endl;
    cout << "Remember to check back for updates and new features." << endl;
    cout << "Your feedback is always welcome to improve our services." << endl;
    cout << "Have a great day and we look forward to seeing you again!" << endl;
    cout << "TOODLESSSSS"<<endl;
    // Exit the program
    exit(0);
}


