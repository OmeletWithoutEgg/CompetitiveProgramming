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
    T operator()() const { return v; }
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
constexpr ll N = 225, INF = 1e18, MOD = 10007, K = 14699, inf = 1e9;
using Mint = Modular<int, MOD>;
Mint modpow(Mint e, uint64_t p) { Mint r = 1; while(p) (p&1) && (r *= e), e *= e, p >>= 1; return r; } // 0^0 = 1

namespace linear_recurrence {
    template <typename T> vector<T> BerlekampMassey(vector<T> a) {
        auto scalarProduct = [](vector<T> v, T c) {
            for (T &x: v) x *= c;
            return v;
        };
        vector<T> s, best;
        int bestPos = 0;
        for (size_t i = 0; i < a.size(); i++) {
            T error = a[i];
            for (size_t j = 0; j < s.size(); j++) error -= s[j] * a[i-1-j];
            if (error == 0) continue;
            if (s.empty()) {
                s.resize(i + 1);
                bestPos = i;
                best.push_back(1 / error);
                continue;
            }
            vector<T> fix = scalarProduct(best, error);
            fix.insert(fix.begin(), i - bestPos - 1, 0);
            if (fix.size() >= s.size()) {
                best = scalarProduct(s, -1 / error);
                best.insert(best.begin(), 1 / error);
                bestPos = i;
                s.resize(fix.size());
            }
            for (size_t j = 0; j < fix.size(); j++)
                s[j] += fix[j];
        }
        return s;
    }
    template <typename T> T deduce(vector<T> a, int n) {
        vector<T> s = BerlekampMassey(a);
        if (s.empty()) return 0;
        debug(s);
        // a[i] = \sum s[j] * a[i-j-1]
        vector<T> r = {1}; // 1
        vector<T> e = {0, 1}; // x;
        auto mul = [&s](vector<T> a, vector<T> b) {
            // return a * b % (x^m - s)
            vector<T> c(a.size() + b.size() - 1);
            for (size_t i = 0; i < a.size(); i++)
                for (size_t j = 0; j < b.size(); j++)
                    c[i+j] += a[i] * b[j];
            for (size_t i = c.size()-1; i >= s.size(); i--)
                for (size_t j = 0; j < s.size(); j++)
                    c[i-j-1] += c[i] * s[j];
            c.resize(s.size());
            return c;
        };
        while (n) {
            if (n & 1)
                r = mul(r, e);
            e = mul(e, e);
            n >>= 1;
        }
        T sum = 0;
        for (size_t j = 0; j < s.size() && j < r.size(); j++) sum += r[j] * a[j];
        return sum;
    }
}
Mint dp[N][N][N * 6 + 10];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    int n;
    cin >> s >> n;
    int m = s.size();
    dp[0][m][0] = 1;

    const int len = m * 3 + 2;
    vector<Mint> ans(len * 2 + 5);
    for (int l = 0; l < m; l++) {
        for (int r = m; r >= l; r--) {
            for (int k = 0; k < len * 2; k++) {
                if (l == r) {
                    ans[k] += dp[l][r][k];
                    ans[k+1] += dp[l][r][k] * 26;
                    dp[l][r][k+2] += dp[l][r][k] * 26;
                } else if (l+1 == r) {
                    ans[k] += dp[l][r][k];
                    dp[l][r-1][k+1] += dp[l][r][k];
                    dp[l][r][k+2] += dp[l][r][k] * 25;
                } else if (s[l] == s[r-1]) {
                    dp[l+1][r-1][k] += dp[l][r][k];
                    dp[l][r][k+2] += dp[l][r][k] * 25;
                } else {
                    dp[l+1][r][k+1] += dp[l][r][k];
                    dp[l][r-1][k+1] += dp[l][r][k];
                    dp[l][r][k+2] += dp[l][r][k] * 24;
                }
            }
        }
    }
    ans.resize(len * 2);
    cout << linear_recurrence::deduce(ans, n) << '\n';
}
