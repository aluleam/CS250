#include "CharList.h"
#include <iostream>
using namespace std;

//Default constructor: Initializes an empty CharList
CharList::CharList() : head(nullptr) { }

// Creates a new CharList as a copy of the other one
CharList::CharList(const CharList &copyObject) : head(nullptr) {
    // Loop through the list and copy the characters
    for (ListNode *current = copyObject.head; current != nullptr; current = current->next)
    {
        appendNode(current->value);
    }
}
//Destroy the list
CharList::~CharList() {
    // Loop through the list and delete each node
    while (head != nullptr) {
        ListNode *current = head; // store the current node
        head = head->next; // Move to the next node
        delete current; // Delete the stored current node
    }
}
// Add characters to the end of the list
void CharList::appendNode(char value)
{
    // Create a new node with the value passed in
    ListNode *newNode = new ListNode(value);

    if (head == nullptr) { // checking If the list is empty
        head = newNode;
    } else {
        //If the list is not empty go through it
        ListNode *current = head;
        while (current->next != nullptr) {
            current = current->next; // Move to the next node
        }
        current->next = newNode;
    }
}

// Inserts a new character
void CharList::insertNode(char myvalue) {
    ListNode *newNode = new ListNode(myvalue); //Create new node

    // Insert at start if list is empty or value is smallest
    if (head == nullptr || head->value >= myvalue) {
        newNode->next = head;
        head = newNode;
    } else {
        ListNode *current = head;
        while (current->next != nullptr && current->next->value < myvalue) {
            current = current->next;
        }
        // Insert new node
        newNode->next = current->next;
        current->next = newNode;
    }
}


// Finds a character in the list and delete it.
void CharList::deleteNode(char value) {
    // If the list is empty we can't delete anything
    if (head == nullptr)
        return;

    ListNode *current = head;
    ListNode *previous = nullptr;

    // If the first character is the one we are looking for, delete it
    if (head->value == value)
    {
        head = head->next;
        delete current;
    }
    else
    {
        // Otherwise look for it in the list
        while (current != nullptr && current->value != value)
        {
            previous = current;
            current = current->next;
        }
        if (current != nullptr) 
        {
            previous->next = current->next;
            delete current;
        }
    }
}

// Displays all the characters in the list
void CharList::displayList() const {
    ListNode *current = head; // Start from the beginning of the list
    int nodePosition = 1; // Keeping track of the position of the nodes

    // Loop through the entire list and print the characters
    while (current != nullptr) {
        cout << "Node " << nodePosition++ << ": " << current->value <<endl;
        current = current->next; // Move to the next node.
    }
}

// Displaying the list in reverse
void CharList::displayReverse(ListNode *node) const {
    if (node == nullptr) { //if the node is nullptr end the recursion
        return;
    }
    // Recursive call with the next node
    displayReverse(node->next);

    //print the value of the current node
    cout << node->value << " ";
}

// Public function to display the entire list in reverse order
void CharList::displayReverse() const
{
    displayReverse(head); //Call for the private recursive function from the start
    cout <<endl;
    
}
