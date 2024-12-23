
#include <iostream>

using namespace std;

string aSequenceOfOrder(int n);
string bSequenceOfOrder(int n);

string aSequenceOfOrder(int n) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    if (n == 0) 
        return "A";
    return aSequenceOfOrder(n - 1) + bSequenceOfOrder(n - 1);
}

string bSequenceOfOrder(int n) {
    /* TODO: Delete this line and the next two lines, then implement this function. */
    if (n == 0) 
        return "B";
    return bSequenceOfOrder(n - 1) + aSequenceOfOrder(n - 1);
}

int main() {
    int n;
    while (true) {
        cout << "Enter a number: ";
        cin >> n;
        if (n < 0) {
            break;
        }
        cout << "A sequence of order " << n << ": " << aSequenceOfOrder(n) << endl;
        cout << "B sequence of order " << n << ": " << bSequenceOfOrder(n) << endl;
    }

    return 0;
}