#pragma GCC optmize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
using ll = long long;
const int MOD = 1000000007, N = 210025, K = 256, B = 256;

struct Query {
    int l, r, id;
} Q[N];

struct Segtree {
    int mn[1 << 19];
    int n = 1 << 18;
    void init() {
        for(int i = 0; i < n*2; i++) mn[i] = -1e9;
    }
    void edit(int p, int d) {
        for(mn[p+=n] = d; p>0; p>>=1)
            mn[p>>1] = min(mn[p], mn[p^1]);
    }
    int bsearch(int k) {
        int i = 1;
        while(i < n) {
            i <<= 1;
            if(mn[i] >= k)
                i |= 1;
        }
        return i - n;
    }
} sgt;
int ans[N], v[N], last[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> v[i], last[v[i]] = -1;
    for(int i = 0; i < q; i++) {
        cin >> Q[i].l >> Q[i].r, --Q[i].l, --Q[i].r;
        Q[i].id = i;
    }
    sort(Q, Q+q, [](Query a, Query b){ return a.r < b.r; });
    sgt.init();
    for(int i = 0, j = 0; i < q; i++) {
        while(j <= Q[i].r) {
            sgt.edit(v[j], j);
            ++j;
        }
        ans[Q[i].id] = sgt.bsearch(Q[i].l);
    }
    for(int i = 0; i < q; i++)
        cout << ans[i] << '\n';
}
