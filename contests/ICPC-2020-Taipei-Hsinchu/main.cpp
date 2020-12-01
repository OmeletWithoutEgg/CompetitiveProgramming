#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;

struct Dsu {
    vector<int> pa, sz;
    Dsu(int n) : pa(n), sz(n, 1) { iota(pa.begin(), pa.end(), 0); }
    int anc(int x) { return x==pa[x] ? x : anc(pa[x]); }
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(sz[x] < sz[y]) swap(x, y);
        return pa[y] = x, sz[x] += sz[y], true;
    }
    long long same(int x, int y) {
        x = anc(x), y = anc(y);
        if(x == y) return 0;
        return 1LL * sz[x] * sz[y];
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int>> e;
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        e.pb(c, a, b);
    }
    Dsu dsu(n);
    sort(e.begin(), e.end(), greater<>());
    int mn = 1e9;
    for(auto [c, a, b]: e) {
        if(dsu.join(a, b)) {
            mn = min(mn, c);
        }
    }
    cerr << mn << '\n';
    dsu = Dsu(n);
    vector<tuple<int,int,int>> ee;
    reverse(e.begin(), e.end());
    for(auto [c, a, b]: e) {
        if(c >= mn && dsu.join(a, b)) {
            ee.pb(c, a, b);
        }
    }
    dsu = Dsu(n);
    long long ans = 0;
    reverse(ee.begin(), ee.end());
    for(auto [c, a, b]: ee) {
        long long p = dsu.same(a, b);
        dsu.join(a, b);
        ans += c * p;
    }
    cout << ans << '\n';
}
