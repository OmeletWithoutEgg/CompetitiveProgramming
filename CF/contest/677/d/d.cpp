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
// #define _GLIBCXX_DEBUG AC
#include <bits/extc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(deque, "[", "]", e) ; NIE(vector, "[", "]", e)
NIE(set, "{", "}", e) ; NIE(multiset, "{", "}", e) ; NIE(unordered_set, "{", "}", e)
NIE(map , "{", "}", e.first << ":" << e.second)
NIE(unordered_map , "{", "}", e.first << ":" << e.second)
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
#define pb emplace_back
#define all(v) begin(v),end(v)
#define mem(v,x) memset(v,x,sizeof v)
#define ff first
#define ss second
 
template <typename T, T MOD> class Modular {
public:
    constexpr Modular() : v() {}
    template <typename U> Modular(const U &u) { v = (0 <= u && u < MOD ? u : (u%MOD+MOD)%MOD); }
    template <typename U> explicit operator U() const { return U(v); }
    T operator()() { return v; }
#define REFOP(type, expr...) Modular &operator type (const Modular &rhs) { return expr, *this; }
    REFOP(+=, v += rhs.v - MOD, v += MOD & (v >> width)) ; REFOP(-=, v -= rhs.v, v += MOD & (v >> width))
    // fits for MOD^2 <= 9e18
    REFOP(*=, v = 1LL * v * rhs.v % MOD) ; REFOP(/=, *this *= inverse(rhs.v))
#define VALOP(op) friend Modular operator op (Modular a, const Modular &b) { return a op##= b; }
    VALOP(+) ; VALOP(-) ; VALOP(*) ; VALOP(/)
    Modular operator-() const { return 0 - *this; }
    friend bool operator == (const Modular &lhs, const Modular &rhs) { return lhs.v == rhs.v; }
    friend bool operator != (const Modular &lhs, const Modular &rhs) { return lhs.v != rhs.v; }
    friend std::istream & operator>>(std::istream &I, Modular &m) { T x; I >> x, m = x; return I; }
    friend std::ostream & operator<<(std::ostream &O, const Modular &m) { return O << m.v; }
private:
    constexpr static int width = sizeof(T) * 8 - 1;
    T v;
    static T inverse(T a) {
        // copy from tourist's template
        T u = 0, v = 1, m = MOD;
        while (a != 0) {
            T t = m / a;
            m -= t * a; std::swap(a, m);
            u -= t * v; std::swap(u, v);
        }
        assert(m == 1);
        return u;
    }
};

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = std::priority_queue<T,vector<T>,less<T> >;
template <typename T> using min_heap = std::priority_queue<T,vector<T>,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <typename V, typename T> int get_pos(const V &v, T x) { return lower_bound(all(v),x) - begin(v); }
template <typename V> void sort_uni(V &v) { sort(all(v)), v.erase(unique(all(v)),end(v)); }
template <typename T> bool chmin(T &x, const T &v) { return v < x ? (x=v, true) : false; }
template <typename T> bool chmax(T &x, const T &v) { return x < v ? (x=v, true) : false; }
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 500025, INF = 1e18, MOD = 1000000007, K = 325, inf = 1e9;
using Mint = Modular<int, MOD>;
Mint modpow(Mint e, uint64_t p) { Mint r = 1; while(p) (p&1) && (r *= e), e *= e, p >>= 1; return r; } // 0^0 = 1

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    vector<vector<int>> dp(n, vector<int>(m, inf));
    vector<vector<pair<int,int>>> pos(p);
    auto BFS = [&dp, n, m](vector<pair<int,int>> &p) {
        constexpr int dx[4] = {1, 0, -1, 0};
        constexpr int dy[4] = {0, 1, 0, -1};
        vector<vector<int>> dis(n, vector<int>(m, -1));
        sort(all(p), [&](pair<int,int> a, pair<int,int> b) { return dp[a.first][a.second] < dp[b.first][b.second]; });
        int it = 0;
        queue<pair<int,int>> q;
        dis[p[0].ff][p[0].ss] = dp[p[0].ff][p[0].ss];
        q.emplace(p[it++]);
        debug(dp, p);
        while(!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            while(it < p.size() && dis[x][y] == dp[p[it].ff][p[it].ss]) {
                auto [px, py] = p[it++];
                dis[px][py] = dp[px][py];
                q.emplace(px, py);
            }
            for(int k = 0; k < 4; k++) {
                int nx = x+dx[k], ny = y+dy[k];
                if(nx >= 0 && nx < n && ny >= 0 && ny < m && dis[nx][ny] == -1) {
                    dis[nx][ny] = dis[x][y] + 1;
                    q.emplace(nx, ny);
                }
            }
        }
        debug(dis);
        return dis;
    };
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int v;
            cin >> v;
            --v;
            pos[v].pb(i, j);
        }
    }
    for(auto [x, y]: pos[0]) dp[x][y] = x + y;
    debug(dp, pos[0]);
    for(int i = 1; i < p; i++) {
        if(pos[i-1].size() < K) {
            for(auto [xi, yi]: pos[i])
                for(auto [xj, yj]: pos[i-1])
                    chmin(dp[xi][yi], dp[xj][yj] + abs(xi-xj) + abs(yi-yj));
        } else {
            auto dis = BFS(pos[i-1]);
            for(auto [x, y]: pos[i]) dp[x][y] = dis[x][y];
            debug(dp);
        }
    }
    int ans = inf;
    for(auto [x, y]: pos.back()) chmin(ans, dp[x][y]);
    cout << ans << '\n';
}
