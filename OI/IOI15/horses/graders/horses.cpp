#pragma GCC optimize("Ofast")
#include "horses.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(a...) qqbx(#a, a)
#define pary(a...) danb(#a, a)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using ld = long double;
using ll = long long;
using namespace std;
const int maxn = 500025;
const int mod = 1000000007;

struct Segtree {
    pair<ld,int> st[maxn * 2];
    ld lz[maxn];
    int n;
    void build(int N) {
        n = N;
        for (int i = n-1; i > 0; i--)
            st[i] = max(st[i<<1], st[i<<1|1]), lz[i] = 0;
    }
    void upd(int p, ld x) {
        st[p].first += x;
        if (p < n) lz[p] += x;
    }
    void pull(int p) {
        for (; p > 1; p>>=1) {
            st[p>>1] = max(st[p], st[p^1]);
            st[p>>1].first += lz[p>>1];
        }
    }
    void add(int l, int r, ld x) {
        int L = l, R = r;
        // push(l+n), push(r-1+n);
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) upd(l++, x);
            if (r&1) upd(--r, x);
        }
        pull(L+n), pull(R-1+n);
    }
    int query() {
        return st[1].second;
        pair<ld,int> r;
        for (int i = 0; i < n; i++) {
            r = max(r, st[i + n]);
        }
        return r.second;
    }
} sgt;

ll modpow(ll e, ll p) {
    ll r = 1;
    while (p) {
        if (p&1) r = r*e%mod;
        e = e*e%mod;
        p >>= 1;
    }
    return r;
}
struct Fenwick {
    int n;
    ll b[maxn];
    void init(int N) {
        n = N;
        for (int i = 1; i <= n; i++) b[i] = 1;
    }
    void add(int p, ll d) {
        for (++p; p <= n; p += p&-p) b[p] = b[p] * d % mod;
    }
    ll query(int p) {
        ll r = 1;
        for (++p; p > 0; p -= p&-p) r = r * b[p] % mod;
        return r;
    }
} BIT;
int x[maxn], y[maxn], n;
int init(int N, int X[], int Y[]) {
    long double sum = 0;
    BIT.init(N);
    for (int i = 0; i < N; i++) {
        sum += log(X[i]);
        sgt.st[i + N] = { sum + log(Y[i]), i };
        BIT.add(i, X[i]);
    }
    sgt.build(N);
    n = N;
    for (int i = 0; i < N; i++) x[i] = X[i];
    for (int i = 0; i < N; i++) y[i] = Y[i];
    int p = sgt.query();
    debug(p, N);
    ll prod = 1;
    for (int i = 0; i <= p; i++) prod = prod * X[i];
    debug(prod);
    return BIT.query(p) * y[p] % mod;
}

int updateX(int pos, int val) {	
    sgt.add(pos, n, -log(x[pos]));
    BIT.add(pos, modpow(x[pos], mod-2));
    x[pos] = val;
    sgt.add(pos, n, log(x[pos]));
    BIT.add(pos, x[pos]);
    int p = sgt.query();
    return BIT.query(p) * y[p] % mod;
}

int updateY(int pos, int val) {
    sgt.add(pos, pos+1, -log(y[pos]));
    y[pos] = val;
    sgt.add(pos, pos+1, log(y[pos]));
    int p = sgt.query();
    return BIT.query(p) * y[p] % mod;
}
