// Event.cpp
#include "Event.h"
#include <iostream>

Event::Event() {
    name = "";
    attendance = 0;
    type = GENERAL;
}

Event::Event(const string theName, EventType theType, int Attend) {
    name = theName;
    type = theType;
    attendance = Attend;
}

int Event::getAttendance() const {
    return attendance;
}

string Event::getName() const {
    return name;
}

EventType Event::getType() const {
    return type;
}

void Event::setAttendance(int attend) {
    if (attend >= 0) {
        attendance = attend;
    } else {
        cout << "Invalid attendance value" << endl;
    }
}

void Event::setName(const string theName) {
    if (theName.empty()) {
        cout << "Mmh it looks like the name is missing" << endl;
    } else {
        name = theName;
    }
}

void Event::setType(EventType theType) {
    if (theType < GENERAL || theType > CONCERT) {
        cout << "Invalid event type" << endl;
    } else {
        type = theType;
    }
}

