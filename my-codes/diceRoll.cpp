#include <iostream>
using namespace std;

void diceRoll(int n, string s) {
    if (n <= 0) {
        cout << s << endl;
    } else {
        for (int i = 1; i <= 6; i++) {
            diceRoll(n - 1, s +  to_string(i));
        }
    }
}


int main (){
    int n;
    while (cin >> n) {
        cout << "diceRoll n:" << endl;
        diceRoll(n, "");
        cout << "----------------" << endl;
    }
    return 0;
}