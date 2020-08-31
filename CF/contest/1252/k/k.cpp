//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\
//   \###################\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.
 
#ifdef local
#include <bits/extc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#else
#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#include <bits/stdc++.h>
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define get_pos(v,x) int(lower_bound(begin(v),end(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define ff first
#define ss second
#define mem(v,x) memset(v,x,sizeof v)
 
using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = std::priority_queue<T,vector<T>,less<T> >;
template <typename T> using min_heap = std::priority_queue<T,vector<T>,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

array<array<int,2>,2> F[2], I;
void pr(array<array<int,2>,2> a) {
    cerr << '{' << a[0][0] << ',' << a[0][1] << '}' << ' ' << '{' << a[1][0] << ',' << a[1][1] << '}' << '\n';
}
array<array<int,2>,2> mul(const array<array<int,2>,2> &a, const array<array<int,2>,2> &b) {
     array<array<int,2>,2> c = {};
     for(int i = 0; i < 2; i++) for(int k = 0; k < 2; k++) for(int j = 0; j < 2; j++) c[i][j] = (c[i][j] + 1LL * a[i][k] * b[k][j]) % MOD;
     return c;
}
struct segtree {
    array<array<int,2>,2> st[1 << 19];
    bool rev[1 << 18];
    int n;
    void init(const string &s, int _n) {
        n=1; while(n<_n) n<<=1;
        for(int i = 0; i < n; i++) st[i+n] = i<_n ? F[s[i]=='A'] : I;
        for(int i = n-1; i > 0; i--) st[i] = mul(st[i<<1], st[i<<1|1]);
    }
    void upd(int p) {
        swap(st[p][0][0], st[p][1][1]);
        swap(st[p][0][1], st[p][1][0]);
        if(p < n) rev[p] = !rev[p];
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p>>h;
            if(!rev[i>>1]) continue;
            upd(i), upd(i^1);
            rev[i>>1] = 0;
        }
    }
    void pull(int p) {
        for(p>>=1; p>0; p>>=1) {
            st[p] = mul(st[p<<1], st[p<<1|1]);
            if(rev[p]) {
                swap(st[p][0][0], st[p][1][1]);
                swap(st[p][1][0], st[p][0][1]);
            }
        }
    }
    void modify(int l, int r) {
        int L = l, R = r;
        push(l+n), push(r-1+n);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) upd(l++);
            if(r&1) upd(--r);
        }
        pull(L+n), pull(R-1+n);
    }
    array<array<int,2>,2> query(int l, int r) {
        array<array<int,2>,2> resl = I;
        array<array<int,2>,2> resr = I;
        push(l+n), push(r-1+n);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) resl = mul(resl, st[l++]);
            if(r&1) resr = mul(st[--r], resr);
        }
        return mul(resl, resr);
    }
} sgt;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    F[0][0][0] = F[0][0][1] = F[0][1][1] = 1;
    F[1][0][0] = F[1][1][0] = F[1][1][1] = 1;
    I[0][0] = I[1][1] = 1;
    int n, q;
    string s;
    cin >> n >> q >> s;
    sgt.init(s, n);
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int l, r;
            cin >> l >> r;
            --l;
            sgt.modify(l, r);
        } else if(t == 2) {
            int l, r, a, b;
            cin >> l >> r >> a >> b;
            --l;
            array<array<int,2>,2> M = sgt.query(l, r);
            /* pr(M); */
            cout << (1LL * a * M[0][0] + 1LL * b * M[1][0]) % MOD << ' ' << (1LL * a * M[0][1] + 1LL * b * M[1][1]) % MOD << '\n';
        }
    }
}
