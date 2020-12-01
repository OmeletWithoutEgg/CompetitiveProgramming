#include "simurgh.h"

#include <bits/stdc++.h>
#ifdef local
#define debug(...) QQBX(#__VA_ARGS__, __VA_ARGS__)
void QQBX(const char *s) {}
template <typename H, typename ...T> void QQBX(const char *s, const H&h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) QQBX(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n";
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
const int N = 250025;

vector<pair<int,int>> g[N];
struct DisjointSets {
    int pa[N], rk[N];
    int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x,y);
        return pa[y] = x, rk[x]!=rk[y]||++rk[x], true;
    }
    void init(int n) { iota(pa, pa+n, 0), fill(rk, rk+n, 0); }
} dsu;
vector<int> cand, must;
bool vis[N];
void dfs(int i) {
    vis[i] = true;
    for(auto p: g[i]) {
        int j = p.first;
        int id = p.second;
        if(!vis[j]) {
            cand.pb(id);
            dfs(j);
        }
    }
}
vector<int> concat(vector<int> a, const vector<int> &b) {
    for(int x: b) a.pb(x);
    return a;
}
std::vector<int> find_roads(int n, std::vector<int> u, std::vector<int> v) {
    int m = u.size();
    for(int i = 0; i < m; i++) {
        g[u[i]].pb(v[i], i);
        g[v[i]].pb(u[i], i);
    }
    dfs(0);
    auto findAux = [&](int x) -> vector<int> {
        dsu.init(n);
        for(int y: must) dsu.join(u[y], v[y]);
        for(int y: cand) if(y!=x) dsu.join(u[y], v[y]);
        vector<int> res;
        for(int i = 0; i < m; i++) {
            int a = dsu.anc(u[i]);
            int b = dsu.anc(v[i]);
            int c = dsu.anc(u[x]);
            int d = dsu.anc(v[x]);
            if((a==c && b==d) || (a==d && b==c)) res.pb(i);
        }
        return res;
    };
    safe;
    while(true) {
        for(int &x: cand) {
            debug(x);
            auto aux = findAux(x);
            for(int y: aux) debug(y);
            safe;
            int mx = -1, mxy = -1;
            for(int y: aux) {
                int t = x;
                x = y;
                for(int z: concat(cand, must)) debug(z);
                int val = count_common_roads(concat(cand, must));
                if(val > mx) {
                    mx = val;
                    mxy = y;
                }
                x = t;
            }
            if(mxy != x) {
                vector<int> tmp;
                for(int y: cand) if(y!=x) tmp.pb(y);
                must.pb(mxy);
                cand = tmp;
                break;
            }
        }
    }
    return concat(must, cand);
}
