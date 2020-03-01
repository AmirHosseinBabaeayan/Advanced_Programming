#include <iostream>
#include <string>
#include <map>
#include <iterator>
#include <vector>
using namespace std;

int main()
{
    int number_set,count_set;
    cin>>number_set;
    string set_mem;
    map <string,int> s;
    //s.insert(pair<string,int>("hello",6));
    //cout<<s.find("helo")->second<<endl;
    for(int i=0;i<number_set;i++)
    {
        cin>>count_set;
        for(int j=0;j<count_set;j++)
        {
            cin>> set_mem;
            if(s.find(set_mem)->second==0)
            {
                s.insert(pair<string,int>(set_mem,1));
            }
            else
            {
                s[set_mem]=s.find(set_mem)->second+1;
            }
            
        }
    }
    cout<<s.size()<<endl;
    map <string,int>::iterator itr;
    vector <string> subscription;
    int counter=0;
    for (itr=s.begin();itr!=s.end();++itr)
    {
        if(itr->second==number_set)
        {
            counter++;
            subscription.push_back(itr->first);
        }
        cout<<itr->first<<" ";
    }
    cout<<endl;
    cout<<counter<<endl;
    if(counter)
    {
        for(int i=0;i<subscription.size();i++)
        {
            cout<<subscription.at(i)<<" ";
        }
    }
    cout<<endl;
    return 0;
}