#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v),end(v)
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
#else
#define debug(...) ((void)0)
#endif // local

using namespace std;
const int N = 1000025;

struct segtree {
    int mx[N<<1], mn[N<<1], lz[N], n;
    void go(int p, int d) {
        mx[p] += d, mn[p] += d;
        if(p<n) lz[p] += d;
    }
    void pull(int p) {
        for(; p > 1; p >>= 1) {
            mx[p>>1] = max(mx[p], mx[p^1])+lz[p>>1];
            mn[p>>1] = min(mn[p], mn[p^1])+lz[p>>1];
        }
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p>>h;
            if(!lz[i>>1]) continue;
            go(i, lz[i>>1]);
            go(i^1, lz[i>>1]);
            lz[i>>1] = 0;
        }
    }
    void add(int l, int r, int d) {
        l = clamp(l, 0, n), r = clamp(r, 0, n);
        int L = l, R = r;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) go(l++, d);
            if(r&1) go(--r, d);
        }
        pull(L+n), pull(R-1+n);
    }
    int query_max(int l, int r) {
        l = clamp(l, 0, n), r = clamp(r, 0, n);
        push(l+n), push(r-1+n);
        int res = -1e9;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res = max(res, mx[l++]);
            if(r&1) res = max(res, mx[--r]);
        }
        return res;
    }
    int query_min(int l, int r) {
        l = clamp(l, 0, n), r = clamp(r, 0, n);
        push(l+n), push(r-1+n);
        int res = 1e9;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res = min(res, mn[l++]);
            if(r&1) res = min(res, mn[--r]);
        }
        return res;
    }
} sgt;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int &x: a) cin >> x;
    cin >> q;
    vector<int> ans(q);
    vector<tuple<int,int,int,int,int>> Q(q);
    for(int i = 0; i < q; i++) {
        auto &[v, l, r, c, id] = Q[i];
        cin >> v >> l >> r >> c;
        --l, --r;
        id = i;
    }
    for(int i = 0; i < n; i++) Q.pb(a[i], -1, i, 0, -1);
    sort(all(Q));
    sgt.n = n;
    for(auto [v, l, r, c, id]: Q) {
        debug(v, l, r);
        if(l == -1) {
            int i = r;
            sgt.add(i-k+1, i+1, 1);
        } else {
            int mn = sgt.query_min(l, r-k+2);
            int mx = sgt.query_max(l, r-k+2);
            ans[id] = mn <= c && c <= mx;
        }
    }
    for(int i = 0; i < q; i++) cout << ans[i] << '\n';
}
