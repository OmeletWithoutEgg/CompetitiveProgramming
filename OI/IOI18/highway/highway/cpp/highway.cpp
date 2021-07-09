#include "highway.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ... , (std::cerr << a << (--cnt ? ", " : "\e[0m)\n")));
}
#define pary(x...) danb(#x, x)
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int maxn = 100025;
vector<pair<int,int>> g[maxn];
void find_pair(int N, std::vector<int> U, std::vector<int> V, int A, int B) {
    int M = U.size();
    for (int i = 0; i < M; i++) {
        g[U[i]].emplace_back(V[i], i);
        g[V[i]].emplace_back(U[i], i);
    }

    auto bfs = [&](int src) -> pair<vector<int>,vector<int>> {
        vector<int> dis(N, -1);
        vector<int> prv(N, -1);
        queue<int> q;
        dis[src] = 0, q.push(src);
        while (!q.empty()) {
            int i = q.front(); q.pop();
            for (auto [j, id]: g[i])
                if (dis[j] == -1)
                    prv[j] = id, dis[j] = dis[i] + 1, q.push(j);
        }
        return { prv, dis };
    };
    ll org = ask(vector<int>(M, 0));
    int pref = 0;
    for (int s = 1 << 20; s; s >>= 1) {
        if (pref+s >= M) continue;
        vector<int> tmp(M);
        for (int i = 0; i < M; i++) tmp[i] = (i < pref+s);
        if (ask(tmp) == org) {
            pref += s;
        }
    }
    assert(pref < M);
    auto [p1, d1] = bfs(U[pref]);
    auto [p2, d2] = bfs(V[pref]);
    debug(U[pref], V[pref]);
    pary(all(d1));
    pary(all(d2));

    vector<int> t1, t2;
    vector<int> span_tree(M, 1);
    span_tree[pref] = 0;
    for (int i = 0; i < N; i++)
        if (d1[i] != d2[i]) {
            if (i == U[pref] || i == V[pref]) continue;
            if (d1[i] < d2[i]) {
                span_tree[p1[i]] = 0;
                t1.push_back(i);
            } else {
                span_tree[p2[i]] = 0;
                t2.push_back(i);
            }
        }
    pary(all(span_tree));
    // assert(ask(span_tree) == org);

    sort(all(t1), [&](int u, int v){ return d1[u] > d1[v]; });
    sort(all(t2), [&](int u, int v){ return d2[u] > d2[v]; });

    pary(all(t1));
    pary(all(t2));

    int Sid = 0;
    for (int s = 1 << 20; s; s >>= 1) {
        if (Sid + s > t1.size()) continue;
        auto tmp = span_tree;
        for (int i = 0; i < t1.size(); i++) if (i < Sid + s) tmp[p1[t1[i]]] = 1;
        if (ask(tmp) == org) {
            Sid += s;
        }
    }
    int S = Sid < t1.size() ? t1[Sid] : U[pref];
    int Tid = 0;
    for (int s = 1 << 20; s; s >>= 1) {
        if (Tid + s > t2.size()) continue;
        auto tmp = span_tree;
        for (int i = 0; i < t2.size(); i++) if (i < Tid + s) tmp[p2[t2[i]]] = 1;
        if (ask(tmp) == org) {
            Tid += s;
        }
    }
    int T = Tid < t2.size() ? t2[Tid] : V[pref];
    answer(S, T);
    debug(S, T);
    debug(A, B);
}
