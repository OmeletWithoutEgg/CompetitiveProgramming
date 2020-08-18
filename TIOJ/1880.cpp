#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 100001;

int n,m,cnt[2],vis[N],col[N];
vector<int> g[N];
bool dfs(int i, int c = 0) {
    vis[i] = 1, col[i] = c;
    ++cnt[c];
    for(int j:g[i])
        if(vis[j] ? col[j]==col[i] : !dfs(j,!c))
            return false;
    return true;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m;
    for(int i = 0,a,b; i < m; i++) {
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    int res = 0, ans = 1;
    for(int i = 1; i <= n; i++) if(!vis[i]) {
        cnt[0] = cnt[1] = 0;
        if(!dfs(i)) return cout << 0 << '\n', 0;
        ++res;
    }
    for(int i = 1; i < res; i++) {
        ans <<= 1;
        if(ans >= 1000007) ans -= 1000007;
    }
    cout << ans << '\n';
}
