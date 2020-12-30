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
constexpr ll N = 400025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Segtree {
    ll sum[1 << 20], lz[1 << 19];
    int n = 1 << 19;
    void upd(int p, ll d, int len) {
        sum[p] += d * len;
        if(p < n) lz[p] += d;
    }
    void pull(int p) {
        for(int len = 2; p>1; p>>=1, len<<=1)
            sum[p>>1] = sum[p] + sum[p^1] + lz[p>>1] * len;
    }
    void push(int p, int len) {
        if(!lz[p>>1]) return;
        upd(p, lz[p>>1], len);
        upd(p^1, lz[p>>1], len);
        lz[p>>1] = 0;
    }
    void add(int l, int r, ll d) {
        int tl = l, tr = r, len = 1;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1, len<<=1) {
            if(l&1) upd(l++, d, len);
            if(r&1) upd(--r, d, len);
        }
        pull(tl+n), pull(tr-1+n);
    }
    int getKth(int k) {
        if(sum[1] < k) return 1e9;
        int i = 1, len = n;
        while(i < n) {
            i <<= 1;
            len >>= 1;
            push(i, len);
            if(sum[i] < k) {
                k -= sum[i];
                i |= 1;
            }
        }
        return i - n;
    }
} sgt;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> L(n);
    for(int &x: L) cin >> x;
    sort(all(L), greater<int>());
    if(accumulate(all(L), 0LL) - n * 2 + 1 < k) return cout << -1 << '\n', 0;
    sgt.add(0, 1, 1);
    int ans = 1e9;
    for(int len: L) {
        int half = len / 2;
        int dep = sgt.getKth(1);
        sgt.add(dep, dep+1, -1);
        sgt.add(dep+2, dep+half+2, 1);
        sgt.add(dep+2, dep+len-1-half+2, 1);
        ans = min(ans, sgt.getKth(k));
    }
    cout << ans << '\n';
}
