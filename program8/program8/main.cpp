#include "CharList.h"
#include <iostream>

using namespace std;

int main() {
    CharList list;

    // Testing the appendNode function
    cout << "Appending characters"<<endl;
    list.appendNode('A');
    list.appendNode('B');
    list.appendNode('C');
    list.appendNode('D');
    list.displayList();
    cout<<endl;

    //Testing the insertNode function
    cout <<"Inserting character E"<<endl;
    list.insertNode('E');
    list.displayList();
    cout<<endl;

    // Testing delete function
    cout << "Deleting C from the list"<<endl;
    list.deleteNode('C');
    list.displayList();//Display the list to ensure it was deleted
    cout<<endl;
    //Test display Reverse wrapper
    cout << "Displaying the list in reverse order"<<endl;
    list.displayReverse();
    cout<<endl;
    
    //Test copy constructor
    CharList theCopy(list);
    cout << "Displaying copied list"<<endl;
    theCopy.displayList();
    cout<<endl;
    //Test displayReverse on the list we copied
    cout << "Displaying copied list in reverse"<<endl;
    theCopy.displayReverse();
    cout<<endl;

    //Ensuring the original list was not changed
    cout << "Original list"<<endl;
    list.displayList();
    cout<<endl;
    
    // Test deleteNode on the copied list
    cout << "Deleting character 'D' from the copied list"<<endl;
    theCopy.deleteNode('D');
    theCopy.displayList(); //display the copied list after deleting a character
    cout<<endl;
    //Test destructor by creating a local scope
    {
        cout << "Creating a new CharList in a local scope"<<endl;
        CharList localList;
        localList.appendNode('M');
        localList.appendNode('N');
        localList.appendNode('O');
        localList.displayList();
        cout << "The local list should be destroyed"<<endl;
    }
  
    cout << "The end of the test program. TOODLES!!!!!"<<endl<<endl;
    return 0;
}

