#include <bits/stdc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> void qqbx(const char*s, const H &h, T ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr (sizeof...(T)) qqbx(++s, args...);
}
#define pb emplace_back

using namespace std;
typedef long long ll;
const int N = 2500025;

struct Segtree {
    ll mx[N<<1];
    ll lz[N], ad[N];
    int n;
    void init(int _n) {
        n = 1;
        while(n < _n) n *= 2;
        for(int i = 0; i < n; i++) lz[i] = 0;
        for(int i = 1; i < n*2; i++) mx[i] = 0;
    }
    void upd(int p, ll w){
        mx[p] += w;
        if(p < n) lz[p] += w;
    }
    void down(int p) {
        if(!lz[p>>1]) return;
        upd(p, lz[p>>1]), upd(p^1, lz[p>>1]);
        lz[p>>1] = 0;
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; --h) {
            int i = p>>h;
            down(i);
        }
    }
    void pull(int p) {
        for(; p>0; p>>=1)
            mx[p>>1] = max(mx[p], mx[p^1]) + lz[p>>1];
    }
    void add(int l, int r, ll w) {
        /* for(int i = l; i < r; i++) mx[i] += w; return; */
        int L = l, R = r;
        push(l+n), push(r-1+n);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) upd(l++, w);
            if(r&1) upd(--r, w);
        }
        pull(L+n), pull(R-1+n);
    }
    ll query(int p) {
        push(p+n);
        return mx[p+n];
    }
    int bs(ll w) {
        /* for(int i = 0; i < n; i++) if(mx[i] > w) return i; return n; */
        /* for(int i = 0; i < n; i++) push(i+n); */
        push(n*2-1);
        if(mx[n*2] <= w) return n;
        int i = 1, l = 0, r = n;
        while(l+1 != r) {
            /* down(i<<=1); */
            int m = l+(r-l)/2;
            if(mx[i] > w)
                r = m;
            else
                l = m, i |= 1;
        }
        debug(l);
        return l;
    }
} sgt;
int l[N], r[N], w[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> l[i];
    for(int i = 0; i < n; i++) cin >> r[i];
    for(int i = 0; i < n; i++) cin >> w[i];
    vector<int> u;
    for(int i = 0; i < n; i++) u.pb(l[i]), u.pb(r[i]);
    sort(u.begin(), u.end()), u.erase(unique(u.begin(), u.end()), u.end());
    ll best = 0;
    sgt.init(u.size());
    for(int i = 0; i < n; i++) {
        l[i] = lower_bound(u.begin(), u.end(), l[i]) - u.begin();
        r[i] = lower_bound(u.begin(), u.end(), r[i]) - u.begin();
        ll dp = sgt.query(r[i]) + w[i];
        best = max(best, dp);
        vector<pair<int,int>> seg;
        int p = r[i]+1;
        debug(u.size(), p);
        while(p < u.size() && sgt.query(p) < dp) {
            int q = sgt.bs(sgt.query(p));
            seg.pb(p, q);
            p = q;
        }
        for(auto [L, R]: seg) sgt.add(L, R, -sgt.query(L));
        sgt.add(l[i], p, w[i]);
    }
    cout << best << '\n';
}
