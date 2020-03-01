#include <iostream>
#include <string>
using namespace std;
int main()
{
    int n;
    bool first_pos=false;
    bool third_pos=true;
    cin>>n;
    int *p=new int[n];
    int temp;
    if (n%2!=0)
    {
        for(int i=0;i<n;i++)
        {
            cin>>*(p+i);
            if(i>n/2)
            {
                if(*(p+i)>*(p+n-i-1)&&!first_pos) first_pos=true;
                *(p+i)=*(p+n-i-1);
            } 
        }
        if(!first_pos)
        {
            for(int i=0;i<n;i++)
            {
                cout<<*(p+i)<<" ";
            }
            cout<<endl;
        }
        else
        {
            *(p+n/2)=*(p+n/2)+1;
            for(int i=n/2;i>=0;i--)
            {
                if(*(p+i)==10)
                {
                    *(p+i)=0;
                    *(p+n-i-1)=0;
                    *(p+n-i)+=1;
                    *(p+i-1)+=1;
                }
                else
                {
                    break;
                }               
            }
            for(int i=0;i<n;i++)
            {
                cout<<*(p+i)<<" ";
            }
            cout<<endl;
        }              
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            cin>>*(p+i);
            if(i>=n/2)
            {
                if(*(p+i)>*(p+n-i-1)&&!first_pos) first_pos=true;
                *(p+i)=*(p+n-i-1);
            }
        }
        if(!first_pos)
        {
            for(int i=0;i<n;i++)
            {
                cout<<*(p+i)<<" ";
            }
        }
        else
        {
            *(p+n/2-1)+=1;
            *(p+n/2)+=1;
            for(int i=n/2-1;i>=0;i--)
            {
                if(*(p+i)==10)
                {
                    *(p+i)=0;
                    *(p+n-i-1)=0;
                    *(p+i-1)+=1;
                    *(p+n-i)+=1;
                }
                else
                {
                    break;
                }
                
            }
            for(int i=0;i<n;i++)
            {
                cout<<*(p+i)<<" ";
            }
            cout<<endl;
        }
        
    }
    return 0;
}