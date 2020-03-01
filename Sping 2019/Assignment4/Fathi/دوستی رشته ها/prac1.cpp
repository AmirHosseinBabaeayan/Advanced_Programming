#include <iostream>
#include <string>

using namespace std;

int main()
{
    string str1,str2;
    cin>> str1;
    cin>> str2;   
    if(str2.size()>str1.size())
    {
        cout<<"no"<<endl;
        return 0;
    }
    for(int i=0;i<str2.length();i++)
    {
        if(str1.find(str2[i]) != std::string::npos)
        {
            if(i==str2.size()-1)
            {
                break;
            }
            str1=str1.substr(str1.find(str2[i])+1,str1.size()-str1.find(str2[i]));
        }
        else
        {
            cout<<"no"<<endl;
            return 0;
        }
        
    }
    cout<<"yes"<<endl;
    return 0;
}