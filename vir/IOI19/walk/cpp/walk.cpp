#include "walk.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename H, typename ...T> void qqbx(const char *s, const H&h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;


struct Dijkstra {
    vector<vector<pair<int,int>>> g;
    vector<long long> dis;
    Dijkstra(int n) : g(n), dis(n) {}
    void addEdge(int a, int b, int c) {
        assert(c >= 0);
        g[a].pb(c, b);
        g[b].pb(c, a);
    }
    long long calc(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        priority_queue<pair<long long,int>> pq;
        pq.push({dis[s]=0, s});
        while(!pq.empty()) {
            auto [d, i] = pq.top(); pq.pop();
            if(d != dis[i]) continue;
            for(auto [c, j]: g[i]) {
                if(dis[j] == -1 || dis[j] > d + c) {
                    pq.push({dis[j]=c+d, j});
                }
            }
        }
        return dis[t];
    }
};

const int N = 1000025;

int getId(int i, int y) {
    static int tot;
    static map<pair<int,int>, int> mp;
    if(mp.count({i,y})) return mp[{i,y}];
    return mp[{i,y}] = tot++;
}
bool ok[N];
long long min_distance(std::vector<int> x, std::vector<int> h, std::vector<int> l, std::vector<int> r, std::vector<int> y, int s, int g) {
    int n = x.size();
    int m = l.size();
    Dijkstra dij(n*m);
    vector<vector<pair<int,int>>> vert(n), hori(m);
    for(int i = 0; i < m; i++) {
        auto &H = hori[i];
        for(int j = l[i]; j <= r[i]; j++) {
            if(h[j] < y[i]) continue;
            H.pb(x[j], getId(j, y[i]));
            /* dij.addEdge(getId(last, y[i]), getId(j, y[i]), x[j]-x[last]); */
            vert[j].pb(y[i], getId(j, y[i]));
        }
        sort(all(H));
        for(int j = 0; j < H.size() && j < 2; j++) ok[H[j].second] = ok[H[H.size()-1-j].second] = true;
    }
    for(int i = 0; i < n; i++) vert[i].pb(0, getId(i, 0));
    for(int i = 0; i < n; i++) {
        auto &V = vert[i];
        sort(all(V));
        for(int j = 0; j < V.size() && j < 2; j++) ok[V[j].second] = ok[V[V.size()-1-j].second] = true;
    }
    for(int i = 0; i < m; i++) {
        auto &H = hori[i];
        int last = -1;
        for(int j = 0; j < H.size(); j++) {
            if(!ok[H[j].second]) continue;
            if(~last) dij.addEdge(H[j].second, H[last].second, H[j].first - H[last].first);
            last = j;
        }
    }
    for(int i = 0; i < n; i++) {
        auto &V = vert[i];
        int last = -1;
        for(int j = 0; j < V.size(); j++) {
            if(!ok[V[j].second]) continue;
            if(~last) dij.addEdge(V[j].second, V[last].second, V[j].first - V[last].first);
            last = j;
        }
    }
    return dij.calc(getId(s, 0), getId(g, 0));
}
