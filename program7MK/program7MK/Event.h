// Event.h
#ifndef Event_h
#define Event_h

#include <string>
using namespace std;

enum EventType { GENERAL, DINNER, CONCERT };

class Event {
private:
    string name;
    int attendance;
    EventType type;

public:
    Event();
    Event(const string theName, EventType theType, int Attend);
    int getAttendance() const;
    string getName() const;
    EventType getType() const;
    void setAttendance(int attend);
    void setName(const string theName);
    void setType(EventType type);
};

#endif

