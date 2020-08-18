#pragma g++ optimize("Ofast")
#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
const int N = 60;
typedef int64_t ll;
typedef pair<ll,ll> pll;

int n,k;
int64_t w[N], g[N], x;
set<pll> vis, q;
void solve() {
    cin >> n >> k;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) cin >> x, g[i] |= x<<j;
        g[i] = ~(g[i] | (1LL<<i));
    }
    for(int i = 0; i < n; i++) cin >> w[i];
    int cnt = 0;
    int64_t last = 0;
    vis.clear(), q.clear();
    pll src{0,0};
    q.insert(src);
    vis.insert(src);
    while(!q.empty()) {
        pll cur = *q.begin(); q.erase(cur);
        int64_t c = cur.ff;
        int64_t s = cur.ss;
        last = c, ++cnt;
        if(cnt == k) break;
        int64_t r = -1;
        for(int i = 0; i < n; i++) if(s >> i & 1) r &= g[i];
        for(int i = 0; i < n; i++) if(r >> i & 1) {
            pll nxt{c + w[i], s | (1LL<<i)};
            if(!vis.count(nxt)) {
                q.insert(nxt);
                vis.insert(nxt);
                if(q.size() > k) q.erase(prev(q.end()));
            }
        }
    }
    //for(auto p: vis) cout << bitset<3>(p.ss) << ' ' << p.ff << '\n';
    if(cnt == k)
        cout << last << '\n';
    else
        cout << -1 << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}
