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
constexpr ll N = 100025, INF = 1e18, MOD = 998244353, K = 19, inf = 1e7;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

void FFT(vector<int> &F, bool inv) {
    int n = F.size();
    for(int i = 0, j = 0; i < n; i++) {
        if(i < j) swap(F[i], F[j]);
        for(int k = n>>1; (j^=k) < k; k>>=1);
    }
    for(int s = 1; s < n; s <<= 1) {
        int omega = modpow(3, (MOD-1) / (s*2));
        if(inv) omega = modpow(omega, MOD-2);
        for(int i = 0; i < n; i += s*2) {
            ll now = 1;
            for(int j = 0; j < s; j++) {
                int a = F[i+j], b = F[i+j+s] * now % MOD;
                F[i+j] = (a+b < MOD ? a+b : a+b-MOD);
                F[i+j+s] = (a-b < 0 ? a-b+MOD : a-b);
                now = now * omega % MOD;
            }
        }
    }
    if(inv) {
        ll in = modpow(n, MOD-2);
        for(int i = 0; i < n; i++) F[i] = F[i] * in % MOD;
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    int sz = 1 << __lg(n*5+1) + 1;
    vector<int> cnt(sz);
    for(int i = 0; i < k; i++) {
        int d;
        cin >> d;
        ++cnt[d];
    }
    FFT(cnt, false);
    for(int i = 0; i < sz; i++) cnt[i] = modpow(cnt[i], n/2);
    FFT(cnt, true);
    int ans = 0;
    for(int i = 0; i < sz; i++) ans = (ans + 1LL * cnt[i] * cnt[i]) % MOD;
    cout << ans << '\n';
}
