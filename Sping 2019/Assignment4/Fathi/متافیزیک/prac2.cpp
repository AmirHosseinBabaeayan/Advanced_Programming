#include <iostream>
#include <bitset>
#include <string>
#include <algorithm>

using namespace std;
int main()
{
    int a;
    cin>>a;
    string str1=bitset<20>(a).to_string();
    size_t found=str1.find('1');
    string str2=str1.substr(found,str1.size()-found);
    reverse(str2.begin(),str2.end());
    unsigned long result=bitset<20>(str2).to_ulong();
    cout<< result<<endl;
    return 0;
}