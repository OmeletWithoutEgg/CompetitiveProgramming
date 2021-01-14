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
constexpr ll N = 500025, INF = 1e18, MOD = 1000000007, K = 81, inf = 1e9;
using Mint = Modular<int, MOD>;
Mint modpow(Mint e, uint64_t p) { Mint r = 1; while(p) (p&1) && (r *= e), e *= e, p >>= 1; return r; } // 0^0 = 1

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int A, B;
    cin >> A >> B;
    vector<vector<int>> d(A+1, vector<int>(B+1));
    for(int i = 1; i <= A; i++) {
        for(int j = 1; j <= B; j++) {
            cin >> d[i][j];
        }
    }
    vector<tuple<int,int,int>> edges;
    const int n = 101;
    auto encode = [&](int i, int j) {
        return i * 2 + j;
    };
    auto addEdge = [&](int a, int b, int c) {
        debug(a, b, c);
        edges.pb(a, b, c);
    };
    for(int i = 1; i < n; i++)
        addEdge(encode(i-1, 0), encode(i, 0), -1);
    for(int a = 0; a < n; a++) {
        for(int b = 0; b < n; b++) {
            int mx = -inf;
            for(int i = 1; i <= A; i++) {
                for(int j = 1; j <= B; j++) {
                    mx = max(mx, d[i][j] - a * i - b * j);
                }
            }
            // mx >= 0
            if(mx >= 0) addEdge(encode(a, 0), encode(b, 1), mx);
        }
    }
    for(int i = n-1; i >= 1; i--)
        addEdge(encode(i, 1), encode(i-1, 1), -2);
    debug(edges);
    vector<int> dis(n*2);
    for(int i = 1; i <= A; i++) {
        for(int j = 1; j <= B; j++) {
            for(int t = 1; t < n*2; t++) dis[t] = -1;
            dis[0] = 0;
            for(int t = 0; ; t++) {
                bool relax = false;
                for(auto [a, b, c]: edges) {
                    if(c == -1) {
                        c = i;
                    } else if(c == -2) {
                        c = j;
                    } else assert(c >= 0);
                    if(dis[b] == -1 || dis[b] > dis[a] + c)
                        dis[b] = dis[a] + c, relax = true;
                }
                if(!relax) break;
                assert(t == 0);
            }
            debug(dis);
            debug(dis[encode(0, 1)], d[i][j]);
            if(dis[encode(0, 1)] != d[i][j])
                return cout << "Impossible\n", 0;
        }
    }
    cout << "Possible\n";
    cout << n*2 << ' ' << edges.size() << '\n';
    for(auto [a, b, c]: edges) {
        cout << a+1 << ' ' << b+1 << ' ';
        if(c == -1)
            cout << "X\n";
        else if(c == -2)
            cout << "Y\n";
        else
            cout << c << '\n';
    }
    cout << 1 << ' ' << encode(0, 1)+1 << '\n';
}
