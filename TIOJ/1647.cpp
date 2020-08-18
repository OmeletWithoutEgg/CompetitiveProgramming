#include <bits/stdc++.h>
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
using namespace std;
const long long N = 200025, INF = 1e18;
int vis[N], sz[N], mxs[N];
long long ans[N], k, val[N];
struct Edge { int to, cost; };
vector<Edge> g[N];
vector<int> tmp, subtree[N];
void dfs(int i) {
    vis[i] = 1, sz[i] = 1, mxs[i] = 0, tmp.push_back(i);
    for(auto e:g[i]) if(!vis[e.to]) {
        dfs(e.to);
        sz[i] += sz[e.to];
        mxs[i] = max(mxs[i], sz[e.to]);
    }
}
void get_dis(int i, int s, long long pa_d, long long dis = 0, long long sum = 0, long long best = 0) {
    vis[i] = 1;
    dis += pa_d;
    sum = max<long long>(0, sum+pa_d);
    best = max(best, sum);
    val[i] = (best>=k ? INF : dis);
    subtree[s].push_back(i);
    for(auto e:g[i]) if(!vis[e.to]) get_dis(e.to, s, e.cost, dis, sum, best);
}
void deco(int c) {
    tmp.clear();
    dfs(c);
    int S = tmp.size();
    for(int x:tmp) if(max(mxs[x], S-sz[x]) < max(mxs[c], S-sz[c])) c = x;
    //debug(c);
    val[c] = 0;
    for(int x:tmp) vis[x] = (x==c);
    for(auto e:g[c]) if(!vis[e.to]) {
        subtree[e.to].clear();
        get_dis(e.to,e.to,e.cost);
    }
    for(int x:tmp) vis[x] = (x==c);
    //cout << "JIZZ: "; for(int x:tmp) cout << val[x] << ' '; cout << '\n';
    for(int x:tmp) if(x!=c && val[x] >= k) ++ans[c];
    for(auto e:g[c]) if(!vis[e.to]) {
        // dis[x] + dis[y] >= K;
        //cout << "d: "; for(int x:subtree[e.to]) cout << val[x] << ' '; cout << '\n';
        for(int a:subtree[e.to]) for(int x:tmp) if(val[a]+val[x] >= k) ++ans[a];
        for(int a:subtree[e.to]) for(int x:subtree[e.to]) if(val[a]+val[x] >= k) --ans[a];
    }
    //debug(ans);
    for(int x:tmp) vis[x] = (x==c);
    for(auto e:g[c]) if(!vis[e.to]) deco(e.to);
}
signed main() {
    int n;
    cin >> n >> k;
    for(int i = 1, a, b, c; i < n; i++) {
        cin >> a >> b >> c;
        g[a].push_back({b,c});
        g[b].push_back({a,c});
    }
    deco(1);
    //for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
    cout << accumulate(ans+1, ans+n+1, 0LL)/2 << '\n';
}
