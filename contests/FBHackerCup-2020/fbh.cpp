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
 
#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) { string s=qqbx(__VA_ARGS__);std::cerr<<__PRETTY_FUNCTION__<<" #"<<__LINE__<<"\n\t("<<#__VA_ARGS__<< ") = ("<<s<<")\n"; }
template <typename H, typename ...T> constexpr std::string qqbx(const H &h, T &&...args) {
    if constexpr(sizeof...(T)) return std::to_string(h) + ", " + qqbx(args...); // C++ 17!
    return std::to_string(h);
}
#else
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
constexpr ll N = 10025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

#define int ll
vector<int> read(int k, int n) {
    vector<int> res(n);
    for(int i = 0; i < k; i++) cin >> res[i];
    ll A, B, C, D;
    cin >> A >> B >> C >> D;
    for(int i = k; i < n; i++) res[i] = (A * res[i-2] + B * res[i-1] + C) % D + 1;
    return res;
}
struct seg {
    int h, l, r;
};
void solve() {
    int n, k, w;
    cin >> n >> k >> w;
    auto L = read(k, n), H = read(k, n);
    deque<seg> dq;
    ll res = 1, ans = 0;
    vector<int> h(L[n-1]+w+1);
    for(int i = 0; i < n; i++) {
        ans += 2 * (i ? min(w, L[i]-L[i-1]) : w);
        for(int j = L[i]; j < L[i]+w; j++) h[j] = max(h[j], H[i]);
        int sum=0;
        for(int j = L[0]; j < L[i]+w; j++) sum += abs(h[j]-h[j+1]);
        for(int j = L[0]; j < L[i]+w; j++) cerr<<h[j]<<' ';cerr<<endl;
        debug(ans,sum);
        res *= (ans+sum);
        res %= MOD;
    }
    cout<<res<<'\n';
}
signed main() {
    /* freopen("../dislodging_logs_input.txt", "r", stdin); */
    /* freopen("../dislodging_logs_output.txt", "w", stdout); */
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    for(int tc = 1; tc <= t; tc++) {
        cout << "Case #" << tc << ": ";
        solve();
    }
}
