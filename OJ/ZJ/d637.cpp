#include <bits/stdc++.h>
#define N 1000000
#define pii pair<int,int>
#define F first
#define S second

using namespace std;

int dp[N+1] = {};
pii v[10000] = {};
int sum = 0,n;
int main(){
    cin >> n;
    for(int i = 0;i < n;i++)cin >> v[i].F >> v[i].S;
    //int *dp = new int[sum+1];
    int res = 0;
    fill(dp,dp+N+1,0);
    for(int i = 0;i < n;i++)
        for(int w = N;w >= v[i].F;w--)
            dp[w] = max(dp[w-v[i].F]+v[i].S,dp[w]);
    printf("%d\n",dp[100]);
    return 0;
}
