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
    int cnt = sizeof...(T);
    std::cerr << "\033[1;32m(" << s << ") = (";
    ( (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")) , ... , void() );
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
constexpr ll N = 5025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

void chkmx(int &x, int v) {
    if(x < v) x = v;
}
int dp[N][N];
int con[7][N];
int sdp[N];
int scon[7];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int &x: a) cin >> x;
    vector<int> u = a;
    sort_uni(u);
    vector<int> id(n), prv(n), nxt(n);
    for(int i = 0; i < n; i++) {
        id[i] = get_pos(u, a[i]) + 1;
        if(binary_search(all(u), a[i]-1))
            prv[i] = get_pos(u, a[i]-1)+1;
        if(binary_search(all(u), a[i]+1))
            nxt[i] = get_pos(u, a[i]+1)+1;
    }
    vector<int> slen(n);
    sdp[0] = -inf;
    for(int i = 0; i <= n; i++) dp[0][i] = -inf;
    int best = 0;
    for(int i = 0; i < n; i++) {
        vector<int> len(i);
        slen[i] = max({ sdp[prv[i]], sdp[nxt[i]], scon[a[i]%7] }) + 1;
        chkmx(sdp[id[i]], slen[i]);
        chkmx(scon[a[i]%7], slen[i]);
        for(int j = 0; j < i; j++) {
            int y = id[j];
            len[j] = max({1 + slen[j], dp[prv[i]][y] + 1, dp[nxt[i]][y] + 1, con[a[i]%7][y] + 1});
            best = max(best, len[j]);
        }
        for(int j = 0; j < i; j++) {
            int L = len[j];
            chkmx(dp[id[i]][id[j]], L);
            chkmx(dp[id[j]][id[i]], L);
            chkmx(con[a[i]%7][id[j]], L);
            chkmx(con[a[j]%7][id[i]], L);
        }
    }
    cout << best << '\n';
}
