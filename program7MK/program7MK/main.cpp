

#include <iostream>
#include <iomanip>
#include "Event.h"


int displayMenu();
void displayType(Event events[], int size, EventType theType);
void displayAll(Event events[], int size);
void UserEdit (Event events[], int size);
void calcAverage(Event events[], int size);


int main() {
    int userChoice;
    const int size = 8;
    Event events[size] =
    {
        Event("New Year’s Party", CONCERT, 500),
        Event("Sweetheart Gala", DINNER, 250),
        Event("Jansen-Mendez Wedding", GENERAL, 350),
        Event("Christmas Party", DINNER,459),
        Event("New Year’s Party", CONCERT, 500),
        Event("Sweetheart Gala", DINNER, 250),
        Event("Jansen-Mendez Wedding", GENERAL, 350),
        Event("Christmas Party", DINNER,459)
    };
    Event myclass;
    
    
    do{
        userChoice = displayMenu();
        switch (userChoice) {
            case 1:displayType(events,size,DINNER);
                break;
            case 2:displayAll(events, size);
                break;
            case 3: UserEdit(events, size);
                break;
            case 4: calcAverage(events,size);
                break;
            case 5: cout<<"Exiting the program..."<<endl;
            default:
                cout<<"Invalid";
                break;
        }
    }while(userChoice!=5);
    
    

   
   
    return 0;
}




void Event::setAttendance(int attend) {
    if (attend >= 0) {
        attendance = attend;
    } else {
        cout << "Invalid attendance value" << endl;
    }
}


void Event:: setName(const string theName)
{
    if(theName.empty())
    {
        cout<<"Mmh it looks like the name is missing"<<endl;
    }
    else
        name = theName;
    
}

void Event::setType(EventType theType)
{

    if (theType < GENERAL || theType > CONCERT)
    {
        cout << "Invalid event type" << endl;
    }
    else
        type = theType;
        
}

void displayType(Event events[], int size, EventType type)
{
    for(int i = 0; i<size; i++)
    {
        if(events[i].getType()== type)
        {
            cout<<events[i].getName()<<endl;
            
        }
    }
}

void displayAll(Event events[], int size)
{
    cout <<endl<<endl<<"Displaying all the events along with their details" << endl;
    cout << "-------------------------|--------------|---------------|-------" << endl;
    cout << left << setw(25) << "NAME OF THE EVENT" << setw(15) << "| TYPE" << setw(20) << "| ATTENDANCE    |Indices" << endl;
    cout << "-------------------------|--------------|---------------|-------" << endl;

    for (int i = 0; i < size; i++)
    {
        // Name
        cout << left << setw(25)<<events[i].getName();
        

        // Type
        switch (events[i].getType()) {
            case GENERAL:
                cout << setw(15) << "| GENERAL";
                break;
            case DINNER:
                cout << setw(15) << "| DINNER";
                break;
            case CONCERT:
                cout << setw(17) << "  | CONCERT";
                break;
            default:
                cout << setw(15) << "| Invalid";
                break;
        }

        // Attendance
        cout << right << setw(2) << "| " << events[i].getAttendance()<<setw(12)<<"|";
        cout<<i+1<<endl;
    }
    calcAverage(events, size);

    cout << "----------------------------------------------------------------" << endl;
}

void UserEdit(Event events[], int size) {
    int eventIndex, newAttendance, typeInput;
    string newName;
    EventType newType;

    // Display all events with indices
    displayAll(events, size);
    cout << "Select the event to edit (by index number): ";
    cin >> eventIndex;
    eventIndex--; // Adjusting for array indexing

    // Validate the selected index
    if(eventIndex <0 || eventIndex >= size) {
        cout << "Invalid event selection." << endl;
        return;
    }

    // Display selected event
    cout << "Selected Event: " << events[eventIndex].getName() << endl;
    cout << "1. Edit Name" << endl;
    cout << "2. Edit Type" << endl;
    cout << "3. Edit Attendance" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    // Handle the chosen edit operation
    switch(choice) {
        case 1:
            cout << "Enter new name: ";
            cin.ignore(); // Clearing the input buffer before getline
            getline(cin, newName);
            events[eventIndex].setName(newName);
            break;
        case 2:
            cout << "Enter new type (0 for GENERAL, 1 for DINNER, 2 for CONCERT): ";
            cin >> typeInput;

            // Validate the input type
            if(typeInput < 0 || typeInput > 2) {
                cout << "Invalid type." << endl;
            } else {
                newType = static_cast<EventType>(typeInput);
                events[eventIndex].setType(newType);
            }
            break;
        case 3:
            cout << "Enter new attendance: ";
            cin >> newAttendance;
            events[eventIndex].setAttendance(newAttendance);
            break;
        default:
            cout << "Invalid choice." << endl;
    }
}



void calcAverage(Event events[], int size)
{
    int total = 0, average = 0;
    
    for(int i = 0; i<size; i++)
    {
        
        total += events[i].getAttendance();
        
    }
    average = total/size;
    cout<<endl<<endl<<"Displaying the total attendance and the average"<<endl;
    cout<<"-------------------------------"<<endl;
    cout<<"The total attendance is: "<<total<<endl;
    cout<<"The average is: "<<average<<endl;
    cout<<"-------------------------------"<<endl;
}
