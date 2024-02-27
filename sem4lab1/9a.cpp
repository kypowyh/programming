

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int main() {

    auto dictionary = unordered_map<string, vector<int>>{
        {"first", {1, 2, 3}},
        {"second", {4, 5, 6}},
        {"third", {7, 8, 9}}
    };

    for (const auto& pair : dictionary) {
        cout << pair.first << ": ";
        for (const auto& value : pair.second) {
            cout << value << " ";
        }
        cout << endl;
    }

    return 0;
}