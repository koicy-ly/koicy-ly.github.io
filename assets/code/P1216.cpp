#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
int n,dp[1000+50][1000+50];
int main()
{
  cin>>n;
  for(int i=1; i<=n; i++)
    for(int j=1; j<=i; j++)
      cin>>dp[i][j];
  for(int i=n-1; i>=1; i--)
    for(int j=1; j<=i; j++)
      dp[i][j]+=max(dp[i+1][j],dp[i+1][j+1]);
  cout<<dp[1][1]<<endl;
  return 0;
}