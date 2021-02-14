#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local

using namespace std;
using ll = long long;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int maxn = 800025;
const ll INF = 1e18;

vector<pair<ll,int>> g[maxn];
map<int,ll> sum[maxn];
map<int,int> color[maxn];
ll dis[maxn];
void addEdge(int a, int b, ll c) {
    g[a].emplace_back(c, b);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    int tot = n + m;
    vector<tuple<int,int,int,int>> edges(m);
    for (auto &[a, b, c, p]: edges) {
        cin >> a >> b >> c >> p;
        --a, --b;
        sum[a][c] += p;
        sum[b][c] += p;
        if (!color[a].count(c)) color[a][c] = tot++;
        if (!color[b].count(c)) color[b][c] = tot++;
    }

    for (int i = 0; i < m; i++) {
        int eid = n + i;
        auto [a, b, c, p] = edges[i];
        addEdge(a, b, sum[a][c] - p);
        addEdge(b, a, sum[b][c] - p);
        addEdge(a, eid, p);
        addEdge(b, eid, p);
        addEdge(eid, a, 0);
        addEdge(eid, b, 0);

        if (sum[a][c] != p) {
            addEdge(eid, color[a][c], sum[a][c]-p);
            addEdge(color[a][c], b, - p);
        }
        if (sum[b][c] != p) {
            addEdge(eid, color[b][c], sum[b][c]-p);
            addEdge(color[b][c], a, - p);
        }
    }

    fill(dis, dis+tot, INF);
    min_heap<pair<ll,int>> pq;
    dis[0] = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, i] = pq.top(); pq.pop();
        if (dis[i] != d) continue;
        for (auto [c, j]: g[i]) {
            if (dis[j] > dis[i] + c) {
                dis[j] = dis[i] + c;
                pq.emplace(dis[j], j);
            }
        }
    }
    if (dis[n-1] == INF)
        cout << -1 << '\n';
    else
        cout << dis[n-1] << '\n';
}

/*
4 6
1 4 4 4
3 4 1 3
1 3 4 4
2 4 3 1
2 3 3 2
1 2 4 2

5 7
2 3 7 1
1 4 5 1
4 5 3 1
3 4 7 1
2 4 3 1
3 5 6 1
1 2 5 1

13 21
7 10 4 4
3 6 4 7
8 10 4 5
3 9 2 5
1 4 4 5
2 6 4 2
3 11 2 2
3 8 16 2
8 11 16 1
6 10 4 14
6 8 16 6
9 12 16 5
5 13 4 6
1 12 4 7
2 4 4 18
2 9 4 10
2 12 4 6
10 13 4 28
5 7 2 5
5 11 2 16
7 13 4 20
*/
