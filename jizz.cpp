#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#ifdef local
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
#define safe ((void)0)
#define debug(...) ((void)0)
#endif // local

#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 155, mod = 998244353, sigma = 6;

constexpr struct FastMod {
    using ull = uint64_t;
    using uL = __uint128_t;
    ull b, m;
    constexpr FastMod(ull b) : b(b), m(ull((uL(1) << 64) / b)) {}
    constexpr ull reduce(ull a) const {
        ull q = (ull)((uL(m) * a) >> 64), r = a - q * b;
        return r >= b ? r - b : r;
    }
} fm(mod);

template <typename T, T MOD> class Modular {
public:
    constexpr Modular() : v() {}
    template <typename U> Modular(const U &u) { v = (0 <= u && u < MOD ? u : (u%MOD+MOD)%MOD); }
    template <typename U> explicit operator U() const { return U(v); }
    T operator()() const { return v; }
#define REFOP(type, expr...) Modular &operator type (const Modular &rhs) { return expr, *this; }
    REFOP(+=, v += rhs.v - MOD, v += MOD & (v >> width)) ; REFOP(-=, v -= rhs.v, v += MOD & (v >> width))
    // fits for MOD^2 <= 9e18
    REFOP(*=, v = fm.reduce(1LL * v * rhs.v)) ; REFOP(/=, *this *= inverse(rhs.v))
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

using Mint = Modular<int, mod>;
Mint modpow(Mint e, uint64_t p) { Mint r = 1; while(p) (p&1) && (r *= e), e *= e, p >>= 1; return r; } // 0^0 = 1

vector<Mint> BerlekampMassey(vector<Mint> x) {
    vector<Mint> cur, ls;
    int lf = 0;
    Mint ld = 0;
    for (int i = 0; i < (int)x.size(); ++i) {
        Mint t = 0;
        for (int j = 0; j < (int)cur.size(); ++j)
            t += cur[j] * x[i - j - 1];
        if (t == x[i]) continue;
        if (cur.empty()) {
            cur.resize(i + 1);
            lf = i, ld = t - x[i];
            continue;
        }
        Mint k = (t - x[i]) / ld;
        vector<Mint> c(i - lf - 1);
        c.push_back(k);
        for (int j = 0; j < (int)ls.size(); ++j)
            c.push_back(- k * ls[j]);
        if (c.size() < cur.size()) c.resize(cur.size());
        for (int j = 0; j < (int)cur.size(); ++j)
            c[j] += cur[j];
        if (i - lf + (int)ls.size() >= (int)cur.size()) {
            ls = cur, lf = i;
            ld = t - x[i];
        }
        cur = c;
    }
    return cur;
    // x[i] = \sum x[i-1-j] * cur[j] for j in len(cur)
}
vector<Mint> sparseLinearEquation(vector<vector<pair<int,Mint>>> A, vector<Mint> b) {
    int n = b.size();
    vector<Mint> u(n);
    for (int i = 0; i < n; i++) u[i] = rand();

    auto mulA = [&A, &n](vector<Mint> &v) {
        vector<Mint> res(n);
        for (int i = 0; i < n; i++)
            for (auto [j, c]: A[i])
                res[i] += v[j] * c;
        v = res;
    };
    vector<Mint> a(n * 2 + 1), cur = b;
    for (int i = 0; i <= n * 2; i++) {
        a[i] = inner_product(u.begin(), u.end(), cur.begin(), Mint(0));
        mulA(cur);
    }
    auto r = BerlekampMassey(a);
    int m = r.size();
    // debug(r, a);
    // A^m = A^{m-1} * r[0] + A^{m-2} * r[1] + ... + A^0 * r[m-1]
    // A^{-1}b = (A^{m-1}b - A^{m-2}b * r[0] - A^{m-3}b * r[1] - ... - A^0b * r[m-2])
    cur = b;
    vector<Mint> res(n);
    for (int i = 0; i < m-1; i++) {
        for (int j = 0; j < n; j++) res[j] -= cur[j] * r[m-2-i];
        mulA(cur);
    }
    for (int j = 0; j < n; j++) res[j] += cur[j];
    Mint inv = 1 / r[m-1];
    for (int j = 0; j < n; j++) res[j] *= inv;
    return res;
}
struct AhoCorasick {
    int ch[maxn][sigma], fail[maxn];
    int tot;
    bool isEnd[maxn];
    void insert(const string &s) {
        int now = 0;
        for (char c: s) {
            c -= '1';
            if (!ch[now][c])
                ch[now][c] = ++tot;
            now = ch[now][c];
        }
        isEnd[now] = true;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < sigma; i++)
            if (ch[0][i])
                q.push(ch[0][i]);
        while (!q.empty()) {
            int i = q.front(); q.pop();
            int f = fail[i];
            isEnd[i] |= isEnd[f];
            for (int c = 0; c < sigma; c++) {
                if (ch[i][c]) {
                    fail[ ch[i][c] ] = ch[f][c];
                    q.push(ch[i][c]);
                } else {
                    ch[i][c] = ch[f][c];
                }
            }
        }
    }
    void solve() {
        vector<vector<pair<int,Mint>>> A(tot+1);
        vector<Mint> B(tot+1);
        Mint inv = 1 / Mint(sigma);
        for (int i = 0; i <= tot; i++) {
            A[i].emplace_back(i, 1);
            for (int c = 0; c < sigma; c++)
                if (int j = ch[i][c]; !isEnd[j])
                    A[i].emplace_back(j, -inv);
        }
        for (int i = 0; i <= tot; i++) if (!isEnd[i]) B[i] = 1;
        cout << sparseLinearEquation(A, B)[0] << '\n';
    }
} AC;
signed main() {
    // debug(BerlekampMassey({ 1, 1, 3, 7, 17 }));
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    while (n--) {
        string s;
        cin >> s;
        AC.insert(s);
    }
    AC.build();
    AC.solve();
}
