#include <iostream>
#include <algorithm>

using namespace std;
int main()
{
    int n,i,j,temp;
    cin>>n>>i>>j;
    int*p=new int[n];
    for(int i=0;i<n;i++)
    {
        cin>>temp;
        *(p+i)=temp;
    }
    sort(p,p+n);
    do
    {
        if(*(p+i)<*(p+j))
        {
            for(int i=0;i<n;i++)
            {
                cout<<*(p+i)<<" ";
            }
            cout<<endl;
        }   
    } while (next_permutation(p,p+n));
    
    return 0;
}