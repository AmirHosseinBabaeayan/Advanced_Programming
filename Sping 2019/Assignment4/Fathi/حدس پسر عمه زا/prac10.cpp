#include <iostream>
#include <math.h>
using namespace std;
bool is_prime(int n)
{
    if(n==2) return true;
    if(n==1)return false;
    for(int i=2;i<=sqrt(n);i++)
    {
        if(n%i==0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    int n;
    cin>> n;
    if(n%2!=0)
    {
        if(is_prime(n-4))
        {
            cout<<"2 "<<"2 "<<n-4<<endl;       
        }
        else
        {
            n=n-3;
            for(int i=3;i<n;i++)
            {
                if(is_prime(i)&&is_prime(n-i))
                {
                    cout<<"3 "<<i<<" "<<n-i<<endl;
                    break;
                }
            }
        }       
    }
    else
    {
        cout<<"2 ";
        n=n-2;
        for(int i=2;i<n;i++)
            {
                if(is_prime(i)&&is_prime(n-i))
                {
                    cout<<i<<" "<<n-i<<endl;
                    break;
                }
            }
    }
    
    return 0;
}