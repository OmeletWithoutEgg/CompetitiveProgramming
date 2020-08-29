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
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
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

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int R, C, q;
    cin >> R >> C >> q;
    while(q--) {
        string T;
        cin >> T;
        int a, b;
        cin >> a >> b;
        if(T == "P") {
            if(a != b) cout << 0 << ' ' << 0 << '\n';
            else cout << R-1 << ' ' << 1 << '\n';
        } else if(T == "R") {
            if(a == b) cout << 1 << ' ' << 1 << '\n';
            else cout << 2 << ' ' << 2 << '\n';
        } else if(T == "Q") {
            if(a == b || a+R-1 == b || a == b+R-1) cout << 1 << ' ' << 1 << '\n';
            else {
                int ans = 0;
                // V H
                // H V
                ans += 2;
                // V D
                // D V
                ans += 2;
                // H D
                // D H
                if(b-R+1 >= 1) ++ans;
                if(b+R-1 <= C) ++ans;
                if(a-R+1 >= 1) ++ans;
                if(a+R-1 <= C) ++ans;
                // D D
                if((a+1+b-R) % 2 == 0 && (a+1+b-R) / 2 >= 1) ++ans;
                if((a-1+b+R) % 2 == 0 && (a-1+b+R) / 2 <= C) ++ans;
                cout << 2 << ' ' << ans << '\n';
            }
        } else if(T == "B") {
            // bishop
            if((a+1+b-r) & 1) cout << 0 << ' ' << 0 << '\n';
            else {
            }
        } else if(T == "K") {
            // king
            vector<int> fr(N), ifr(N);
            fr[0] = 1;
            for(int i = 1; i < N; i++) fr[i] = 1LL * fr[i-1] * i % MOD;
            for(int i = 0; i < N; i++) ifr[i] = modpow(fr[i], MOD-2);
            auto choose = [&](int n, int k) -> int64_t  {
                return 1LL * fr[n] * ifr[k] % MOD * ifr[n-k] % MOD;
            };
        }
    }
}
