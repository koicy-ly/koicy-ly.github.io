#include <iostream>
using namespace std;
int a[1000000];
int main()
{
    long long int n,i,j,p=0;
    long long int num=0,maxx=-100000000000000000000000;
    cin>>n;
    for(long long int i=0;i<n;i++)
    {
        cin>>a[i];
    }
    for(j=p;j<n;j++)
    {
        num+=a[j];
        maxx=max(maxx,num);
        if(num<0)
        {
            num=0;
            continue;
        }
    }
    cout<<maxx;
    return 0;
}

