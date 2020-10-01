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
constexpr ll N = 100025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

void ins(deque<pll> &dq, ll v, ll pos) {
    while(dq.size() && dq.back().first <= v) dq.pop_back();
    dq.emplace_back(v, pos);
}
void maintain(deque<pll> &dq, int lim) {
    while(dq.size() && dq.front().second < lim) dq.pop_front();
}
array<ll,2> dp[N], nxt[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    ll G1, G2, G3;
    string s;
    cin >> n >> k >> G1 >> G2 >> G3 >> s;
    s = '#' + s + '#';
    int last = 0;
    for(int i = 1; i <= k; i++) dp[i][0] = dp[i][1] = -INF;
    dp[0][1] = -INF;
    for(int i = 1; i < n+2; i++) if(s[i] == '#') {
        int len = i - last - 1;
        last = i;
        if(len == 0) {
            for(int j = 0; j <= k; j++) dp[j][1] = -INF;
            // nxt[j][0] = dp[j][0]; nxt[j][1] = -INF
        } else if(len == 1) {
            // nxt[j][0] = max(dp[j][0], dp[j-1][0], dp[j][1])
            // nxt[j][1] = dp[j][0]
            for(int j = 0; j <= k; j++) {
                nxt[j][0] = max({dp[j][0], j ? dp[j-1][0] : -INF, dp[j][1]});
                nxt[j][1] = dp[j][0] + G3;
            }
            for(int j = 0; j <= k; j++) dp[j] = nxt[j];
        } else { // len >= 2
            for(int j = 0; j <= k; j++) nxt[j][0] = nxt[j][1] = -INF;
            for(int a : {0, 1}) for(int b : {0, 1}) {
                int rest = len - a - b;
                deque<pair<ll,ll>> dq[2];
                for(int j = 0; j <= k; j++) {
                    // (rest - j + (j-x)) / 2 != (rest + (j-x)) / 2 - (j / 2) if rest+(j-x) is even and j is odd
                    maintain(dq[0], j - rest);
                    maintain(dq[1], j - rest);
                    ins(dq[(rest+j) & 1], dp[j][b] + a * G3 + (rest + j) / 2 * G2, j);
                    ll good[2] = {dq[0].size() ? dq[0].front().first : -INF, dq[1].size() ? dq[1].front().first : -INF};
                    if(j & 1) {
                        nxt[j][a] = max({ nxt[j][a], good[0] - (j / 2 + 1) * G2, good[1] - j / 2 * G2 });
                    } else {
                        nxt[j][a] = max({ nxt[j][a], good[0] - j / 2 * G2, good[1] - j / 2 * G2 });
                    }
                    /* for(int x = 0; x <= j && x <= rest; x++) { */
                    /*     nxt[j][a] = max(nxt[j][a], dp[j-x][b] + a * G3 + (rest-x)/2 * G2); */
                    /* } */
                }
            }
            for(int j = 0; j <= k; j++) dp[j] = nxt[j];
        }
    }
    ll mx = -INF;
    for(int i = 0; i <= k; i++) mx = max(mx, dp[i][0] + i * G1);
    cout << mx << '\n';
}
