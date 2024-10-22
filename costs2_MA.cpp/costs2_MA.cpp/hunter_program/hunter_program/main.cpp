// Hunter Hagedorn
// 9/24/2023
// CSC 250
// Programming Assignment 4 (Sorting and Searching Arrays with Pointers)
// a program that allows the user to enter a student’s ID and displays their cost using pointers

#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;


int readNumber(void);// function for reading first number in the file
int readID(void); // Function prototype for reading user ID
void readData(int* &id, double* &cost, int size); // Function prototype for reading data
void sortParallelArrays(int* id, double* cost, int size); // Function prototype for sorting arrays
int binarySearch(const int array[], int numElems, int searchElems); // Function prototype for binary search
void showResult(int id[], double cost[], int value, int searchValue); // Function prototype for displaying results

int main() {
    int size = readNumber(); // sets size of array with first number in file

    double* cost = new double[size]; // dynamically allocate memory for cost
    int* id = new int[size]; // dynamically allocate memory for id


    char choice;

    readData(id, cost, size); // reads user data from file
    sortParallelArrays(id, cost, size); // binary sorts the two arrays in parallel

    do {
        int searchValue = readID(); // read ID ready for function

        int value = binarySearch(id, size, searchValue); // get search ready
        showResult(id, cost, value, searchValue); // shows end result

        cout << "Do you want to keep searching? (y/n): ";
        cin >> choice; // loop asks until user inputs n

        if (choice == 'n' || choice == 'N') {
            cout << "Thank You Have a Great Day!" << endl;
            delete[] cost;
            delete[] id;
            return 0;
        }

    } while (choice == 'Y' || choice == 'y'); // y keeps loop going

    return 0;
}
int readNumber(void) {
    int number = 0;
    ifstream myFile;
    myFile.open("/Users/makingaberto/Desktop/C:C++/MK C++/Files_C++/costs2_MA.cpp/costs2_MA.cpp/hunter_program/hunter_program/cost2.txt");
    
    if (!myFile) {
        cout << "File Was Unable to Open." << endl;
        exit(102); // exits with error code
    }

    if (myFile) {
        myFile >> number;
        
        myFile.close();
    }
    
    return number;
}

int readID(void) {
    int id; // int for ID

    cout << "Please Enter Your ID!: "; // prints to ask to enter id
    cin >> id; // takes in the id

    return id; // returns id
}

void readData(int* &id, double* &cost, int size) {
    ifstream inFile("/Users/makingaberto/Desktop/C:C++/MK C++/Files_C++/costs2_MA.cpp/costs2_MA.cpp/hunter_program/hunter_program/cost2.txt"); // file directory for user ID text file

    if (!inFile) {
        cout << "File Was Unable to Open." << endl;
        exit(102); // exits with error code
    }

    int count = 0; // sets count to 0
    id = new int[size]; // new int called size linked to ID
    cost = new double[size]; // new double called size linked to cost

    while (inFile >> id[count] && inFile >> cost[count] && count < size) {
        count++; // increase count
    } // stay in file until they find what needed info

    inFile.close(); // closes file
}

int binarySearch(const int array[], int numElems, int searchElems) { // binary search algorithm
    int first = 0;
    int position = -1;
    int last = numElems - 1;
    int middle;

    while (position == -1 && first <= last) {
        middle = (first + last) / 2; // splits in half to limit numbers
        if (searchElems == array[middle]) {
            position = middle; // then position is middle
        }
        else if (searchElems > array[middle]) { // if search elems is greater than middle array
            first = middle + 1; // search right half by adding 1
        }
        else {
            last = middle -1; // subtracts 1 and searches left
        }
    }

    return position; // returns position
}

void sortParallelArrays(int* id, double* cost, int size) {
    bool swap; // passes with array until it can't
    int tempID;
    double tempCost;

    do
    {
        swap = false;
        for (int i = 0; i < size-1; i++)
        {
            // Swap for both ID
            if (*(id + i) > *(id + i + 1))
            {
                tempID = *(id + i);
                *(id + i) = *(id + i + 1);
                *(id + i + 1) = tempID;
                //swap the cost
                tempCost = *(cost + i + 1);
                *(cost + i + 1) = *(cost + i);
                *(cost + i) = tempCost;
                swap = true;
            }
        }
    } while (swap);
}

void showResult(int id[], double cost[], int value, int searchValue) { // shows the end results
    if (value == -1) { // if ID was not found
        cout << "A User with the ID: " << searchValue << " Was Not Found" << endl;
    }
    else {
        cout << "A User With That ID Was Found:" << endl;
        cout << "User ID      User Balance" << endl;
        cout << "ID: " << id[value] << setw(12) << right << "Balance: " << cost[value] << endl;
        // prints in clean order the user's info
    }

    return;
}
