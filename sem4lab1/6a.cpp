#include <iostream>

using namespace std;

class Balance {
private:
    double balance;

public:
    Balance(double current) {
        balance = current;
    }

    void increase(double sum) {
        if (sum > 0) {
            balance += sum;
            cout << "Пополнение на " << sum << " успешно!" << endl;
        }
        else {
            cout << "Сумма для пополнения должна быть положительной" << endl;
        }
    }

    void decrease(double sum) {
        if (sum > 0 && balance >= sum) {
            balance -= sum;
            cout << "Списание " << sum << " выполнено успешно!" << endl;
        }
        else {
            cout << "Недостаточно средств для списания!" << endl;
        }
    }

    void getBalance() {
        cout << "Текущий баланс: " << balance << endl;
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    Balance balance(1000);

    balance.getBalance();

    balance.increase(500);
    balance.getBalance();

    balance.decrease(200);
    balance.getBalance();

    balance.decrease(2000);

    return 0;
}