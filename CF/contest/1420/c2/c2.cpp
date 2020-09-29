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
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    std::cerr << "\033[1;32m" << '(' << s << ')' << " = " << '(';
    constexpr int size = sizeof...(T);
    int cnt = size, dummy[size] = { (std::cerr << args << (--cnt ? ", " : ")\033[0m\n"), 0)... };
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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Segtree {
    struct node : array<array<ll,2>,2> {
        node(int x) {
            at(0)[0] = x;
            at(1)[1] = -x;
            at(0)[1] = at(1)[0] = -INF;
        }
        node() {
            for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) at(i)[j] = 0;
        }
        friend node operator+(const node &a, const node &b) {
            node res;
            for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) res[i][j] = max(a[i][j], b[i][j]);
            for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) {
                for(int k = 0; k < 2; k++) {
                    res[i][j] = max(a[i][k] + b[!k][j], res[i][j]);
                }
            }
            return res;
        }
    };
    vector<node> st;
    int n;
    Segtree(const vector<int> &a) : n(a.size()) {
        st.resize(n*2);
        for(int i = 0; i < n; i++) st[i+n] = node(a[i]);
        for(int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
    }
    void modify(int p, int d) {
        for(st[p+=n] = node(d); p>>=1; )
            st[p] = st[p<<1] + st[p<<1|1];
    }
    ll query(int l, int r) {
        node resl, resr;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) resl = resl + st[l++];
            if(r&1) resr = st[--r] + resr;
        }
        node res = resl + resr;
        return max(res[0][0], res[0][1]);
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for(int i = 0; i < n; i++) cin >> a[i];
        Segtree sgt(a);
        cout << sgt.query(0, n) << '\n';
        for(int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            swap(a[l], a[r]);
            sgt.modify(l, a[l]);
            sgt.modify(r, a[r]);
            cout << sgt.query(0, n) << '\n';
        }
    }
}