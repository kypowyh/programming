#include <iostream>
#include <string>
#include <regex>


using namespace std;

class User {
private:
    string username;
    string password;
    string email;
    int age;

    bool isValidEmail(const string& email) const {
        const regex pattern(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
        return regex_match(email, pattern);
    }

    void setEmail(const string& newEmail) {
        if (isValidEmail(newEmail)) {
            email = newEmail;
        }
        else {
            cerr << "Неверный формат почты!" << endl;
            email = "null";

        }
    }

public:

    void UserInfo() const {
        cout << "Имя: " << username << endl;
        cout << "Почта: " << email << endl;
        cout << "Возраст: " << age << endl;
    }

    User(const string& name, const string& pass, const string& mail, int newage) {
        username = name;
        password = pass;
        setEmail(mail);
        age = newage;
    }

    bool authenticate() const {
        string inputUsername, inputPassword;
        while (true) {
            cout << "Введите имя: ";
            cin >> inputUsername;
            cout << "Введите пароль: ";
            cin >> inputPassword;
            if (username == inputUsername && password == inputPassword) {
                cout << "Добро пожаловать, " << username << "!" << endl;
                return true;
            }
            else {
                cout << "Неверное имя пользователя или пароль!" << endl;
            }
        }
    }

    void setPassword() {
        string newPass;
        cout << "Введите новый пароль: ";
        cin >> newPass;
        password = newPass;
    }

    string getUsername() const {
        return username;
    }

};

int main() {

    setlocale(LC_ALL, "rus");

    User user("name", "pass", "userexample.com", 25);

    user.authenticate();

    user.setPassword();

    user.UserInfo();

    return 0;
}
