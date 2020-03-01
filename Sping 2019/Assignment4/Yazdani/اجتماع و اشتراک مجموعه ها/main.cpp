#include <iostream>
#include <set>
#include <array>
#include <vector>
using namespace std;
int main() 
{
    int setsCount, setSize;
    string val;
    bool intersection = true;
    cin >> setsCount;
    int shortestSetSize = -1;
    set<string>* sets = new set<string>[setsCount];
    set<string>* shortestSet;
    set<string> unionSet;
    set<string> intersectionSet;
    for (int i = 0; i < setsCount; i++) {
        cin >> setSize;
        if (shortestSetSize == -1 || setSize < shortestSetSize)  {
            shortestSetSize = setSize;
            shortestSet = &sets[i];
        }
        for (int j = 0; j < setSize; j++) {
            cin >> val;
            unionSet.insert(val);
            sets[i].insert(val);
        }
    }
    set<string>::iterator iter = (*shortestSet).begin();
    vector<string> intersectionRes;
    for (int i = 0; i < shortestSetSize; i++) {
        intersection = true;
        for (int j = 0; j < setsCount; j++) {
            if (sets[j].find(*iter) == sets[j].end()) {
                intersection = false;
            }
        }
        if (intersection)
            intersectionRes.push_back(*iter);
        iter++;
    }
    set<string>::iterator unionIter = unionSet.begin();
    cout << unionSet.size() << endl;
    for (auto str : unionSet) {
        cout << str << " ";
    }
    cout << endl;
    cout << intersectionRes.size() << endl;
    for (auto str : intersectionRes) {
        cout << str << " ";
    }
    cout << endl;
    return 0; 
} 