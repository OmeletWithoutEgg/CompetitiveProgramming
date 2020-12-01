#include <bits/stdc++.h>
#ifdef local
#define debug(args...) ppbx(#args, args)
template <typename ...T> void ppbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v), end(v)
using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> p(n);
    for(int i = 0; i < n; i++) cin >> p[i], --p[i];
    for(int i = 0; i < n; i++) if(p[i] + p[n-1-i] != n-1) return cout << -1 << '\n', void();
    vector<pair<int,int>> ans;
    int H = n/2;
    vector<int> pos(H);
    for(int i = 0; i < H; i++) pos[p[i] < H ? p[i] : n-1-p[i]] = i;
    vector<int> vis(H);
    int last = -1;
    auto go = [&](int a, int b) {
        swap(p[a], p[b]);
        swap(p[n-1-a], p[n-1-b]);
        ans.pb(a, b);
    };
    for(int i = 0; i < H; i++) {
        if(!vis[i]) {
            vector<int> cyc;
            for(int x = i; !vis[x]; x = pos[x]) {
                vis[x] = true;
                if(p[x] >= H)
                    cyc.pb(x);
            }
            if(cyc.size() % 2 == 1) {
                if(last == -1) last = cyc.back();
                else go(last, n-1-cyc.back()), last = -1;
                cyc.pop_back();
            }
            for(int i = 0; i < int(cyc.size()); i += 2) {
                int a = cyc[i], b = cyc[i+1];
                debug(a, b);
                go(a, n-1-b);
            }
        }
    }
    if(last != -1) return cout << -1 << '\n', void();
    /* for(int i = 0; i < n; i++) cerr << p[i]+1 << (i+1==n ? '\n' : ' '); */
    /* for(int i = 0; i < H; i++) cerr << pos[i] << ' '; */
    /* cerr << '\n'; */
    for(int i = 0; i < H; i++) pos[p[i]] = i;
    vis = vector<int>(n, 0);
    for(int i = 0; i < H; i++) {
        if(!vis[i]) {
            vector<int> cyc;
            for(int x = i; !vis[x]; x = pos[x]) {
                vis[x] = true;
                cyc.pb(x);
            }
            /* cerr << "cyc = "; */
            /* for(int x: cyc) cerr << x << ' '; */
            /* cerr << '\n'; */
            for(int i = 1; i < int(cyc.size()); i++) {
                go(cyc[i], cyc[i-1]);
            }
        }
    }
    /* for(int i = 0; i < n; i++) cerr << p[i]+1 << (i+1==n ? '\n' : ' '); */
    cout << ans.size() << ' ' << ans.size() << '\n';
    for(auto [a, b]: ans) cout << a+1 << ' ' << b+1 << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t = 1;
    cin >> t;
    while(t--) solve();
}
