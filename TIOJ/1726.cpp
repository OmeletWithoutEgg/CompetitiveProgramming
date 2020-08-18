#include <bits/stdc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#define debug(x) ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
constexpr int N = 60025, K = 300, inf = 1e8;

vector<int> id[N],ans[K];
int big[N],totb,n,q,v[N];
void precalc(int k) {
    ans[k].resize(n+1,inf);
    //for(int i = 1; i <= n; i++) ans[k][i] = inf;
    int last;
    last = -inf;
    for(int i = 0; i < n; i++) {
        if(big[v[i]] == k)
            last = i;
        else
            ans[k][v[i]] = min(ans[k][v[i]], i - last);
    }
    last = inf;
    for(int i = n-1; i >= 0; i--) {
        if(big[v[i]] == k)
            last = i;
        else
            ans[k][v[i]] = min(ans[k][v[i]], last - i);
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    // small - small -> brute every time
    // big - other -> precalc
    cin >> n >> q;
    int S = 400;
    for(int i = 0; i < n; i++) cin >> v[i];
    for(int i = 0; i < n; i++) id[v[i]].pb(i);
    for(int i = 1; i <= n; i++) if(id[i].size() >= S) {
        big[i] = ++totb;
        precalc(big[i]);
    }
    while(q--) {
        int a,b;
        cin >> a >> b;
        if(id[a].empty() || id[b].empty()) cout << -1 << '\n';
        else if(a == b) cout << 0 << '\n';
        else {
            if(id[a].size() < S && id[b].size() < S) {
                vector<int> A = id[a];
                vector<int> B = id[b];
                int i = 0, j = 0, lastA = -inf, lastB = -inf, res = inf;
                while(i < A.size() || j < B.size()) {
                    if(j==B.size() || (i<A.size() && A[i]<B[j])) {
                        int t = A[i++];
                        res = min(res, t - lastB);
                        lastA = t;
                    }else {
                        int t = B[j++];
                        res = min(res, t - lastA);
                        lastB = t;
                    }
                }
                cout << res << '\n';
            }else {
                if(big[a])
                    cout << ans[big[a]][b] << '\n';
                else
                    cout << ans[big[b]][a] << '\n';
            }
        }
    }
}
