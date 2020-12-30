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
constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Dsu {
    vector<int> pa, rk, tag;
    Dsu(size_t n) : pa(n), rk(n), tag(n) {
        iota(all(pa), 0);
    }
    int anc(int x) { return x==pa[x] ? x : pa[x]=anc(pa[x]); }
    bool join(int x, int y) {
        if((x=anc(x)) == (y=anc(y))) return false;
        if(rk[x] < rk[y]) swap(x, y);
        return tag[x] |= tag[y], pa[y] = x, rk[x]!=rk[y] || ++rk[x];
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int m, n;
    cin >> m >> n;
    vector<tuple<int,int,int>> edges;
    Dsu dsu(n);
    vector<int> ans;
    auto used = [&dsu](int x) -> int& { return dsu.tag[dsu.anc(x)]; };
    for(int i = 1; i <= m; i++) {
        int k;
        cin >> k;
        if(k == 1) {
            int x;
            cin >> x;
            --x;
            if(!used(x)) {
                used(x) = i;
                ans.pb(i);
            }
            // ans.pb(i);
        } else {
            int x, y;
            cin >> x >> y;
            --x, --y;
            debug(x, used(x), y, used(y));
            if(!used(x) && !used(y)) {
                if(dsu.join(x, y)) {
                    ans.pb(i);
                }
            } else if(used(x) && !used(y))
                ans.pb(i);
            else if(!used(x) && used(y))
                ans.pb(i);
            dsu.join(x, y);
        }
    }
    // for(int i = 0; i < n; i++) if(used(i) > 0) ans.pb(used(i))
    sort_uni(ans);
    cout << modpow(2, ans.size()) << ' ' << ans.size() << '\n';
    for(int x: ans) cout << x << ' ';
    cout << '\n';
}
