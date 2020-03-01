#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string fStr, sStr;
    cin >> fStr >> sStr;
    if (fStr.size() < sStr.size()) swap(fStr, sStr);
    bool goodFriends = true;
    for (int i = 0; i < sStr.size(); i++) {
        char c = sStr[i];
        if (count(fStr.begin(), fStr.end(), c) < count(sStr.begin(), sStr.end(), c)) {
            goodFriends = false;
            break;
        }
    }
    cout << ((goodFriends) ? "Yes" : "No");
}