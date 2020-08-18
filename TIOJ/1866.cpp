#include <bits/stdc++.h>
#define pb emplace_back
#define mem(v,x) memset(v,x,sizeof v)
#define debug(x) (cerr<<#x<<" = "<<x<<'\n')

using namespace std;
typedef long long ll;
const int N = 100025, K = 30, M = 3100025;
int n,v[N],pa[N];
vector<int> g[N];
int ans[N],root[N];
int ch[2][M],tot;
int qry(int i,int x) {
    int ans = 0;
    for(int p = K-1; p >= 0; p--) {
        int d = (x>>p) & 1;
        if(ch[!d][i]) i = ch[!d][i], ans |= 1<<p;
        else i = ch[d][i];
    }
    return ans;
}
int ins(int i,int x) {
    int res = ++tot, now = res;
    for(int p = K-1; p >= 0; p--) {
        int d = (x>>p) & 1;
        ch[d][now] = ++tot;
        ch[!d][now] = ch[!d][i];
        now = ch[d][now];
        i = ch[d][i];
    }
    return res;
}
void dfs(int i) {
    v[i] ^= v[pa[i]];
    ans[i] = max(ans[pa[i]], qry(root[pa[i]],v[i]));
    root[i] = ins(root[pa[i]],v[i]);
    for(int j:g[i]) if(j!=pa[i]) {
        pa[j] = i;
        dfs(j);
    }
}
void solve() {
    tot = 0, mem(ch,0), mem(root,0);
    root[0] = ins(0,0);
    cin >> n;
    for(int i = 1; i <= n; i++) g[i].clear();
    for(int i = 1; i <= n; i++) cin >> v[i];
    for(int i = 1,a,b; i < n; i++) cin >> a >> b, g[a].pb(b), g[b].pb(a);
    dfs(1);
    for(int i = 1; i <= n; i++) cout << ans[i] << '\n';
}
signed main() {
    int t;
    cin >> t;
    while(t--) solve();
}
