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
constexpr ll N = 100025, INF = 1e18, MOD = 998244353, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

ll cnt[N], s1[N], s2[N], ans[N];
ll fr[N];
ll C(ll n, ll k) {
    if(k<0 || n<k) return 0;
    return fr[n]*modpow(fr[k]*fr[n-k], MOD-2) % MOD;
}
pll getCoef(ll n) {
    if(n <= 1) return {0, 0};
    if(n == 2) return {1, 1};
    return {(n-1) % MOD * modpow(2, n-2) % MOD, n % MOD * modpow(2, n-3) % MOD};
    ll c1=0,c2=0;
    for(int i = 0; i <= n; i++) c1 = (c1 + (i-1) * C(n-1, i-1)) % MOD;
    for(int i = 0; i <= n; i++) c2 = (c2 + (i-1) * C(n-2, i-2)) % MOD;
    return {c1, c2};
}
signed main() {
    fr[0]=1;
    for(int i = 1; i < N; i++) fr[i] = fr[i-1]*i%MOD;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int m;
    cin >> m;
    while(m--) {
        int a;
        cin >> a;
        cin >> cnt[a];
    }
    for(int i = 1; i < N; i++) s1[i] = cnt[i] * i % MOD, s2[i] = s1[i] * i % MOD;
    for(int i = 1; i < N; i++) {
        for(int j = i*2; j < N; j += i) {
            cnt[i] += cnt[j];
            s1[i] = (s1[i] + s1[j]) % MOD;
            s2[i] = (s2[i] + s2[j]) % MOD;
        }
    }
    for(int i = 1; i < N; i++) {
        ll xx = s2[i], xy = (s1[i] * s1[i] - s2[i] + MOD) % MOD;
        auto [c1, c2] = getCoef(cnt[i]);
        ans[i] = (xx * c1 + xy * c2) % MOD;
    }
    for(int i = N-1; i >= 1; i--) {
        for(int j = i*2; j < N; j += i) {
            ans[i] = (ans[i] - ans[j] + MOD) % MOD;
        }
    }
    cout << ans[1] << '\n';
}
/*
 * sum(A) * \sum_{x\in A} (sum(A) - x)
 * = sum(A)^2 * |A| - sum(A)^2
 * \sum_{k=0}^{|S|} (k-1) \sum_{|A| = k} sum(A)^2
 * \sum_{|A|=k} sum(A)^2 = \sum_{x\in S} x^2 * C(|S|-1, k-1) + 2\sum_{x,y\in S} xy * C(|S|-2, k-2)
 */
