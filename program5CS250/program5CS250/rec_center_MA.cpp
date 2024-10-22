#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
// Activity locations
enum Location {GYM,PARK,CLASSROOM};

struct recCenter {
    string name;         // Activity name
    Location location;   // Activity location
    int max_enroll;      // Maximum participants
    int current_enroll;  // Current participants
    string emails;       // Participants emails
};
//prototypes
string getLocation(Location place);
void printActivities(const recCenter activities[], int size);
void printEmails(const recCenter activities[], int size);
void registerAct(recCenter activities[], int size);
int getChoice();


int main() {
    // Define available activities
    recCenter centerActivities[5] = {
        {"Indoor Soccer", GYM, 50, 0, ""},
        {"Cross Country Skiing", PARK, 25, 0, ""},
        {"Video Editing", CLASSROOM, 40, 0, ""},
        {"Hot Yoga", GYM, 20, 0, ""},
        {"Water Color Painting", CLASSROOM, 15, 0, ""}
    };

    int choice;
    
    do {
        choice = getChoice(); // Ask user for a choice
        switch (choice) {
            case 1:
                // Show all activities
                printActivities(centerActivities, 5);
                break;
            case 2:
                // Sign up for an activity
                registerAct(centerActivities, 5);
                break;
            case 3:
                // Show emails of those who signed up
                printEmails(centerActivities, 5);
                break;
            case 4:
                // Exit message
                cout << "Toodles!!!!!" << endl;
                break;
            default:
                cout<<"Invalid Input"<<endl;
                break;
        }
    } while (choice != 4); // Keep running until the user choose the option to exit

    return 0;
}

// Convert Location enum to string
string getLocation(Location place) {
    switch (place) {
        case GYM: return "GYM";
        case PARK: return "PARK";
        case CLASSROOM: return "CLASSROOM";
    }
    // Return "UNKNOWN" for any other value
    return "UNKNOWN";
}

// Display activities in a formatted table.
void printActivities(const recCenter activities[], int size) {
    
    // Print table header
    cout << endl << "Activities" << endl;
    cout << "------------------------------------------------------------------------" << endl;
    cout << "No. | Activity Name           | Location  | Max Enroll  | Current Enroll " << endl;
    cout << "----|-------------------------|-----------|-------------|---------------" << endl;
    // Loop through activities and print details
    for (int i = 0; i < size; i++) {
        cout << setw(3) << i + 1 << " | ";
        cout << setw(23) << activities[i].name << " | "; //Display the name of the activities
        cout << setw(9) << getLocation(activities[i].location) << " | ";//Display the location
        cout << setw(11) << activities[i].max_enroll << " | "; //Display the maximum enrollment
        cout << setw(11) << activities[i].current_enroll << endl; //Display current enrolled
    }
    // Print table footer
    cout << "---------------------------------------------------------------------------" << endl;
}

// Display emails of participants for each activity.
void printEmails(const recCenter activities[], int size) {
    // Print header for the emails section
    cout << "Emails of Registered Participants for Each Activity:" << endl;
    cout << "-----------------------------------------------------" << endl;
    
    // Loop through each activity to print the emails
    for (int i = 0; i < size; i++) {
        // Display the activity name and location of the activity
        cout << activities[i].name << " " << getLocation(activities[i].location) << ":" << endl;
        // Check if there are any registered emails
        if (activities[i].emails.empty()) {
            cout << "No participants" << endl;
        } else {
            cout << activities[i].emails << endl;
        }
        // Line separator
        cout << "-----------------------------------------------------" << endl;
    }
}
// Allow user to register for an activity using their email
void registerAct(recCenter activities[], int size) {
    int choice;
    string email;

    // Display the list of activities with their current enrollment
    for (int i = 0; i < size; i++) {
        cout << i + 1 << ". " << activities[i].name << "Current Enrollment: "
             << activities[i].current_enroll << "/" << activities[i].max_enroll << endl;
    }

    // Ask the user to select an activity using its number
    cout << "Enter the number of the activity you want to register for: ";
    cin >> choice;

    // If user input is outside the range print a message and exit
    if (choice < 1 || choice > size) {
        cout << "Invalid choice." << endl;
        return;
    }

    // Use user choice minus 1 to get the correct array position
    recCenter& chosenActivity = activities[choice - 1];

    // Check If the chosen activity is already full and notity them
    if (chosenActivity.current_enroll >= chosenActivity.max_enroll) {
        cout << "Oops, the chosen activity is already full." << endl;
        return;
    }
    // Ask the user for their email to register for the activity
    cout << "Enter your email to register for " << chosenActivity.name << ": ";
    cin >> email;

    // If there are emails registered already add a semicolon to separator each
    if (!chosenActivity.emails.empty()) {
        chosenActivity.emails += ";";
    }
    chosenActivity.emails += email; //append the email to the emails lists

    // Update the count of the participants enrolled
    chosenActivity.current_enroll++;

    // Let the user know that their registration was successful
    cout << "You successfully registered for the " << chosenActivity.name << "." << endl;
}

// Asking the user to select an option from the menu and validate the choice entered
int getChoice() {
    int choice;

    do {
        // Display menu options
        cout << endl << "Menu:" << endl;
        cout << "1. View Activities" << endl;
        cout << "2. Register for an Activity" << endl;
        cout << "3. View Registered Emails" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        // Validate the choice is between 1 and 4
        if(choice < 1 || choice > 4) {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while(choice < 1 || choice > 4); // Repeat until the user enter a valid choice

    return choice;
}


