// **********************************************************
// Name:         Masumbuko Alulea
// Date:         October 09 2023

#include <iostream>
#include <cstring>
#include <iomanip>
#include <fstream>
using namespace std;

// Constants for the size of the 2D array
const int ROWS = 5; // Number of activities
const int COLS = 4; // Number of school years

//Indices to keep track of the activities with the highest and lowest participation
int highestIndex = 0;
int lowestIndex = 0;

const int CHARACTERS = 50;

//prototypes
void readData( char activityNames[ROWS][CHARACTERS],int my_array[ROWS][COLS]);
void total_each_year(int my_array[ROWS][COLS], int yearlyTotal[COLS]);
void total_each_activity(int my_array[ROWS][COLS], int activityTotal[ROWS]);
int total_partic(int my_array[ROWS][COLS]);
int highest_partic(int my_array[ROWS][COLS]);
int lowest_partic(int my_array[ROWS][COLS]);
void write_file_results(char activityNames[ROWS][CHARACTERS],int my_array[ROWS][COLS], int yearlyTotal[COLS], int activityTotal[ROWS], int overallTotal, int highestp, int lowestp);


int main() {
    
    char activityNames[ROWS][CHARACTERS]; // 2D array to hold the names of the activities
    int yearlyTotal[COLS] = {0}; //This holds the total participation for each year
    int activityTotal[ROWS] = {0}; // Holds the total participation for each activity
    int my_array[ROWS][COLS] = {0}; //2D array to store participation for each activity and years
 
    readData(activityNames, my_array); //call the read data function
    total_each_year(my_array, yearlyTotal); // Get totals for each year
    total_each_activity(my_array, activityTotal); // Get totals for each activity
    int overallTotal = total_partic(my_array); //Get the overall total
    // Determine the highest and lowest participation
    int highestP = highest_partic(my_array);
    int lowestP = lowest_partic(my_array);
    
    // Write all the results to the results.txt file
    write_file_results(activityNames,my_array, yearlyTotal, activityTotal, overallTotal, highestP, lowestP);
    

    return 0;
}

//Reads activity names in 2D array from the file into activityNames and associated integers into my 2 dimensional array named my_array.
void readData( char activityNames[ROWS][CHARACTERS],int my_array[ROWS][COLS])
{
    ifstream my_file; //reading data in a file
    my_file.open("activities2.txt");//opening the file
    // Check if the file was successfully opened
    if(!my_file)
    {
        cout<<"Unable to open the file"<<endl;// Print an error message if the file doesn't exist.
        exit(102); //error code
    }
    // Loop through each row of the 2D array
    for(int i = 0; i< ROWS; i++)
    {
        my_file.getline(activityNames[i],CHARACTERS); //store the names in activity names array
        for(int j = 0; j<COLS;j++)
        {
            my_file>>my_array[i][j];
                if(my_array[i][j]<0)// Check if any number is negative
                {
                    //print a message and show where those negative values are.
                    cout<<"Negative number has been detected "<<"Row: "<<(i+1)<<" Column: "<<(j+1)<<endl;
                    my_array[i][j] = 0;// Set negative values to zero if there's any
                }
        }
        // Ignore up to 1000 characters or until a newline in the file
       my_file.ignore(1000,'\n');
    }
    cout<<"File opened successfully"<<endl;
    
    my_file.close();// Close the file

    return;
}
// Function to calculate the total participation for each year
void total_each_year(int my_array[ROWS][COLS], int yearlyTotal[COLS]) {

    // Loop through each column, which represents a year
    for(int i = 0; i < COLS; i++) {
        yearlyTotal[i] = 0;// Initialize the yearly total to zero
        
        // Loop through each row for the current column
        // to sum up the participations of all activities for that year
        for(int j = 0; j < ROWS; j++)
        {
            yearlyTotal[i] += my_array[j][i]; // Add the participation number to yearly total.
        }
    }
    return;
}
// Function to calculate the total participation for each activity
void total_each_activity(int my_array[ROWS][COLS], int activityTotal[ROWS])
{
    // Loop through each row which represents an activities
    for(int i = 0; i < ROWS; i++) {
        // Initialize the total participation to zero for the activity
        activityTotal[i] = 0;
        // Loop through each column and the current row
        // to add the participations for that activity for all years.
        for(int j = 0; j < COLS; j++) {
            
            // Add the participation number from the current year to activityTotal
            activityTotal[i] += my_array[i][j];
        }
    }
    
    return;
}
// Function to get the total of all participations.
int total_partic(int my_array[ROWS][COLS]) {
    
    int total = 0;  // Initialize the overall total to zero
    // Iterate through each element of the 2D array using nested loops.
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            total += my_array[i][j];  // Add the current value to the total.
        }
    }

    return total; //return total participation
}
// Function to determine the highest participation value across all the activities and the years.
// Function to find the highest sum of participation in a 2D array.
int highest_partic(int my_array[ROWS][COLS]) {
    int highest = 0;
    int sum;
    
    for (int i = 0; i < ROWS; i++) {
        sum = 0;

        // Sum participation for the current row
        for (int j = 0; j < COLS; j++) {
            sum += my_array[i][j];
        }

        // Update the highest sum if necessary
        if (sum > highest) {
            highest = sum;
        }
    }

    return highest; //return the highest participation
}

// Function to determine the lowest participation value across all the activities and the years.
int lowest_partic(int my_array[ROWS][COLS]) {
    int temp = 0;
    int lowest;

    // Calculate the total participation for the first activity to initialize lowest
    for(int j = 0; j < COLS; j++) {
        temp += my_array[0][j];
    }

    lowest = temp; // Initialize the lowest with the total of the first activity
    lowestIndex = 0;  // Initialize with the index of the first activity

    // Start from the second activity since we have already went through the first one
    for(int i = 1; i < ROWS; i++) {
        temp = 0;  // Reset temp for each new activity
        for(int j = 0; j < COLS; j++) {
            temp += my_array[i][j];  // Calculate total participation for this activity
        }

        if(temp < lowest) {
            lowest = temp;  // Update lowest if this activity's total is lesser
            lowestIndex = i;  // The index of the activity with lowest participation
        }
    }
    return lowest;  // Return the lowest participation value
}
// Writes all the results to a file named: 'resultsfile.txt'.
void write_file_results(char activityNames[ROWS][CHARACTERS],int my_array[ROWS][COLS], int yearlyTotal[COLS], int activityTotal[ROWS], int overallTotal, int highestp, int lowestp)
{
    const char grade_leves[COLS][CHARACTERS] = {"Freshmen", "Sophomores", "Juniors", "Seniors"};
    

    ofstream result_file; //writing the results to the file
    result_file.open("resultsfile.txt");

    // Writing the header
    result_file << "                                 Hobo Day Activities participation       "<< endl<<endl;
    result_file << setw(20) << left << "Activities";
    for (int i = 0; i < COLS; i++) {
        result_file << setw(13) << right << grade_leves[i]; //print the grade levels and format it using the setw function
    }
    result_file << setw(12) << "Total" << endl;
    result_file << "------------------------------------------------------------------------------------" << endl;
   
    // Loop through all activities
    for (int i = 0; i < ROWS; i++) {
       
        result_file << setw(22) << left << activityNames[i];
        // Loop to write participation for the years of the current activity
        for (int j = 0; j < COLS; j++) {
            result_file << setw(12) << right << my_array[i][j];
        }
        // Write total participation for the current activity
        result_file << setw(10) << right << " " << activityTotal[i] << endl;
    }

    // A line for separation
    result_file << "------------------------------------------------------------------------------------" << endl;

    result_file << endl << "Yearly Totals: ";

    // Loop through each year (column) to write the total participation for that year
    for (int i = 0; i < COLS; i++) {
        // Output the yearly total for the current year with 12 spaces to the right
        result_file << setw(12) << right << yearlyTotal[i];
    }

    // Separate the data in the file
    result_file << endl << endl;

    // Check the highest participation activity based on the index and output the corresponding activity name
    switch(highestIndex) {
        case 0:
            result_file << "Highest Participation: Hobo Button Day";
            break;
        case 1:
            result_file << "Highest Participation: Lil’s Food Drive";
            break;
        case 2:
            result_file << "Highest Participation: Will’s Football Toss";
            break;
        case 3:
            result_file << "Highest Participation: Hobo Stew Feed";
            break;
        case 4:
            result_file << "Highest Participation: Band Rally";
            break;
        default:
            // If the highestIndex doesn't match any known activity print unknown
            result_file << "Highest Participation: Unknown";
            break;
    }
    // write the highest participation along with the name of the activity
    result_file << ": " << highestp << " participants." << endl;
    
    // Check the highest participation activity based on the index and output the corresponding activity name

    switch(lowestIndex) {
        case 0: result_file << "Lowest Participation: Hobo Button Day";
            break;
        case 1: result_file << "Lowest Participation: Lil’s Food Drive";
            break;
        case 2: result_file << "Lowest Participation: Will’s Football Toss";
            break;
        case 3: result_file << "Lowest Participation: Hobo Stew Feed";
            break;
        case 4: result_file << "Lowest Participation: Band Rally";
            break;
        default: result_file << "Lowest Participation: Unknown Activity";
            break;
    }
    result_file << ": " << lowestp << " participants." << endl; // write the lowest participation along with the name of the activity
    result_file << "Overall Total: " << overallTotal << endl<<endl; // Write overall total to the file

    result_file.close();  // Close the file
}
