#include <iostream>

using namespace std;

void printDecimal(int, string);

int main() {
    int n;
    while (cin >> n) {
        cout << "printDecimal n:" << endl;
        printDecimal(n, "");
        cout << "----------------" << endl;
    }

    return 0;
}


void printDecimal(int n, string s) {
    if (n <= 0) {
        cout << s << endl;
    } else {
        for (int i = 0; i < 10; i++) {
            printDecimal(n - 1, s + to_string(i));
        }
    }
}