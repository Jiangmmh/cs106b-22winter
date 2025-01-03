#include <iostream>

using namespace std;
 
constexpr int sz() {
    return 10;
}

int main () {
    const int size = sz();
    cout << size << endl;
    return 0;
}