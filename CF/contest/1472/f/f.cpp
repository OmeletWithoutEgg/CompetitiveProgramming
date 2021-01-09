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
    constexpr static int width = sizeof(T) * 8 - 1;
    REFOP(+=, v += rhs.v - MOD, v += MOD & (v >> width)) ; REFOP(-=, v -= rhs.v, v += MOD & (v >> width))
    // fits for MOD^2 <= 9e18
    REFOP(*=, v = 1LL * v * rhs.v % MOD) ; REFOP(/=, *this *= inverse(rhs.v))
#define VALOP(op) friend Modular operator op (Modular a, const Modular &b) { return a op##= b; }
    VALOP(+) ; VALOP(-) ; VALOP(*) ; VALOP(/)
    Modular operator-() const { return 0 - *this; }
    friend bool operator == (const Modular &lhs, const Modular &rhs) { return lhs.v == rhs.v; }
    friend bool operator != (const Modular &lhs, const Modular &rhs) { return lhs.v != rhs.v; }
    friend std::istream & operator>>(std::istream &I, Modular &m) { T x; I >> x, m = Modular(x); return I; }
    friend std::ostream & operator<<(std::ostream &O, const Modular &m) { return O << m.v; }
    friend Modular power(Modular e, uint64_t p) { // 0^0 = 1
        Modular r = 1;
        while(p) (p&1) && (r *= e), e *= e, p >>= 1;
        return r;
    }
private:
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
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
// constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 500025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
using Mint = Modular<int, MOD>;

using Matrix = array<array<int,4>,4>;
Matrix mul(Matrix A, Matrix B) {
    Matrix C = {};
    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) for(int k = 0; k < 4; k++) C[i][j] |= A[i][k] && B[k][j];
    return C;
}
array<int,4> mul(array<int,4> v, Matrix A) {
    array<int,4> r = {};
    for(int i = 0; i < 4; i++) for(int j = 0; j < 4; j++) r[i] |= A[i][j] && v[j];
    return r;
}
Matrix power(Matrix e, uint64_t p) {
    Matrix r = {};
    for(int i = 0; i < 4; i++) r[i][i] = 1;
    while(p) {
        if(p & 1) r = mul(r, e);
        e = mul(e, e);
        p >>= 1;
    }
    return r;
}
array<array<int,4>,4> G;
void solve() {
    int n, m;
    cin >> n >> m;
    map<int,int> mp;
    for(int i = 0; i < m; i++) {
        int r, c;
        cin >> r >> c;
        --r;
        mp[c] |= 1 << r;
    }
    int last = 0;
    array<int,4> state = {};
    state[0] = state[3] = true;
    debug(state);
    for(auto [pos, m]: mp) {
        state = mul(state, power(G, pos - last));
        debug(state);
        array<int,4> nxt = {};
        for(int i = 0; i < 4; i++)
            if(!(i & m))
                nxt[i | m] = state[i];
        state = nxt;
        last = pos;
    }
    state = mul(state, power(G, n - last));
    debug(state);
    if(state[3])
        cout << "YES\n";
    else
        cout << "NO\n";
}
signed main() {
    G[1][2] = 1;
    G[2][1] = 1;
    G[3][3] = 1;
    G[3][0] = G[0][3] = 1;
    debug(G);
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--)
        solve();
}