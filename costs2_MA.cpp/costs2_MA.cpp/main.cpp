// **********************************************************
// Program:      costs2_MA.cpp
// Name:         Masumbuko Alulea
// Date:         September 26 2023
// ***********************************************************

#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

//Prototypes
int read_first_number(void);
void readData(int* &ID, double* &cost, int size);
void sortParallelArrays(int mat_ID[],double mat_cost[],int size);
int readID(void);
int binarySearch(const int array[],int num_elem, int search_elem);
void showResult(int id[], double cost[], int index, int search_value);


int main() {
    
    //initialize the size of arrays with the first number in the file.
    int size = read_first_number();
    
// Pointers for ID and cost arrays
    int* id;
    double* cost;

    // Read data from the file into dynamically allocated arrays
    readData(id, cost, size);
    
    // Sort the ID array along with the cost
    sortParallelArrays(id, cost, size);
     
    char choice;
    //As long as the choice is y or Y do the code within the loop
    do
    {
        // Read the id from the user
        int search_value = readID();
        
        // initialize the value with the index returned of the ID from the binary search
        int value = binarySearch(id, size, search_value);
        
        // Display the result
        showResult(id, cost, value, search_value);

        cout << "Would you like to search again? Please enter y(yes) or n(no)?: ";
        cin >> choice;
        
        // Handling the choice of the user
        if (choice == 'n' || choice == 'N')
        {
            cout << "You are done searching!!!" << endl;
            break;
        }
        //If it's something other than y or Y than there was an invalid input
        else if (choice != 'y' && choice != 'Y')
        {
            cout << "Invalid input!" << endl;
        }
    } while (choice == 'Y' || choice == 'y');

    // Deallocate memory once were are done
    delete[] id;
    delete[] cost;

    return 0;
}

// Function to read the first number from the file which will be the size of the arrays
int read_first_number(void)
{
    int number = 0;
    ifstream myfile; // For an existing file
    myfile.open("cost2.txt"); //Open the file
    
    // Error handling for file opening
    if (!myfile)
    {
        cout << "Unable to open the file." << endl;
        exit(102);
    }
    
    // If the file opens read the first number
    if (myfile)
    {
        myfile >> number; // Read the first number from the file
        myfile.close(); //close the file
    }
    
    return number; //return the we read
}

// Function to read the ID and cost data from the file into dynamically allocated arrays
void readData(int* &ID, double* &cost, int size)
{
    // Dynamically allocate the arrays based on the size provided
    ID = new int[size];
    cost = new double[size];
    
    int count = 0;
    ifstream myFile("cost2.txt");// open an existing file
    
    // Error handling for file opening
    if (!myFile)
    {
        cout << "Unable to open the file." << endl;
        exit(102);
    }

    // Read ID and cost data from the file
    while (myFile >> ID[count] && myFile >> cost[count] && count < size)
    {
        count++; //Increment count to store data in the next position
    }
    
    myFile.close(); // close the file after reading the data
}

// Function to sort ID and cost arrays in parallel using the Bubble Sort algorithm
void sortParallelArrays(int *ID, double* cost, int size)
{
    //float temp_cost;
   // int temp_id;
    bool swap_t;
    
    do
    {
        swap_t = false;
        for (int j = 0; j < size-1; j++)
        {
            // Swap for both ID
            if (*(ID + j) > *(ID + j + 1))
            {
                swap(*(ID+j),*(ID + j + 1));
                swap(*(cost+j),*(cost+j+1));
                swap_t = true;
            }
        }
    } while (swap_t);
}

// Function to read an ID from the user
int readID(void)
{
    int ID; // declare an integer for ID
    cout << "Enter the ID: ";
    cin >> ID; // prompt to enter the ID
    return ID; //return the ID
}

// Binary search function to find the index of the entered ID
int binarySearch(const int array[], int num_elem, int search_elem)
{

    int position = -1; // Initialize starting position as -1
    int first, last;
    first = 0; // Start of the search range
    last = num_elem - 1; // End of the search range
    int middle; //middle element

    // Search while the range is valid
    while (position == -1 && first <= last)
    {
        middle = (first + last) / 2;
        if (search_elem == array[middle])
        {
            position = middle; // Found it
        }
        else if (search_elem > array[middle])
        {
            first = middle + 1; // Search right half
        }
        else
        {
            last = middle - 1; //Search left half
        }
    }
    
    return position; // Return the position, or -1 if not found
        
}

// Function to display the result of the search
void showResult(int id[], double cost[], int index, int search_value)
{
    // Display the table headers
    cout << "Material ID     Material Cost" << endl;
    cout << "--------------\t---------------" << endl;

    // Set decimal precision for cost
    cout << fixed << setprecision(2);

    // Check if the id was found
    if (index != -1)
    {
        // Display the found ID and its corresponding cost
        cout << "ID: " << id[index] << setw(12) << right << "Cost: " << cost[index] << endl;
    }
    else
    {
        // Display a message if the ID was not found
        cout << "ID not found" << endl;
    }

}
