#include <iostream>
#include <string>

using namespace std;

auto repeatString(int numRepeats, const string& str) {
    string result;
    for (int i = 0; i < numRepeats; ++i) {
        result += str;
    }
    return result;
}

int main() {
    auto str = "Hello!";
    auto repeated = repeatString(3, str);
    cout << repeated << endl; 
    return 0;
}