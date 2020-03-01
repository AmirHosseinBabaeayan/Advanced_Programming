#include <iostream>
#include <math.h>
using namespace std;

int main()
{
    int n;
    cin>>n;
    int setnum;
    double count=pow(2,n-1);
    double result=0;
    for(int i=0;i<n;i++)
    {
        cin>>setnum;
        result+=setnum*count;
    }
    cout<<result<<endl;
    return 0;
}