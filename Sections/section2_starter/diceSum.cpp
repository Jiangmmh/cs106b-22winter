#include "vector.h"
#include <iostream>
#include "console.h"

using namespace std;

void diceSumHelper(int n, int sum, Vector<int>& res) {
    if (n == 0) {
        if (sum == 0) {
            cout << res << endl;
        }
    } else {
        for (int i = 1; i <= 6; i++) {
            if (sum <= n * 6 && sum >= n * 1) {
                res.add(i);
                diceSumHelper(n - 1, sum - i, res);
                res.remove(res.size() - 1);
            }
        }
    }
}

void diceSum(int n, int sum) {
    Vector<int> res;
    diceSumHelper(n, sum, res);
}


int main__ (){
    int n, sum;
    cin >> n >> sum;
    diceSum(n, sum);

    return 0;
}
