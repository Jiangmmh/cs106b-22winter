#include "vector.h"
#include <iostream>
#include "console.h"
#include "strlib.h"

using namespace std;

void helper(Vector<string> chs, string result) {
    if (chs.isEmpty())
        cout << result << endl;
    for (int i = 0; i < chs.size(); i++) {
        string itemRemoved = chs.remove(0);
        helper(chs, result + itemRemoved);
        chs.add(itemRemoved);
    }
}


void permute(string str) {
    Vector<string> chs;
    for (int i = 0; i < str.size(); i++)
        chs.add(str.substr(i, 1));
    helper(chs, "");
}



int main____() {
    cout << "Permutation:" << endl;
    // string mat = "MARTY";
    string mat = "MART";
    permute(mat);

    return 0;
}
