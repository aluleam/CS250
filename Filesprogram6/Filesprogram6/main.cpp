#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;
// Activity locations
enum Location {GYM,PARK,CLASSROOM};
enum Operation {ADD, PRINT, EDIT, EXIT};

const int MAX_SIZE = 51;

struct recCenter {
    char activities[MAX_SIZE];// Activity name
    Location location;   // Activity location
    int max_enroll;      // Maximum participants
    
};

void addRecord(fstream& activitiesFile);
void printActivities(fstream& activitiesFile);
void editItem(fstream& activitiesFile);
void exitProgram();
int handleMenu();



int main()
    {
        int choice;
        
        fstream activitiesFile("activities.dat", ios::in | ios::out | ios::binary);
        
        if (!activitiesFile.is_open()) {
            cout << "Unable to open the file for reading and writing." << endl;
            activitiesFile.clear(); // Clear error flags
            activitiesFile.open("activities.dat", ios::out | ios::binary); // Try creating it for writing
            
            if (!activitiesFile.is_open()) {
                cout << "Failed to create the file." << endl;
                return 102; // Exit with an error code
            } else {
                cout << "New file created for writing." << endl;
            }
        } else {
            cout << "File opened successfully for reading and writing." << endl;
        }
        
        // File should be opened only once and should be closed at the end of the main function
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
        
        activitiesFile.close();
        return 0;
    }

void printActivities(fstream& activitiesFile)
{
    string locationString;
    recCenter activity;
    activitiesFile.seekg(0L); // Go to the beginning of the file

    cout << left << setw(20) << "Name" << setw(15) << "Location" << setw(15) << "Max Enrollment" << endl;
    while (activitiesFile.read(reinterpret_cast<char*>(&activity), sizeof(activity))){
        
        cout << left << setw(20) << activity.activities;
        switch(activity.location)
        {
            case GYM:
                locationString = "Gym";
                break;
            case PARK:
                locationString = "Park";
                break;
            case CLASSROOM:
                locationString = "Classroom";
                break;
            default:
                locationString = "Unknown";
                break;
        }
        cout << setw(15) << locationString;
        cout << setw(15) << activity.max_enroll << endl;
    }
}

void editItem(fstream& activitiesFile) {
    int activityNumber;
    recCenter activity;

    // Read and display all activities with numbers
    int recordNumber = 1;
    activitiesFile.seekg(0L);
    while (activitiesFile.read(reinterpret_cast<char*>(&activity), sizeof(activity))) {
        cout << recordNumber << ". " << activity.activities << endl;
        recordNumber++;
    }

    // Ask the user to select an activity to edit
    cout << "Enter the number of the activity to edit: ";
    cin >> activityNumber;

    // Validate the input
    if (activityNumber < 1 || activityNumber >= recordNumber) {
        cout << "Invalid activity number." << endl;
        return;
    }

    // Move to the selected activity's position in the file
    activitiesFile.seekg((activityNumber - 1) * sizeof(activity));
    activitiesFile.read(reinterpret_cast<char*>(&activity), sizeof(activity));

    // Display the current information of the selected activity
    cout << "Editing activity: " << activity.activities << endl;
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
    cout << "Current max enrollment: " << activity.max_enroll << endl;

    // Ask the user for new information
    cout << "Enter new location (0 for GYM, 1 for PARK, 2 for CLASSROOM): ";
    int loc;
    cin >> loc;
    activity.location = static_cast<Location>(loc);
    cout << "Enter new max enrollment: ";
    cin >> activity.max_enroll;

    // Write the updated information back to the file
    activitiesFile.seekp((activityNumber - 1) * sizeof(activity));
    activitiesFile.write(reinterpret_cast<char*>(&activity), sizeof(activity));

    cout << "Activity updated successfully." << endl;
}
    
// Asking the user to select an option from the menu and validate the choice entered
int handleMenu()
{
    int choice;

    do {
        // Display menu options
        cout << endl << "Menu:" << endl;
        cout << "1. Add a record" << endl;
        cout << "2. View Activities" << endl;
        cout << "3. Edit an item" << endl;
        cout<<  "4. Exit"<<endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate the choice is between 1 and 4
        if(choice < 1 || choice > 4)
        {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while(choice < 1 || choice > 4); // Repeat until the user enter a valid choice

    return choice;
}

void exitProgram()
{
    cout << "Thank you for using the Recruitment Activities Program!" << endl;
    cout << "We hope it has been helpful in organizing and managing the activities." << endl;
    cout << "Remember to check back for updates and new features." << endl;
    cout << "Your feedback is always welcome to improve our services." << endl;
    cout << "Have a great day and we look forward to seeing you again!" << endl;

    // Use exit code 0 to indicate a clean and expected termination
    exit(0);
}


