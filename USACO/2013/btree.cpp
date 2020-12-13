#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n"))));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
const int N = 40025;

vector<int> g[N];
int vis[N];
int sz[N];
void getSize(int i, int p = -1) {
    sz[i] = 1;
    for(int j: g[i]) {
        if(j == p || vis[j]) continue;
        getSize(j, i);
        sz[i] += sz[j];
    }
}
int getCent(int n, int i, int p = -1) {
    for(int j: g[i]) {
        if(j == p || vis[j]) continue;
        if(sz[j]*2 >= n) return getCent(n, j, i);
    }
    return i;
}
map<int,int> has;
int lab[N];
int ans;
void getPath(vector<pair<int,int>> &sub, int i, int p, int bal, int mx, int mn) {
    bal += lab[i];
    mx = max(mx, bal);
    mn = min(mn, bal);
    if(bal >= mx)
        sub.pb(bal, bal - mn);
    if(bal <= mn)
        sub.pb(bal, mx - bal);
    for(int j: g[i]) {
        if(j == p || vis[j]) continue;
        getPath(sub, j, i, bal, mx, mn);
    }
}
void solve(int i) {
    getSize(i);
    int c = getCent(sz[i], i);
    debug(c+1);
    vis[c] = true;
    has.clear();
    has[0] = 0;
    for(int j: g[c]) {
        if(!vis[j]) {
            vector<pair<int,int>> pos, neg;
            getPath(pos, j, c, lab[c], max(lab[c], 0), min(lab[c], 0));
            getPath(neg, j, c, 0, 0, 0);
            for(auto p: pos) {
                int b, v;
                tie(b, v) = p;
                if(b < 0) continue;
                if(has.count(-b))
                    ans = max(ans, max(v, has[-b]));
            }
            for(auto p: neg) {
                int b, v;
                tie(b, v) = p;
                if(b > 0) continue;
                if(has.count(-b))
                    ans = max(ans, max(v, has[-b]));
            }
            for(auto p: pos) {
                int b, v;
                tie(b, v) = p;
                if(b < 0) continue;
                has[b] = max(has[b], v);
            }
            for(auto p: neg) {
                int b, v;
                tie(b, v) = p;
                if(b > 0) continue;
                has[b] = max(has[b], v);
            }
        }
    }
    for(int j: g[c]) if(!vis[j]) solve(j);
}
signed main() {
#ifndef local
    freopen("btree.in", "r", stdin);
    freopen("btree.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int p;
        cin >> p;
        --p;
        g[p].pb(i);
        g[i].pb(p);
    }
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        lab[i] = (s == "(" ? 1 : -1);
    }
    solve(0);
    cout << ans << '\n';
}
