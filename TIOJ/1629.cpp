#include <bits/stdc++.h>

using namespace std;
const int N = 1025;

int n, m;
bool dp[N][N][2], fr[N][N][2], g[N][N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b, --a, --b;
        g[a][b] = g[b][a] = true;
    }
    for(int i = 0; i < n; i++) dp[i][1][0] = dp[i][1][1] = true;
    for(int L = 2; L <= n; L++) for(int i = 0; i < n; i++) {
        // dp[i][L][0]
        if(dp[(i+1)%n][L-1][0] && g[(i+1)%n][i]) { // (i+1)%n
            fr[i][L][0] = 0;
            dp[i][L][0] = true;
        }
        if(dp[(i+L-1)%n][L-1][1] && g[(i+L-1)%n][i]) { // (i+L-1)%n
            if(!dp[i][L][0] || (i+1)%n > (i+L-1)%n)
                fr[i][L][0] = 1;
            dp[i][L][0] = true;
        }
        // dp[i][L][1]
        if(dp[(i+n-1)%n][L-1][1] && g[(i+n-1)%n][i]) { // (i+n-1)%n
            fr[i][L][1] = 0;
            dp[i][L][1] = true;
        }
        if(dp[(i+n+1-L)%n][L-1][0] && g[(i+n+1-L)%n][i]) { // (i+n+1-L)%n
            if(!dp[i][L][1] || (i+n-1)%n > (i+n+1-L)%n)
                fr[i][L][1] = 1;
            dp[i][L][1] = true;
        }
    }
    for(int i = 0; i < n; i++) {
        if(dp[i][n][0] || dp[i][n][1]) {
            vector<int> ans;
            for(int c = 0; c < 2; c++) if(dp[i][n][c]) {
                int d = c;
                vector<int> vv;
                for(int L = n; L >= 1; L--) {
                    vv.push_back(i);
                    // cerr<<dp[i][L][d]<<',';
                    int f = fr[i][L][d];
                    if(d) {
                        if(f) {
                            i = (i+n+1-L)%n;
                            d = 0;
                        }else {
                            i = (i+n-1)%n;
                            d = 1;
                        }
                    }else {
                        if(f) {
                            i = (i+L-1)%n;
                            d = 1;
                        }else {
                            i = (i+1)%n;
                            d = 0;
                        }
                    }
                }
                if(ans.empty() || vv < ans) ans = vv;
            }
            for(int x: ans) cout << x+1 << '\n';
            return 0;
        }
    }
    cout << -1 << '\n';
}
