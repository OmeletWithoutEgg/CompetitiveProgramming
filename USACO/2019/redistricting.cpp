#include <bits/stdc++.h>

using namespace std;
const int N = 300025, inf = 1e9;
void chmin(int &x, int v) { if (x > v) x = v; }

struct Segtree {
    int st[N << 1], n;
    void edit(int p, int v) {
        for (st[p += n] = v; p > 1; p >>= 1)
            st[p>>1] = min(st[p], st[p^1]);
    }
    void init(int _n) {
        n = _n;
        for (int i = 1; i < n*2; i++) st[i] = inf;
    }
    int query(int l, int r) {
        int res = inf;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l & 1) chmin(res, st[l++]);
            if (r & 1) chmin(res, st[--r]);
        }
        return res;
    }
} sgt;
multiset<int> ms[N];
int dp[N];
int p[N];
signed main() {
    assert( freopen("redistricting.in", "r", stdin) && freopen("redistricting.out", "w", stdout) );
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    string s;
    cin >> n >> k >> s;
    for (int i = 0; i < n; i++) p[i+1] = (s[i]=='H' ? 1 : -1);
    for (int i = 1; i <= n; i++) p[i] += p[i-1];

    int mn = *min_element(p, p+n+1);
    for (int i = 0; i <= n; i++) p[i] -= mn;

    sgt.init(n+1);
    ms[p[0]].insert(0);
    sgt.edit(p[0], 0);
    for (int i = 1; i <= n; i++) {
        dp[i] = min(sgt.query(0, p[i]), sgt.query(p[i], n+1) + 1);
        ms[p[i]].insert(dp[i]);
        sgt.edit(p[i], *ms[p[i]].begin());
        if (i >= k) {
            int j = i-k;
            ms[p[j]].erase(ms[p[j]].find(dp[j]));
            sgt.edit(p[j], ms[p[j]].empty() ? inf : *ms[p[j]].begin());
        }
    }
    cout << dp[n] << '\n';
}
