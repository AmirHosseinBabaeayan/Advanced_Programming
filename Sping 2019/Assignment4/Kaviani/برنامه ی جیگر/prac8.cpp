#include <iostream>
#include <math.h>
using namespace std;
long long int StirlingNum(int n,int k) {
    int maxj = n-k;

    long long int *arr = new long long int[maxj+1];

    for (int i = 0; i <= maxj; ++i)
        arr[i] = 1;

    for (int i = 2; i <= k; ++i)
        for(int j = 1; j <= maxj; ++j)
            arr[j] += i*arr[j-1]%1000000001;

    return arr[maxj];
}
int main()
{
    int i,j;
    cin>>i>>j;
    long long res=StirlingNum(i,j);
    if(res<1000000001)
    {
        cout<<res<<endl;
    }
    else
    {
        cout<<res%1000000001<<endl;
    }
    return 0;
}