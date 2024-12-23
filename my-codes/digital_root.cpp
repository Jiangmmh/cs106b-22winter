#include <iostream>

using namespace std;

int sumOfDigits(int n) {
    if (n < 10) {
        return n;
    } else {
        return sumOfDigits(n / 10) + n % 10;
    }
}


int digitalRoots(int n) {
    if (n < 10) {
        return n;
    } else {
        return digitalRoots(sumOfDigits(n));
    }
}

int 
main(int argc, char* argv[])
{
    int n;
    cin >> n;
    cout << "The digital roots is: " << digitalRoots(n) << endl;

    return 0;
}