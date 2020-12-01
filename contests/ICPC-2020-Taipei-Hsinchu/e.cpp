#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
const int N = 525;

int dp[N][N];
signed main(){
    string rgb = "RGBCMYK";
    vector<int> id[7];
    string s;
    int m;
    cin >> s >> m;
    if(m == 1)
        return cout << "Yes\n", 0;
    int n = s.size();
    for(int i = 0; i < n; i++) {
        int c = rgb.find(s[i]);
        id[c].pb(i+1);
    }
    for(int i = 0; i <= n+1; i++) for(int j = 0; j <= n+1; j++) dp[i][j] = true;
    for(int l = n; l >= 1; l--) {
        dp[l][l] = false;
        cerr << dp[l][l] << ' ';
        for(int r = l+1; r <= n; r++) {
            dp[l][r] = false;
            for(int k = l; k < r; k++) dp[l][r] |= dp[l][k] & dp[k+1][r];
            for(int color = 0; color < 7; color++) {
                int cnt = 0;
                vector<int> vv;
                vv.pb(l-1);
                for(int j: id[color]) {
                    if(l <= j && j <= r) {
                        ++cnt;
                        vv.pb(j);
                    }
                }
                vv.pb(r+1);
                if(cnt < m) continue;
                bool ok = true;
                for(int i = 1; i < int(vv.size()); i++) {
                    int a = vv[i-1], b = vv[i];
                    ok &= dp[a+1][b-1];
                }
                dp[l][r] |= ok;
            }
            cerr << dp[l][r] << ' ';
        }
        cerr << '\n';
    }
    cout << (dp[1][n] ? "Yes\n" : "No\n");
}
