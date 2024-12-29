#include <iostream>

using namespace std;

void printBinary(int, string);

int main() {
    int n;
    while (cin >> n) {
        cout << "printBinary n:" << endl;
        printBinary(n, "");
        cout << "----------------" << endl;
    }

    return 0;
}


void printBinary(int n, string s) {
    if (n <= 0) {
        cout << s << endl;
    } else {
        printBinary(n - 1, s + "1");      
        printBinary(n - 1, s + "0");
    }
}