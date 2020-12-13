#include <bits/stdc++.h>

using namespace std;
const int MOD = 2012, N = 5025;

int dp[N][N];
signed main() {
#ifndef local
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    int n = s.size();
    dp[0][0] = 1;
    int bal = 0;
    for(int i = 1; i <= n; i++) {
        bal += (s[i-1] == '(' ? 1 : -1);
        if(s[i-1] == '(') {
            dp[i][0] = dp[i-1][0];
            for(int j = 1; j <= bal; j++) {
                dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % MOD;
            }
        } else if(s[i-1] == ')') {
            for(int j = 0; j <= bal; j++)
                dp[i][j] = (dp[i-1][j] + dp[i-1][j+1]) % MOD;
        }
    }
    cout << dp[n][0] << '\n';
}
