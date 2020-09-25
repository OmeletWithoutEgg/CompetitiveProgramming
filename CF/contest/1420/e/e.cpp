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
constexpr ll N = 85, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e6;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

void ins(deque<pair<int,int>> &dq, pair<int,int> L) {
    auto check = [](pair<int,int> A, pair<int,int> B, pair<int,int> C) -> bool {
        // intersect(A, B) >= intersect(B, C)
        return (A.second - B.second) * (C.first - B.first) >= (B.second - C.second) * (B.first - A.first);
    };
    while(dq.size() >= 2 && check(dq[dq.size()-2], dq[dq.size()-1], L)) dq.pop_back();
    dq.push_back(L);
}
int query(deque<pair<int,int>> &dq, int x) {
    if(dq.empty()) return -inf;
    auto f = [x](pair<int,int> L) { return L.first * x + L.second; };
    while(dq.size() >= 2 && f(dq[0]) <= f(dq[1])) dq.pop_front();
    return f(dq[0]);
}
deque<pair<int,int>> dq[N][N*N];
int ans[N*N];
int a[N], pos[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> a[i];
    /* n=80; */
    /* for(int i =1; i<=n;i++) a[i]=rand()&1; */
    int tot = n * (n-1) / 2;
    int one = 0;
    for(int i = 1; i <= n; i++) one += a[i];
    for(int i = 1, j = 1; i <= n; i++) {
        if(a[i] == 1) {
            pos[j++] = i;
        }
    }
    ins(dq[0][0], {0, 0});
    for(int i = 1; i <= n; i++) {
        for(int o = 1; o <= one; o++) {
            for(int k = abs(i-pos[o]); k <= tot; k++) {
                /* for(int j = 0; j < i; j++) { */
                /*     dp[o][k][i] = max(dp[o][k][i], dp[o-1][k - abs(i-pos[o])][j] + (j-o+1) * (i-j-1)); */
                /*     // (j-(o-1)) * ((i-1)-j) = j*(i-1+o-1) - (o-1)*(i-1) - j*j */
                /* } */
                int dp = query(dq[o-1][k-abs(i-pos[o])], (i-1+o-1)) - (o-1)*(i-1);
                ins(dq[o][k], {i, dp - i*i});
                if(o == one) {
                    ans[k] = max(ans[k], dp + (i-o) * (n-i));
                }
            }
        }
    }
    for(int i = 1; i <= tot; i++) ans[i] = max(ans[i], ans[i-1]);
    for(int i = 0; i <= tot; i++) cout << ans[i] << (i == tot ? '\n' : ' ');
    /*
     * dp[i][j][k][last] = max(dp[i-1][j][k][last] + (last-j), dp[i-1][j-1][k - dist(last, i)][last]);
     * dp[i][j][c] = max(dp[i-1][j][c] + (i-j), max{dp[i-1][j'][c-1]})
     */
}
