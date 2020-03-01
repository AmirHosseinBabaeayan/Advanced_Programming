#include <iostream>
#include <map>
#include <iterator>
using namespace std;

int main()
{
    map <float,float> hours;
    int n;
    cin>>n;
    float i,j;
    for(int k=0;k<n;k++)
    {
        cin>>i>>j;
        if(hours.find(i)->second==0)
        {
            hours.insert(pair<float,float>(i,j));
        }
        else
        {
            if(hours[i]<j)
            {
                hours[i]=j;
            }
        }        
    }
    float temp=hours.begin()->first;
    float temp2=hours.begin()->second;
    map <float,float>::iterator itr;
    for(itr=hours.begin();itr!=hours.end();itr++)
    {
        if(temp2>=itr->first)
        {
            if(temp2<itr->second)
            {
                hours[temp]=itr->second;
                temp2=itr->second;
                hours.erase(itr->first);
            }
            else
            {
                hours.erase(itr->first);
            }
            
        }
        else
        {
            cout<<temp<<" "<<temp2<<endl;
            temp=itr->first;
            temp2=hours[temp];

        }
    }
    cout<<temp<<" "<<temp2<<endl;
    return 0;
}