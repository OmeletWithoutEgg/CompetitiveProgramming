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
using ost = std::ostream;
#define DESTL(STL, BEG, END, OUT) \
    template <typename ...T> ost& operator<<(ost &O, std::STL<T...> v) { int f=0; for(auto x: v) O << (f++ ? ", " : BEG) << OUT; return O << END; }
DESTL(deque, "[", "]", x); DESTL(vector, "[", "]", x);
DESTL(set, "{", "}", x); DESTL(multiset, "{", "}", x); DESTL(unordered_set, "{", "}", x);
DESTL(map , "{", "}", x.first << ":" << x.second); DESTL(unordered_map , "{", "}", x.first << ":" << x.second);
template <typename U, typename V> ost& operator<<(ost &O, std::pair<U,V> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> ost& operator<<(ost &O, std::array<T,N> a) { int f=0; for(T x: a) O << (f++ ? ", " : "[") << x; return O << "]"; }
template <typename T, size_t ...I> ost& prtuple(ost &O, T t, std::index_sequence<I...>) { return (..., (O << (I ? ", " : "(") << std::get<I>(t))), O << ")"; }
template <typename ...T> ost& operator<<(ost &O, std::tuple<T...> t) { return prtuple(O, t, std::make_index_sequence<sizeof...(T)>()); }
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
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
constexpr inline ll cdiv(ll x, ll m) { return x/m + (((x<0)^(m>0)) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

bool cmpAngle(tuple<int,int,int> a, tuple<int,int,int> b) {
    int qa = (get<1>(a) == 0 ? (get<0>(a) > 0 ? 0 : 2) : (get<1>(a) > 0 ? 1 : 3));
    int qb = (get<1>(b) == 0 ? (get<0>(b) > 0 ? 0 : 2) : (get<1>(b) > 0 ? 1 : 3));
    if(qa != qb) return qa < qb;
    return 1LL * get<0>(a) * get<1>(b) - 1LL * get<1>(a) * get<0>(b) > 0;
}
bool cmpDist(tuple<int,int,int> a, tuple<int,int,int> b) {
    /* return max(abs(get<0>(a)), abs(get<1>(a))) < max(abs(get<0>(b)), abs(get<1>(b))); */
    return 1LL * get<0>(a) * get<0>(a) + 1LL * get<1>(a) * get<1>(a) < 1LL * get<0>(b) * get<0>(b) + 1LL * get<1>(b) * get<1>(b);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<pair<int,int>> a(n), b(m);
    for(auto &[x, y]: a) cin >> x >> y;
    for(auto &[x, y]: b) cin >> x >> y;
    /* mt19937 rng(7122); */
    /* for(auto &[x, y]: b) x = uniform_int_distribution<int>(-inf, inf)(rng), y = uniform_int_distribution<int>(-inf, inf)(rng); */
    /* b[0] = {0, 3}, b[1] = {0, 4}, b[2] = {0, 5}; */
    /* vector<vector<int>> rk(n, vector<int>(m)); */
    vector<vector<int>> prv(n, vector<int>(m, inf));
    for(int t = 0; t < n; t++) {
        auto [x0, y0] = a[t];
        vector<tuple<int,int,int>> v(m);
        for(int i = 0; i < m; i++) {
            auto [x, y] = b[i];
            v[i] = {x-x0, y-y0, i};
        }
        sort(v.begin(), v.end(), [](auto A, auto B) { return cmpAngle(A, B) || (!cmpAngle(B, A) && cmpDist(A, B)); });
        debug(x0, y0, v);
        
        for(int i = 0, j = 0; i < m; i = j) {
            int last = -1;
            for(j = i; j < m; j++) {
                if(cmpAngle(v[i], v[j])) break;
                int id = get<2>(v[j]);
                /* rk[t][id] = j - i; */
                prv[t][id] = last;
                last = id;
            }
            debug(i, j);
        }
    }
    debug(prv);
    int tot = 0;
    vector<int> vis(m);
    function<bool(vector<int>&, int&, int)> dfs = [&](vector<int> &p, int &id, int now) -> bool {
        if(vis[now] == tot) return true;
        if(id == n) return false;
        for(int t = p[id++], x = prv[t][now]; x != -1; x = prv[t][x]) if(!dfs(p, id, x)) return false;
        vis[now] = tot;
        return true;
    };
    vector<int> ans(m);
    vector<int> p(n);
    iota(all(p), 0);
    do {
        for(int i = 0; i < m; i++) {
            int x = 0;
            ++tot;
            if(dfs(p, x, i)) ans[i] = 1;
        }
    } while(next_permutation(all(p)));
    debug(ans);
    cout << accumulate(all(ans), 0) << '\n';
}
