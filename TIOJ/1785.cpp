#include <bits/stdc++.h>

using namespace std;
const int N = 1000025;

int n,a[N],b[N],pos[N],vis[N];
int64_t w[N],ans;
signed main() {
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i], pos[b[i]] = i;
    for(int i = 0; i < n; i++) if(!vis[i]) {
        vector<int> vv;
        for(int x = i; !vis[x]; x = pos[a[x]]) vis[x] = 1, vv.emplace_back(a[x]);
        int64_t mi = 1e18;
        for(int id:vv) ans += w[id], mi = min(mi,w[id]);
        ans += mi*(int(vv.size())-2);
    }
    cout << ans << '\n';
}
