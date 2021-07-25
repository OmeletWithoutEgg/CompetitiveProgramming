#pragma GCC optmize("Ofast")
#include <bits/stdc++.h>
#include <bits/extc++.h>
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
template <typename T> using min_heap = __gnu_pbds::priority_queue<T, greater<T>>;
using ll = long long;
using ld = double;
using pll = pair<ll,ll>;

struct Dijkstra {
    vector<vector<tuple<ll,ll,int>>> g;
    vector<ll> dis;
    vector<ll> slope;
    vector<int> vis;
    vector<min_heap<pair<ll,int>>::point_iterator> iter;
    Dijkstra(size_t n) : g(n), dis(n), slope(n), vis(n), iter(n, nullptr) {}
    void addEdge(int a, int b, ll c, ll p) {
        g[a].pb(c, p, b);
    }
    pll shortestPath(int s, int t, int T) {
        fill(all(iter), nullptr);
        fill(all(dis), -1);
        fill(all(vis), false);
        min_heap<pair<ll,int>> pq;
        pq.push({0, s});
        dis[s] = 0;
        slope[s] = 0;
        while(!pq.empty()) {
            auto [d, i] = pq.top(); pq.pop();
            if(vis[i]) continue;
            vis[i] = true;
            if(i == t) return {d, slope[t]};
            for(auto [c, p, j]: g[i]) {
                if(vis[j]) continue;
                ll w = c + p * T;
                if(dis[j] == -1 || dis[j] > d + w) {
                    dis[j] = d+w;
                    slope[j] = slope[i] + p;
                    if (iter[j] == nullptr)
                        iter[j] = pq.push({dis[j], j});
                    else
                        pq.modify(iter[j], {dis[j], j});
                }
            }
        }
        return {dis[t], slope[t]};
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
    auto calc = [&](int T) -> pll {
        auto [d1, s1] = dij.shortestPath(A, B, T);
        auto [d2, s2] = dij.shortestPath(B, A, T);
        return {d1+d2, s1+s2};
    };
    ll ans = 0;
    for(int s = 1 << 29; s; s>>=1) {
        debug(ans, s);
        if(ans + s >= D-1) continue;
        auto [dis, slope] = calc(ans + s);
        if(slope >= 0)
            ans += s;
        if(slope == 0) break;
    }
    cout << max(calc(ans).first, calc(ans+1).first) - min(calc(0).first, calc(D-1).first) << '\n';
}
