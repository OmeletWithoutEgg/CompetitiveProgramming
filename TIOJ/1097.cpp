#include <bits/stdc++.h>

using namespace std;
const int N = 5001;

int n,m,dp[2][N],best;
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n >> m, n||m) {
        best = 0;
        for(int j = 1; j <= m; j++) dp[0][j] = dp[1][j] = 0;
        for(int i = 0, d = 0, t; i < n; i++, d = !d) for(int j = 1; j <= m; j++) {
            cin >> t;
            if(t != 2) {
                dp[d][j] = min({dp[!d][j],dp[d][j-1],dp[!d][j-1]}) + 1;
                best = max(best,dp[d][j]);
            }else dp[d][j] = 0;
        }
        cout << best*best << '\n';
    }
}
