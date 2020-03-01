#include <iostream>
#include <math.h>
#include <map>
#include <iterator>

using namespace std;
bool prime(int n)
{
    if(n==1)return 0;
    if(n%2==0)return 0;
    for(int i=3;i<=sqrt(n);i+=2)
    {
        if(n%i==0)
        {
            return 0;
        }
    }
    return 1;
}
int main()
{
    int n;
    cin>>n;
    map <int,int> prime_factors;
    if(n%2==0)
    {
        n=n/2;
        prime_factors.insert(pair<int,int>(2,1));
        while(n%2==0)
        {
            n=n/2;
            prime_factors[2]=prime_factors.find(2)->second+1;
        }
    }
    if(n%3==0)
    {
        n=n/3;
        prime_factors.insert(pair<int,int>(3,1));
        while(n%3==0)
        {
            n=n/3;
            prime_factors[3]=prime_factors.find(3)->second+1;
        }
    }
    int m=n;
    int p;
    for(int i=1;6*i-5<=n;i++)
    {
        if(prime(6*i-5))
        {
            p=6*i-5;
            if(n%p==0)
            {
                m=m/p;
                prime_factors.insert(pair<int,int>(p,1));
                while(m%p==0)
                {
                    if(m==0) break;
                    m=m/p;
                    prime_factors[p]=prime_factors.find(p)->second+1;
                }
            }
        }

        if(prime(6*i-1))
        {
            p=6*i-1;
            if(n%p==0)
            {
                m=m/p;
                prime_factors.insert(pair<int,int>(p,1));
                while(m%p==0)
                {
                    if(m==0) break;
                    m=m/p;
                    prime_factors[p]=prime_factors.find(p)->second+1;
                }
            }
        }
    }
    map <int,int>::iterator itr;
    for(itr=prime_factors.begin();itr!=prime_factors.end();++itr)
    {
        cout<<itr->first<<" "<<itr->second<<endl;
    }
    return 0;
}