#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) cerr<<__PRETTY_FUNCTION__<<" Line "<<__LINE__<<": "<<#x<<" = "<<x<<'\n'
#define ff first
#define ss second
#define pb emplace_back
#define all(v) begin(v),end(v)
#define mem(v,x) memset(v, x, sizeof v)

using namespace std;
typedef int64_t ll;
const int N = 125;

pair<int,int> h[N];
int v[N], n, m, id[N];
int sum(int l, int r) {return v[r] - v[l-1];} // [l,r]
bool dp[N][N], taken[N], valid[N][N];
pair<int,int> fr[N][N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 0; i < m; i++) cin >> h[i].ff >> h[i].ss, id[h[i].ff] = i;
    for(int i = 1; i <= n; i++) cin >> v[i];
    //sort(h,h+m);
    for(int i = 0; i < m; i++) {
        {
            bool ok = true;
            int hp = h[i].ss;
            for(int j = h[i].ff; j >= 1; j--) {
                hp += v[j];
                if(hp < 0) ok = false;
                valid[h[i].ff][j] = ok;
            }
        }
        {
            bool ok = true;
            int hp = h[i].ss;
            for(int j = h[i].ff; j <= n; j++) {
                hp += v[j];
                if(hp < 0) ok = false;
                valid[h[i].ff][j] = ok;
            }
        }
    }
    for(int l = 1; l <= n; l++) for(int r = l; r <= n; r++) {
        if(valid[l][r])
            dp[l][r] = true, fr[l][r] = {r,r};
        if(valid[r][l])
            dp[l][r] = true, fr[l][r] = {l,l};
    }
    for(int l = n+1; l >= 1; l--) for(int r = l-1; r <= n; r++) if(dp[l][r]) {
        for(int x = 1; x < l; x++) {
            if(valid[x][l-1])
                dp[x][r] = true, fr[x][r] = {l,r};
        }
        for(int x = r+1; x <= n; x++) {
            if(valid[x][r+1])
                dp[l][x] = true, fr[l][x] = {l,r};
        }
    }
    int l = 1e9, r = 0;
    for(int i = 0; i < m; i++) l = min(l,h[i].ff), r = max(r,h[i].ff);
    //debug(l),debug(r);
    if(dp[l][r]) {
        vector<int> ans;
        while(l < r) {
            auto [L, R] = fr[l][r];
            if(l == L) ans.pb(r);
            else ans.pb(l);
            l = L, r = R;
        }
        cout << l << '\n';
        reverse(all(ans));
        for(int x: ans) cout << id[x]+1 << ' ', taken[id[x]] = true;
        for(int i = 0; i < m; i++) if(!taken[i]) cout << i+1 << ' ';
        cout << '\n';
    } else {
        cout << -1 << '\n';
    }
}
