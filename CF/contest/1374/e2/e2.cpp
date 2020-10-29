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
constexpr ll N = 200025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct FenwickTree {
    int sum[N], cnt[N];
    void add(int x, int d) {
        for(int p = x; p < N; p += p & -p) sum[p] += x * d, cnt[p] += d;
    }
    int take(int k) {
        int x = 0, ans = 0;
        for(int s = 1<<__lg(N); s; s>>=1) if(x+s < N && cnt[x+s] < k) x+=s, k -= cnt[x], ans += sum[x];
        ans += k * (x+1);
        return ans;
    }
} fwt;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int k, m, n;
    cin >> n >> m >> k;
    vector<pair<int,int>> v[2][2];
    vector<int> pre[2][2];
    for(int i = 0; i < n; i++) {
        int t, a, b;
        cin >> t >> a >> b;
        v[a][b].pb(t, i+1);
    }
    for(int a : {0, 1}) for(int b : {0, 1}) {
        sort(all(v[a][b]));
        int s = v[a][b].size();
        pre[a][b] = vector<int>(s+1);
        for(int i = 0; i < s; i++) pre[a][b][i+1] = pre[a][b][i] + v[a][b][i].first;
    }
    int s = min(v[0][1].size(), v[1][0].size());
    for(int i = int(v[0][1].size()) - 1; i >= s; i--) fwt.add(v[0][1][i].first, 1);
    for(int i = int(v[1][0].size()) - 1; i >= s; i--) fwt.add(v[1][0][i].first, 1);
    for(auto [x, _]: v[0][0]) fwt.add(x, 1);
    for(auto [x, _]: v[1][1]) fwt.add(x, 1);
    int ans = -1;
    int pos = -1;
    for(int i = 0, j = s; i <= int(v[1][1].size()); i++) {
        if(i != 0) fwt.add(v[1][1][i-1].first, -1);
        while(j > 0 && i + j > k) {
            --j;
            fwt.add(v[0][1][j].first, 1);
            fwt.add(v[1][0][j].first, 1);
        }
        if(i + j < k || m - i - j * 2 < 0) continue;
        int now = pre[1][1][i] + pre[0][1][j] + pre[1][0][j] + fwt.take(m - i - j * 2);
        if(ans == -1 || ans > now) {
            ans = now;
            pos = i;
        }
    }
    if(ans == -1) cout << -1 << '\n';
    else {
        cout << ans << '\n';
        int i = pos;
        int j = k - i;
        vector<int> ans;
        for(int t = 0; t < i; t++) ans.pb(v[1][1][t].second);
        for(int t = 0; t < j; t++) ans.pb(v[1][0][t].second);
        for(int t = 0; t < j; t++) ans.pb(v[0][1][t].second);
        vector<pair<int,int>> rest = v[0][0];
        for(int t = j; t < int(v[1][0].size()); t++) rest.pb(v[1][0][t]);
        for(int t = j; t < int(v[0][1].size()); t++) rest.pb(v[0][1][t]);
        for(int t = i; t < int(v[1][1].size()); t++) rest.pb(v[1][1][t]);
        sort(all(rest));
        int s = m - i - j * 2;
        for(int t = 0; t < s; t++) ans.pb(rest[t].second);
        for(int x: ans) cout << x << ' ';
        cout << '\n';
    }
}
