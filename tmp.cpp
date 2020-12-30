#pragma GCC optmize("Ofast")
#include <bits/stdc++.h>
#ifdef local
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define safe ((void)0)
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
using ll = long long;
using ld = double;

struct Dijkstra {
    vector<vector<tuple<ll,ll,int>>> g;
    vector<ll> dis;
    vector<bool> vis;
    Dijkstra(size_t n) : g(n), dis(n), vis(n) {}
    void addEdge(int a, int b, ll c, ll p) {
        g[a].pb(c, p, b);
    }
    ll shortestPath(int s, int t, int T) {
        fill(all(dis), -1);
        fill(all(vis), false);
        min_heap<pair<ll,int>> pq;
        pq.push({0, s});
        dis[s] = 0;
        while(!pq.empty()) {
            auto [d, i] = pq.top(); pq.pop();
            if(vis[i]) continue;
            vis[i] = true;
            if(i == t) return d;
            for(auto [c, p, j]: g[i]) {
                if(vis[j]) continue;
                ll w = c + p * T;
                if(dis[j] == -1 || dis[j] > d + w) {
                    dis[j] = d+w;
                    pq.push({dis[j], j});
                }
            }
        }
        // assert(dis[t] != -1);
        return dis[t];
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, A, B, D;
    cin >> n >> m >> A >> B >> D;
    Dijkstra dij(n);
    // -> : i * 2
    // <- : i*2+1
    for(int i = 0; i < m; i++) {
        int x, y;
        ll c1, p1, c2, p2;
        cin >> x >> y >> c1 >> p1 >> c2 >> p2;
        dij.addEdge(x, y, c1, p1);
        dij.addEdge(y, x, c2, p2);
    }
    auto calc = [&](int T) -> ll {
        return dij.shortestPath(A, B, T) + dij.shortestPath(B, A, T);
    };
    ll ans = 0;
    for(int s = 1 << 29; s; s>>=1) {
        debug(ans, s);
        if(ans + s >= D) continue;
        ll c1 = calc(ans + s - 1);
        ll c2 = calc(ans + s);
        if(c1 <= c2)
            ans += s;
        if(c1 == c2) break;
    }
    cout << calc(ans) - min(calc(0), calc(D-1)) << '\n';
}
