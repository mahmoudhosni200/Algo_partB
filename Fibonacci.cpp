// Mahmoud Part

#include <iostream>
#include <vector>
using namespace std;

vector<int> multi (vector<int> x, vector<int> y) {
    vector<int> res(y.size());
    if (y.size() == 2) {
        res[0] = x[0]*y[0] + x[1]*y[1];
        res[1] = x[2]*y[0] + x[3]*y[1];
        return res;
    }
    res[0] = x[0]*y[0] + x[1]*y[2];
    res[1] = x[0]*y[1] + x[1]*y[3];
    res[2] = x[2]*y[0] + x[3]*y[2];
    res[3] = x[2]*y[1] + x[3]*y[3];
    return res;
}

vector<int> power(vector<int> x, int n) {
    if (n == 1) {
        return x;
    }

    if (n%2==0) {
        return power(multi(x, x), n/2);
    }
    return multi(x, power(multi(x, x), n/2));
}

int main() {
    vector<int> a = {1, 1, 1, 0};
    vector<int> v0 = {1, 0};

    int target = 7;
    cout << multi(power(a, target-1), v0)[0] << endl;
    return  0;
}