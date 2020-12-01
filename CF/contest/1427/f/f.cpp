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
constexpr ll N = 201, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

int dp[2][N*2][N*6];
int fr[2][N*2][N*6];
int v[N*6];
vector<array<int,3>> ans;
void go(bool dir, int L, int i) {
    if(L == 0) return;
    int D = dp[dir][L][i];
    int a = fr[dir][L][i];
    assert(D);
    if(D <= 2) {
        int b = L - a;
        int j = i + a * 3;
        if(D == 1) go(dir, a, i), go(dir^(a&1), b, j);
        else go(dir, b, j), go(dir^(b&1), a, i);
    } else if(D <= 4) {
        int b = L - a - 1;
        int j = i + 1 + a * 3;
        int k = i + L * 3 - 1;
        if(D == 3) go(dir, a, i+1), go(dir^(a&1), b, j+1);
        else go(dir, b, j+1), go(dir^(b&1), a, i+1);
        ans.push_back({i, j, k});
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n * 3; i++) {
        int x;
        cin >> x;
        v[x] = 1;
    }
    /* for(int i = 1; i <= n*6; i++) cerr << i << ' '; */
    /* cerr << '\n'; */
    /* for(int i = 1; i <= n*6; i++) cerr << v[i] << ' '; */
    /* cerr << '\n'; */
    for(int i = 0; i < N*6; i++) dp[0][0][i] = dp[1][0][i] = 5;
    for(int L = 1; L <= n*2; L++) {
        for(int dir = 0; dir < 2; dir++) {
            for(int i = 1; i+L*3-1 <= n*6; i++) {
                for(int a = 1; a < L; a++) {
                    int b = L - a;
                    if(dp[dir][a][i] && dp[dir^(a&1)][b][i+a*3]) {
                        dp[dir][L][i] = 1;
                        fr[dir][L][i] = a;
                        break;
                    }
                    if(dp[dir^(b&1)][a][i] && dp[dir][b][i+a*3]) {
                        dp[dir][L][i] = 2;
                        fr[dir][L][i] = a;
                        break;
                    }
                }
                int turn = dir ^ (L & 1) ^ 1;
                if(dp[dir][L][i] || v[i] != turn || v[i+L*3-1] != turn) continue;
                for(int a = 0; a < L; a++) {
                    int b = L - a - 1;
                    int j = i + 1 + a*3;
                    if(v[j] != turn) continue;
                    if(dp[dir][a][i+1] && dp[dir^(a&1)][b][j+1]) {
                        dp[dir][L][i] = 3;
                        fr[dir][L][i] = a;
                        break;
                    }
                    if(dp[dir^(b&1)][a][i+1] && dp[dir][b][j+1]) {
                        dp[dir][L][i] = 4;
                        fr[dir][L][i] = a;
                        break;
                    }
                }
            }
        }
    }
    /* for(int L = 1; L <= n*2; L++) { */
    /*     for(int i = 1; i <= n*6; i++) { */
    /*         cerr << dp[0][L][i] << ' '; */
    /*     } */
    /*     cerr << '\n'; */
    /* } */
    if(!dp[1][n*2][1]) return -1;
    go(1, n*2, 1);
    for(int i = 0; i < n*2; i++) for(int j = 0; j < 3; j++) cout << ans[i][j] << (j == 2 ? '\n' : ' ');
}
