#include <iostream>
#include <string>

using namespace std;


class Event {
protected:

    string name;
    int securityLevel;

public:
    Event(const string& eventName, int secLevel) {
        name = eventName;
        securityLevel = secLevel;
    }

    virtual void displayDetails() const {
        cout << "Мероприятие: " << name << endl;
        cout << "Уровень безопасности: " << securityLevel << endl;
    }
};

class InternalEvent : public Event {
private:
    string department; 

public:
    InternalEvent(const string& eventName, int secLevel, const string& dept) : Event(eventName, secLevel) {
        department = dept;
    }

    void displayDetails() const override {
        cout << "Детали внутреннего мероприятия:" << endl;
        Event::displayDetails();
        cout << "Департамент: " << department << endl;
    }

};

class ExternalEvent : public Event {
private:
    string organizer; 

public:
    ExternalEvent(const string& eventName, int secLevel, const string& org) : Event(eventName, secLevel) {
        organizer = org;
    }

    void displayDetails() const override {
        cout << "Детали внешнего мероприятия:" << endl;
        Event::displayDetails();
        cout << "Организатор: " << organizer << endl;
    }

    
};

int main() {
    setlocale(LC_ALL, "rus");

    InternalEvent internal("Internal Seminar", 5, "HR Department");

    ExternalEvent external("Tech Conference", 8, "Tech Events Inc.");

    internal.displayDetails();

    external.displayDetails();

    return 0;
}
