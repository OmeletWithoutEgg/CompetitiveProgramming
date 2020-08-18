#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v),end(v)
#define debug(x) cerr<<#x<<" = "<<x<<'\n'

using namespace std;
const int N = 100025, K = 450;
const int inf = (1LL<<31) - 1;

inline int min(int a, int b){return a<b?a:b;}
int n, v[N], q;
struct segtree {
    int mn[N<<1], n;
    void init(int v[], int _n) {
        n = _n;
        for(int i = 0; i < n; i++) mn[i+n] = v[i];
        for(int i = n-1; i >= 0; i--) mn[i] = min(mn[i<<1], mn[i<<1|1]);
    }
    int counter = 0;
    int query(int l, int r) {
        int res = inf;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res = min(res, mn[l++]);
            if(r&1) res = min(res, mn[--r]);
            ++counter;
        }
        return res;
    }
} seg;
struct query {int l,r,res;};
vector<query> Q;
int ans[N];
void solve() {
    int cnt1 = 0, cnt2 = 0;
    // QlogN * K
    for(auto &[l, r, res]: Q) {
        vector<int> small;
        int L = (l+K-1)/K, R = (r-1)/K;
        if(L > R) {
            for(int i = l; i < r; i++) small.pb(v[i]);
        }else {
            for(int i = l; i < L*K && i < n; i++) small.pb(v[i]);
            for(int i = r-1; i >= R*K; i--) small.pb(v[i]);
        }
        // sort(all(small));
        res = inf;
        for(int i = 1; i < small.size(); i++) res = min(res, small[i]-small[i-1]), ++cnt2;
    }
    // (N+QlogN)*N/K
    vector<pair<int,int>> sorted;
    for(int i = 0; i < n; i++) sorted.pb(v[i], i);
    sort(all(sorted));
    for(int b = 0; b*K < n; b++) {
        vector<pair<int,int>> block;
        for(int i = b*K; i < (b+1)*K && i < n; i++)
            block.pb(v[i], i);
        if(block.empty()) continue;
        int cur = 0;
        sort(all(block));
        for(int i = 0; i < n; i++) ans[i] = inf;
        for(auto [val, id]: sorted) {
            while(cur < block.size() && block[cur].first < val)
                ++cur;
            if(id/K == b) continue;
            if(cur < block.size())
                ans[id] = min(ans[id], block[cur].first - val);
            if(cur > 0)
                ans[id] = min(ans[id], val - block[cur-1].first);
            ++cnt1;
        }
        for(int i = 1; i < block.size(); i++) {
            int a = block[i].second, b = block[i-1].second;
            ans[a] = min(ans[a], abs(v[a]-v[b]));
            ans[b] = min(ans[b], abs(v[a]-v[b]));
        }
        seg.init(ans, n);
        for(auto &[l, r, res]: Q) {
            int L = (l+K-1)/K, R = (r-1)/K;
            if(L <= b && b < R) res = min(res, seg.query(l, r));
        }
    }
    debug(seg.counter);
    debug(cnt1);
    debug(cnt2);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    n = 100000;
    // cin >> n;
    for(int i = 0; i < n; i++) v[i] = rand();
    // for(int i = 0; i < n; i++) cin >> v[i];
    q = 100000;
    // cin >> q;
    Q.resize(q);
    // for(int i = 0; i < q; i++) cin >> Q[i].l >> Q[i].r, --Q[i].l;
    for(int i = 0; i < q; i++) {
        Q[i].l = rand(), Q[i].r = rand();
        if(Q[i].l > Q[i].r) swap(Q[i].l, Q[i].r);
        --Q[i].l;
    }
    solve();
    // for(int i = 0; i < q; i++) cout << Q[i].res << '\n';
}
