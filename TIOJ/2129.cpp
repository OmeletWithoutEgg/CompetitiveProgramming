#include <cstdio>
#include <vector>
#include <utility>
#define ff first
#define ss second
#define pb emplace_back

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

typedef int ll;
const int N = 20025;
inline ll min(ll a, ll b){return a>b ? b : a;}
struct Segtree {
    ll mn[N<<1],lz[N];
    int n;
    void init(ll v[], int _n) {
        n = _n;
        for(int i = 0; i < n; i++) mn[i+n] = v[i];
        for(int i = n-1; i > 0; i--) mn[i] = min(mn[i<<1], mn[i<<1|1]);
        for(int i = 0; i < n; i++) lz[i] = 0;
    }
    void upd(int p, ll d) {
        mn[p] += d;
        if(p < n) lz[p] += d;
    }
    void pull(int p) {
        for(; p>1; p>>=1)
            mn[p>>1] = min(mn[p], mn[p^1]) + lz[p>>1];
    }
    void push(int p) {
        for(int h = 31 - __builtin_clz(n); h >= 0; h--) {
            int i = p >> h;
            upd(i, lz[i>>1]);
            upd(i^1, lz[i>>1]);
            lz[i>>1] = 0;
        }
    }
    void add(int l, int r, ll d) {
        int L = l, R = r;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) upd(l++, d);
            if(r&1) upd(--r, d);
        }
        pull(L+n), pull(R-1+n);
    }
    ll query(int l, int r) {
        ll res = 1e9;
        push(l+n), push(r-1+n);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res = min(res, mn[l++]);
            if(r&1) res = min(res, mn[--r]);
        }
        return res;
    }
} sgt;
ll dp[21][N], v[N];
signed main() {
    int n, k;
    n = nextint(), k = nextint();
    for(int i = 1; i <= n; i++) v[i] = nextint();
    dp[0][0] = 0;
    for(int i = 1; i <= n; i++) dp[0][i] = 1e9;
    for(int L = 1; L <= k; L++) {
        sgt.init(dp[L-1], n+1);
        std::vector<std::pair<ll,ll>> mx, mn;
        for(int i = 1; i <= n; i++) {
            {
                while(mx.size() && mx.back().ff <= v[i]) {
                    int r = mx.back().ss;
                    int l = mx.size() >= 2 ? mx[mx.size()-2].ss : 0;
                    sgt.add(l, r, -mx.back().ff);
                    mx.pop_back();
                }
                mx.pb(v[i], i);
                int r = mx.back().ss;
                int l = mx.size() >= 2 ? mx[mx.size()-2].ss : 0;
                sgt.add(l, r, mx.back().ff);
            }
            {
                while(mn.size() && mn.back().ff >= v[i]) {
                    int r = mn.back().ss;
                    int l = mn.size() >= 2 ? mn[mn.size()-2].ss : 0;
                    sgt.add(l, r, +mn.back().ff);
                    mn.pop_back();
                }
                mn.pb(v[i], i);
                int r = mn.back().ss;
                int l = mn.size() >= 2 ? mn[mn.size()-2].ss : 0;
                sgt.add(l, r, -mn.back().ff);
            }
            dp[L][i] = sgt.query(0, i);
            //cout << dp[L][i] << " \n"[i==n];
        }
    }
    printf("%lld\n", dp[k][n]);
}
