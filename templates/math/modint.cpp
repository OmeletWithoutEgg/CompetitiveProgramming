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
