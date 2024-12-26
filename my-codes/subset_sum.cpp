#include <iostream>
#include <vector>

using namespace std;

bool has_target_sum(vector<int> &vec, int target) {
    if (vec.size() == 0) {
        return target == 0;
    }

    int last = vec.back();
    vec.pop_back();

    return has_target_sum(vec, target - last) || has_target_sum(vec, target);
}

int main () {
    vector<int> vec;

    cout << "Enter a target sum: ";
    int target;
    cin >> target;

    cout << "Enter a list of integers: ";
    int num;
    while (cin >> num) {
        vec.push_back(num);
    }

    

    cout << has_target_sum(vec, target) << endl;
}