#include <bits/stdc++.h>
#define all(v) begin(v),end(v)

using namespace std;
using ll = int64_t;

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

const int mod = 1000000007;
using Mint = Modular<int, mod>;

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

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n;
    vector<Mint> b(n);
    for (int i = 0; i < n; i++) cin >> b[i];
    cin >> m;
    vector<tuple<int,int,int>> A(m);
    for (auto &[a, b, c]: A) cin >> a >> b >> c;

    auto mulA = [&A, n](vector<Mint> & v) {
        vector<Mint> res = v;
        for (auto [a, b, c]: A) if (a != b) res[b] += v[a] * c;
        v = res;
    };

    vector<Mint> s; // SLR of A

    {
        vector<Mint> u(n);
        for (Mint &x: u) x = rand();
        vector<Mint> a(n * 5);
        auto cur = b;
        for (int i = 0; i < n * 5; i++) {
            a[i] = inner_product(all(cur), u.begin(), Mint(0));
            mulA(cur);
        }
        s = BerlekampMassey(a);
    }

    assert( s.size() <= n && s.size() >= 0 );

    int q;
    cin >> q;
    while (q--) {
        ll k;
        cin >> k;
        vector<Mint> r = {1}; // 1
        vector<Mint> e = {0, 1}; // x;
        auto mul = [&s](vector<Mint> a, vector<Mint> b) {
            // return a * b % (x^m - s)
            vector<Mint> c(a.size() + b.size() - 1);
            for (size_t i = 0; i < a.size(); i++)
                for (size_t j = 0; j < b.size(); j++)
                    c[i+j] += a[i] * b[j];
            for (size_t i = c.size()-1; i >= s.size(); i--)
                for (size_t j = 0; j < s.size(); j++)
                    c[i-j-1] += c[i] * s[j];
            c.resize(s.size());
            return c;
        };
        while (k) {
            if (k & 1)
                r = mul(r, e);
            e = mul(e, e);
            k >>= 1;
        }
        vector<Mint> ans(n);
        auto cur = b;
        for (size_t i = 0; i < r.size(); i++) {
            for (size_t j = 0; j < n; j++)
                ans[j] += r[i] * cur[j];
            mulA(cur);
        }
        for (int i = 0; i < n; i++)
            cout << ans[i] << (i+1==n ? '\n' : ' ');
    }
}
