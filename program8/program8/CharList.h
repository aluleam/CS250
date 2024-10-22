#ifndef CHARLIST_H
#define CHARLIST_H

class CharList {
private:
    struct ListNode {
        char value;
        ListNode *next;
        ListNode(char val, ListNode *nextNode = nullptr) {
            value = val;
            next = nextNode;
        }
    };
    ListNode *head;

    void displayReverse(ListNode *node) const; // Private recursive function

public:
    CharList(); // Default constructor
    CharList(const CharList &copyObj); // Copy constructor
    ~CharList(); // Destructor

    void appendNode(char value);
    void insertNode(char value);
    void deleteNode(char value);
    void displayList() const;
    void displayReverse() const; // Public wrapper function for recursion
};

#endif

