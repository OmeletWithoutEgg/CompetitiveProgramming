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
    vector<ll> sum, lz;
    int n;
    Segtree(int _n) : n(_n), sum(_n<<1), lz(_n) {}
    void upd(int p, int d, int len) {
        sum[p] += 1LL * d * len;
        if(p < n) lz[p] += d;
    }
    void pull(int p) {
        for(int len = 2; p>1; p>>=1, len<<=1)
            sum[p>>1] = sum[p] + sum[p^1] + lz[p>>1] * len;
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p >> h;
            if(!lz[i>>1]) continue;
            upd(i, lz[i>>1], 1<<h);
            upd(i^1, lz[i>>1], 1<<h);
            lz[i>>1] = 0;
        }
    }
    void add(int l, int r, int d) {
        l = max(0, min(n, l));
        r = max(0, min(n, r));
        if(l >= r) return;
        int L = l, R = r, len = 1;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1, len<<=1) {
            if(l&1) upd(l++, d, len);
            if(r&1) upd(--r, d, len);
        }
        pull(L+n), pull(R-1+n);
    }
    ll query(int l, int r) {
        l = max(0, min(n, l));
        r = max(0, min(n, r));
        if(l >= r) return 0;
        push(l+n), push(r-1+n);
        safe;
        ll res = 0;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res += sum[l++];
            if(r&1) res += sum[--r];
        }
        safe;
        return res;
    }
};
vector<int> getLCP(string s, const string &p) {
    s += '$';
    int O = s.size();
    s += p;
    int j = 0, r = 0;
    vector<int> Z(s.size());
    for(int i = 1; i < int(s.size()); i++) {
        Z[i] = max(0, min(Z[i-j], r-i));
        while(i+Z[i] < int(s.size()) && s[Z[i]] == s[i+Z[i]]) ++Z[i];
        if(i+Z[i] > r) {
            j = i;
            r = i+Z[i];
        }
    }
    return vector<int>(Z.begin() + O, Z.end());
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    string a, b, s;
    cin >> n >> m >> a >> b >> s;
    auto Za = getLCP(s, a);
    reverse(all(s));
    reverse(all(b));
    auto Zb = getLCP(s, b);
    reverse(all(Zb));
    // sui bian -> luan suan
    // rb < la
    // la < rb, more, rb-la+1 >= s.size() -> rb >= la+s.size()-1
    ll ans = 0;
    {
        vector<int> sufA(n+1), sufB(n+1);
        for(int i = 0; i < n; i++) ++sufA[Za[i]];
        for(int i = 0; i < n; i++) ++sufB[Zb[i]];
        for(int i = n-1; i >= 0; i--) sufA[i] += sufA[i+1];
        for(int i = n-1; i >= 0; i--) sufB[i] += sufB[i+1];
        for(int i = 1; i <= n; i++) {
            int j = m-i;
            if(j <= 0 || j > n) continue;
            ans += 1LL * sufA[i] * sufB[j];
        }
    }
    {
        Segtree sgt(n+1);
        for(int i = 0; i < n; i++) {
            debug(i);
            debug(m-Za[i], m, Zb[i]);
            ans -= sgt.query(m-Za[i], m);
            sgt.add(1, Zb[i]+1, 1);
        }
    }
    {
        Segtree sgt(n+1);
        for(int i = 0; i < n; i++) {
            if(i >= m-1) sgt.add(1, Za[i-m+1]+1, 1);
            ans -= sgt.query(m-Zb[i], m);
        }
    }
    cout << ans << '\n';
}
