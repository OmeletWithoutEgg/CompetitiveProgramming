#include <bits/stdc++.h>
using namespace std;
const int N = 105;
int dp[N][N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    for(int n = 1; n <= 100; n++) for(int m = 1; m <= 100; m++) {
        dp[n][m] = n*m;
        if(n == m) dp[n][m] = 1;
        for(int i = 1; i < n; i++)
            dp[n][m] = min(dp[n][m],dp[n-i][m]+dp[i][m]);
        for(int i = 1; i < m; i++)
            dp[n][m] = min(dp[n][m],dp[n][m-i]+dp[n][i]);
    }
    int a,b;
    cin >> a >> b;
    cout << dp[a][b] << '\n';
}
