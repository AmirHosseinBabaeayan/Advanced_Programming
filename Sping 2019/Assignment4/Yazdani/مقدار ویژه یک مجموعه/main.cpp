#include <iostream>
#include <cmath>
using namespace std;
int main() {
    int n, val = 0, tmp, inp;
    cin >> n;
    tmp = pow(2, n - 1);
    for (int i = 0; i < n; i++) {
        cin >> inp;
        val += tmp * inp;
    }
    cout << val;
}