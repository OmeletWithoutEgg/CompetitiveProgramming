#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) cerr<<__PRETTY_FUNCTION__<<" Line "<<__LINE__<<": "<<#x<<" = "<<x<<'\n';
#define ff first
#define ss second
#define pb emplace_back
#define all(v) begin(v),end(v)
#define mem(v,x) memset(v, x, sizeof v)

using namespace std;
typedef int64_t ll;
const int N = 1001, mask = 32767;

int n, v, m;
vector<pair<int,int>> g[N];
int indeg[N], cnt[N], ans[N];
string name[N];
void solve() {
    cin >> n >> v >> m;
    for(int i = 1; i <= n; i++) cin >> name[i];
    for(int i = 0; i < v; i++) g[i].clear(), indeg[i] = cnt[i] = ans[i] = 0;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].pb(c, b);
        ++indeg[b];
    }
    queue<int> q;
    q.push(0);
    cnt[0] = 1;
    while(!q.empty()) {
        int i = q.front(); q.pop();
        for(auto [c, j]: g[i]) {
            cnt[j] = (cnt[j] + cnt[i]) & mask;
            ans[j] = (ans[j] + ans[i] + c*cnt[i]) & mask;
            if(--indeg[j] == 0)
                q.push(j);
        }
    }
    for(int i = 1; i <= n; i++) cout << name[i] << ": " << ans[i] << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    for(int i = 1; i <= t; i++) {
        cout << "Game #" << i << '\n';
        solve();
    }
}
