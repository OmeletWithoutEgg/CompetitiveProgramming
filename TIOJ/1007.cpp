#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int main(){
    int n, m;
    ll dp[100] = {};
    cin >> n >> m;
    dp[0] = 1;
    for(int i = 1;i <= n+1;i++)dp[i] = dp[i-1]<<1;
    dp[n+1]--;
    for(int i = n+2;i <= m;i++)dp[i] = (dp[i-1]<<1) - dp[i-n-2];
    cout << dp[m] << '\n';
    return 0;
}
