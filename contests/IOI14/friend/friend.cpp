#include "friend.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
void qqbx(const char *s) {}
template <typename H, typename ...T> void qqbx(const char *s, const H& h, T&& ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) qqbx(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
using namespace std;

struct Dinic {
    struct Edge {
        int rest, to;
        Edge(int rest, int to) : rest(rest), to(to) {}
    };
    vector<Edge> E;
    vector<vector<int>> g;
    vector<int> dis, cur;
    Dinic(int n) : g(n), dis(n), cur(n) {}
    void addEdge(int a, int b, int c) {
        g[a].pb(E.size()), E.pb(c, b);
        g[b].pb(E.size()), E.pb(0, a);
    }
    bool BFS(int s, int t) {
        fill(dis.begin(), dis.end(), -1);
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        while(!q.empty()) {
            int i = q.front(); q.pop();
            for(int id: g[i]) if(E[id].rest > 0 && dis[E[id].to] == -1) {
                dis[E[id].to] = dis[i] + 1;
                q.push(E[id].to);
            }
        }
        return dis[t] != -1;
    }
    int DFS(int i, int t, int lim) {
        if(i == t) return lim;
        int ans = 0;
        while(cur[i] < g[i].size() && lim) {
            int id = g[i][cur[i]++];
            if(dis[E[id].to] != dis[i] + 1) continue;
            int f = DFS(E[id].to, t, min(lim, E[id].rest));
            E[id].rest -= f;
            E[id^1].rest += f;
            ans += f;
            lim -= f;
        }
        return ans;
    }
    int maxFlow(int s, int t) {
        int ans = 0;
        while(BFS(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            while(int f = DFS(s, t, 1e9)) ans += f;
        }
        return ans;
    }
};
int findSample(int n, int confidence[], int host[], int protocol[]){
    auto isNothing = [&]() -> bool {
        for(int i = 1; i < n; i++) if(protocol[i] != 1) return false;
        return true;
    };
    auto isComplete = [&]() -> bool {
        for(int i = 1; i < n; i++) if(protocol[i] != 2) return false;
        return true;
    };
    auto isTree = [&]() -> bool {
        for(int i = 1; i < n; i++) if(protocol[i] != 0) return false;
        return true;
    };
    auto isBipartite = [&]() -> bool {
        for(int i = 1; i < n; i++) if(protocol[i] == 2) return false;
        for(int i = 0; i < n; i++) if(confidence[i] != 1) return false;
        return true;
    };
    if(isComplete()) {
        return *max_element(confidence, confidence+n);
    }
    if(isTree()) {
        vector<vector<int>> g(n);
        vector<array<int,2>> dp(n);
        for(int i = 1; i < n; i++) g[host[i]].pb(i);
        function<void(int,int)> dfs = [&](int i, int p) {
            dp[i][0] = 0, dp[i][1] = confidence[i];
            for(int j: g[i]) {
                if(j == p) continue;
                dfs(j, i);
                dp[i][0] += max(dp[j][0], dp[j][1]);
                dp[i][1] += dp[j][0];
            }
        };
        dfs(0, -1);
        return max(dp[0][0], dp[0][1]);
    }
    if(isNothing()) {
        long long sum = 0;
        for(int i = 0; i < n; i++) sum += confidence[i];
        return sum;
    }
    if(isBipartite()) {
        safe;
        vector<bool> parity(n);
        vector<vector<int>> g(n);
        for(int i = 1; i < n; i++) {
            if(protocol[i] == 0) {
                g[host[i]].pb(i);
                g[i].pb(host[i]);
                parity[i] = !parity[host[i]];
            } else if(protocol[i] == 1) {
                for(int j: g[host[i]]) {
                    g[j].pb(i);
                    g[i].pb(j);
                }
                parity[i] = parity[host[i]];
            }
        }
        Dinic flow(n*2+2);
        int s = n*2, t = s+1;
        for(int i = 0; i < n; i++) {
            flow.addEdge(s, i, 1);
            flow.addEdge(i+n, t, 1);
        }
        for(int i = 0; i < n; i++) if(!parity[i]) for(int j: g[i]) flow.addEdge(i, j+n, 1e9);
        return n - flow.maxFlow(s, t);
    }
    if(n <= 20) {
        int g[20] = {};
        for(int i = 1; i < n; i++) {
            if(protocol[i] == 0) {
                g[i] |= 1 << host[i];
                g[host[i]] |= 1 << i;
            } else if(protocol[i] == 1) {
                g[i] |= g[host[i]];
                for(int j = 0; j < n; j++) if(g[host[i]] >> j & 1) g[j] |= 1 << i;
            } else if(protocol[i] == 2) {
                g[i] |= g[host[i]];
                for(int j = 0; j < n; j++) if(g[host[i]] >> j & 1) g[j] |= 1 << i;
                g[i] |= 1 << host[i];
                g[host[i]] |= 1 << i;
            }
        }
        int ans = 0;
        /* vector<int> wei(1<<n); */
        /* for(int i = 0; i < n; i++) wei[1<<i] = confidence[i]; */
        /* for(int s = 0; s < (1<<n); s++) wei[s] += wei[s - (s&-s)]; */
        for(int s = 0; s < (1<<n); s++) {
            bool ok = 1;
            for(int i = 0; i < n; i++) if((s >> i & 1) && (g[i] & s)) ok = 0;
            if(ok) {
                int sum = 0;
                for(int i = 0; i < n; i++) if(s >> i & 1) sum += confidence[i];
                ans = max(ans, sum);
            }
        }
        return ans;
    }
    return -1;
}
