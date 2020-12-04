//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\Q
//   \###################\Q
//    \        ____       \B
//     \_______\___\_______\X
// An AC a day keeps the doctor away.
 
#ifdef local
#include <bits/extc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(deque, "[", "]", e); NIE(vector, "[", "]", e); NIE(set, "{", "}", e);
NIE(multiset, "{", "}", e); NIE(unordered_set, "{", "}", e);
NIE(map , "{", "}", e.first << ":" << e.second);
NIE(unordered_map , "{", "}", e.first << ":" << e.second);
template <typename ...T> TAK(std::pair<T...> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> TAK(std::array<T,N> a) { return O << std::vector<T>(a.begin(), a.end()); }
template <typename ...T> TAK(std::tuple<T...> t) {
    return O << "(", std::apply([&O](T ...s){ int f=0; (..., (O << (f++ ? ", " : "") << s)); }, t), O << ")";
}
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
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
constexpr ld PI = acos(-1), eps = 1e-8;
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct BIT {
    int mx[N], n;
    void init(int _n) {
        n = _n;
        for(int i = 1; i <= n; i++) mx[i] = -1;
    }
    void add(int p, int v) {
        for(; p <= n; p += p&-p) mx[p] = max(mx[p], v);
    }
    int qry(int p) {
        int r = -1;
        for(; p > 0; p -= p&-p) r = max(r, mx[p]);
        return r;
    }
} fwt;
int h[N];
ll v[N];
int n, q;
ld solve() {
    ld ans = -1;
    auto calc = [&]() {
        vector<ll> u(v, v+n+1);
        debug(u);
        sort_uni(u);
        fwt.init(u.size());
        for(int i = n; i >= 0; i--) {
            int p = u.size() - get_pos(u, v[i]);
            int j = fwt.qry(p);
            fwt.add(p, i);
            if(j != -1) debug(i, j, v[i], v[j]);
            if(j == -1 || v[j] < v[i]) continue;
            ll s = i ? v[i-1] - v[i] : -1;
            if(s > 0) {
                ans = max(ans, j-i + clamp((v[j] - v[i]) / ld(s), ld(0), ld(1)));
            } else {
                ans = max(ans, ld(j-i));
            }
        }
    };
    calc();
    reverse(v,v+n+1);
    for(int i = 0; i <= n; i++) v[i] = -v[i];
    calc();
    return ans;
}
// ans * 1000000 and calc
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i <= n; i++) cin >> h[i];
    while(q--) {
        ld g;
        cin >> g;
        int s = g * 10;
        for(int i = 0; i <= n; i++) v[i] = h[i] - 1LL * s * i;
        ld ans = solve();
        if(ans < 1)
            cout << -1 << '\n';
        else
            cout << fixed << setprecision(10) << solve() << '\n';
    }
}
