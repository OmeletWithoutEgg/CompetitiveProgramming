#include <bits/stdc++.h>
#define pb emplace_back
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ... args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}

using namespace std;

struct MinCostMaxFlow {
    struct Edge {
        int to, rest, cost;
        Edge(int t, int r, int c) : to(t), rest(r), cost(c) {}
    };
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> dis, prv, prvE;
    MinCostMaxFlow(int n) : g(n), dis(n), prv(n), prvE(n) {}
    void addEdge(int a, int b, int cap, int cost) {
        g[a].pb(E.size()), E.pb(b, cap, cost);
        g[b].pb(E.size()), E.pb(a, 0, cost);
    }
    bool spfa(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        fill(prv.begin(), prv.end(), -1);
        priority_queue<pair<int,int>> pq;
        pq.push({dis[s] = 0, s});
        while(!pq.empty()) {
            auto [d, i] = pq.top(); pq.pop();
            for(int id: g[i]) {
                if(E[id].rest == 0) continue;
                int j = E[id].to;
                if(dis[j] == -1 || dis[j] > dis[i] + E[id].cost)
                    pq.push({dis[j] = dis[i] + E[id].cost, j}), prv[j] = i, prvE[j] = id;
            }
        }
        return dis[t] != -1;
    }
    pair<int,int> minCostMaxFlow(int s, int t) {
        int ans = 0, cost = 0;
        while(spfa(s, t)) {
            int f = 1e9;
            for(int x = t; x != s; x = prv[x]) f = min(f, E[prvE[x]].rest);
            ans += f;
            cost += f * dis[t];
            for(int x = t; x != s; x = prv[x]) {
                int id = prvE[x];
                E[id].rest -= f;
                E[id^1].rest += f;
            }
        }
        return {ans, cost};
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string T;
    cin >> T;
    int n;
    cin >> n;
    MinCostMaxFlow flow(n + 26 + 2);
    int apb[26] = {};
    for(int i = 0; i < 26; i++) apb[i] = n + i;
    int s = n + 26, t = n + 27;
    for(int i = 0; i < n; i++) {
        string str;
        int a;
        cin >> str >> a;
        flow.addEdge(s, i, a, i+1);
        int cnt[26] = {};
        for(char c: str) cnt[c-'a'] += 1;
        for(int j = 0; j < 26; j++) {
            if(!cnt[j]) continue;
            flow.addEdge(i, apb[j], cnt[j], 0);
        }
    }
    int cnt[26] = {};
    for(char c: T) cnt[c-'a'] += 1;
    for(int i = 0; i < 26; i++) {
        if(!cnt[i]) continue;
        flow.addEdge(apb[i], t, cnt[i], 0);
    }
    auto [F, C] = flow.minCostMaxFlow(s, t);
    if(F != int(T.size())) cout << -1 << '\n';
    else cout << C << '\n';
}
