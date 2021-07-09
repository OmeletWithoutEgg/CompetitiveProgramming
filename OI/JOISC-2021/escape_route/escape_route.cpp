#include "escape_route.h"
#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) qqbx(#a, a)
#define pary(a...) danb(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (auto it = L; it != R; ++it)
        std::cerr << *it << ' ';
    std::cerr << "]\033[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back
#define get_pos(u,v) int(lower_bound(all(u), v) - u.begin())
using namespace std;

using ll = long long;
using pll = pair<ll,ll>;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int maxn = 95;
const ll INF = 2e17;

vector<tuple<int,ll,ll>> g[maxn];
ll dis[maxn];
bool vis[maxn];
vector<ll> calculate_necessary_time(
        int N, int M, ll S, int Q, vector<int> A, vector<int> B,
        vector<ll> L, vector<ll> C, vector<int> U,
        vector<int> V, vector<ll> T) {

    for (int i = 0; i < M; i++) {
        g[A[i]].emplace_back(B[i], C[i], L[i]);
        g[B[i]].emplace_back(A[i], C[i], L[i]);
    }

    vector<ll> ans(Q);
    for (int now = 0; now < Q; now++) {
        fill(dis, dis+N, INF);
        fill(vis, vis+N, false);
        dis[U[now]] = T[now];
        
        for (int t = 0; t < N; t++) {
            int i = -1;
            for (int j = 0; j < N; j++) if (!vis[j] && (i==-1 || dis[j] < dis[i])) i = j;
            vis[i] = true;
            ll d = dis[i];
            for (auto [j, lim, cost]: g[i]) {
                ll nd;
                if (d % S + cost > lim)
                    nd = S * (d / S + 1) + cost;
                else
                    nd = d + cost;
                if (dis[j] > nd)
                    dis[j] = nd;
            }
        }
        ans[now] = dis[V[now]] - T[now];
    }
    return ans;
}
