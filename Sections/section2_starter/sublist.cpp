#include "vector.h"
#include <iostream>
#include "console.h"
#include "strlib.h"

using namespace std;

void helper(Vector<string> &list, Vector<string> &sofar) {
    if (list.isEmpty()) {
        cout << sofar << endl;
    } else {
        string first = list.remove(0);
        sofar.add(first);
        helper(list, sofar);

        sofar.remove(sofar.size() - 1);
        helper(list, sofar);

        list.insert(0, first);
    }
}


void sublist(Vector<string> &list) {
    Vector<string> sofar;
    helper(list, sofar);
}



int main() {
    cout << "SubList:" << endl;
    Vector<string> list = {"Jane", "Bob", "Matt", "Sara"};
    sublist(list);

    return 0;
}
