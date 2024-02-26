#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Department {
private:
    string name;

public:
    Department(const string& deptName) {
        name = deptName;
    }

    string getName() const {
        return name;
    }
};


class Event {
protected:

    string name;
    int securityLevel;

public:

    Event(const string& eventName, int secLevel) {
        name = eventName;
        securityLevel = secLevel;
    }

    int getLevel() const {
        return securityLevel;
    }

    virtual void displayDetails() const {
        cout << "Мероприятие: " << name << endl;
        cout << "Уровень безопасности: " << securityLevel << endl;
    }

    virtual void enterEvent() const {
        cout << "Приглашаем вас на мероприятие " << name << " !" << endl;
    }

    static void compareSecurityLevels(const Event& event1, const Event& event2) {
        if (event1.getLevel() > event2.getLevel()) {
            cout << event1.name << " безопаснее, чем " << event2.name << endl;
        }
        else if (event1.getLevel() < event2.getLevel()) {
            cout << event2.name << " безопаснее, чем " << event1.name << endl;
        }
        else {
            cout << event1.name << " и " << event2.name << " имеют одинаковый уровень безопасности." << endl;
        }
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
        cout << "Участники: " << department << endl;
    }

    void enterEvent() const override {
        cout << "Приглашаем вас на мероприятие " << name << " с участником " << department << " !" << endl;
    }

};

class ExternalEvent : public Event {
private:
    string organizer;
    vector<Department> departments;

public:
    ExternalEvent(const string& eventName, int secLevel, const string& org) : Event(eventName, secLevel) {
        organizer = org;
    }

    void addDepartment(const Department& dept) {
        departments.push_back(dept);
    }

    void displayDetails() const override {
        Event::displayDetails();
        cout << "Организатор: " << organizer << endl;
        cout << "Участники мероприятия:" << endl;
        for (const auto& dept : departments) {
            cout << "- " << dept.getName() << endl;
        }
    }

    void enterEvent() const override {
        cout << "Приглашаем вас на мероприятие " << name << " организованное " << organizer << "!" << endl;
        cout << "Участники мероприятия:" << endl;
        for (const auto& dept : departments) {
            cout << "- " << dept.getName() << endl;
        }
    }

    
};

int main() {
    setlocale(LC_ALL, "rus");

    InternalEvent internal("Родительское собрание", 5, "Родители");

    ExternalEvent external("Технический семинар", 8, "Техническая корпорация");

    external.addDepartment(Department("Департамент Айти"));
    external.addDepartment(Department("Маркетинговый департамент"));

    internal.displayDetails();

    external.displayDetails();

    internal.enterEvent();

    external.enterEvent();

    Event::compareSecurityLevels(internal, external);

    return 0;
}
