#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

namespace fft {
    const int maxn = 1 << 15;
    const int magic = 128;

    typedef double ftype;
    typedef complex<ftype> point;

    point w[maxn];
    const ftype pi = acos(-1);
    bool initiated = 0;
    void init() {
        if(!initiated) {
            for(int i = 1; i < maxn; i *= 2) {
                for(int j = 0; j < i; j++) {
                    w[i + j] = polar<ftype>(1, pi * j / i);
                }
            }
            initiated = 1;
        }
    }
    template<typename T>
        void fft(T *in, point *out, int n) {
            for (int i = 0, j = 0; i < n; i++) {
                out[i] = in[j];
                for (int s = n>>1; (j^=s) < s; s>>=1);
            }
            for (int s = 1; s < n; s *= 2) {
                for (int i = 0; i < n; i += s * 2) {
                    for (int j = 0; j < s; j++) {
                        point b = out[i+j+s] * w[s+j];
                        out[i+j+s] = out[i+j] - b;
                        out[i+j] += b;
                    }
                }
            }
        }

    template<typename T>
        void mul_slow(vector<T> &a, const vector<T> &b) {
            vector<T> res(a.size() + b.size() - 1);
            for(size_t i = 0; i < a.size(); i++) {
                for(size_t j = 0; j < b.size(); j++) {
                    res[i + j] += a[i] * b[j];
                }
            }
            a = res;
        }


    template<typename T>
        void mul(vector<T> &a, const vector<T> &b) {
            if(min(a.size(), b.size()) < magic) {
                mul_slow(a, b);
                return;
            }
            init();
            static const int shift = 15, mask = (1 << shift) - 1;
            size_t n = a.size() + b.size() - 1;
            while(__builtin_popcount(n) != 1) {
                n++;
            }
            a.resize(n);
            static point A[maxn], B[maxn];
            static point C[maxn], D[maxn];
            for(size_t i = 0; i < n; i++) {
                int64_t ai = static_cast<int64_t>(a[i]);
                int64_t bi = static_cast<int64_t>(i < b.size() ? b[i] : 0);
                A[i] = point(ai & mask, ai >> shift);
                B[i] = point(bi & mask, bi >> shift);
            }
            fft(A, C, n); fft(B, D, n);
            for(size_t i = 0; i < n; i++) {
                size_t j = i ? n - i : 0;
                point c0 = C[i] + conj(C[j]);
                point c1 = C[i] - conj(C[j]);
                point d0 = D[i] + conj(D[j]);
                point d1 = D[i] - conj(D[j]);
                A[i] = c0 * d0 - point(0, 1) * c1 * d1;
                B[i] = c0 * d1 + d0 * c1;
            }
            fft(A, C, n); fft(B, D, n);
            reverse(C + 1, C + n);
            reverse(D + 1, D + n);
            ftype t = ftype(1) / (4 * n);
            for(size_t i = 0; i < n; i++) {
                T A0 = llround(real(C[i]) * t);
                T A1 = llround(imag(D[i]) * t);
                T A2 = llround(imag(C[i]) * t);
                a[i] = A0 + A1 * (1LL << shift) + A2 * (1LL << 2 * shift);
            }
            return;
        }
}

const int MOD = 1000000007;
// Montegomery multiplication
class Mint {
    using T = int_fast32_t;
public:
    constexpr Mint() : v() {}
    template <typename U> Mint(const U &u) { v = mont.from(0 <= u && u < MOD ? u : (u%MOD+MOD)%MOD); }
    template <typename U> explicit operator U() const { return U(mont.get(v)); }
    T operator()() const { return mont.get(v); }
#define REFOP(type, expr...) Mint &operator type (const Mint &rhs) { return expr, *this; }
    REFOP(+=, v += rhs.v - MOD, v += MOD & (v >> width)) 
    REFOP(-=, v -= rhs.v, v += MOD & (v >> width))
    // fits for MOD^2 <= 9e18
    REFOP(*=, v = mont.redc(v, rhs.v))
    REFOP(/=, *this *= inverse(mont.get(rhs.v)))
#define VALOP(op) friend Mint operator op (Mint a, const Mint &b) { return a op##= b; }
    VALOP(+) 
    VALOP(-) 
    VALOP(*)
    VALOP(/)
    Mint operator-() const { return 0 - *this; }
    friend bool operator == (const Mint &lhs, const Mint &rhs) { return lhs.v == rhs.v; }
    friend bool operator != (const Mint &lhs, const Mint &rhs) { return lhs.v != rhs.v; }
    friend std::istream & operator>>(std::istream &I, Mint &m) { T x; I >> x, m = mont.from(x); return I; }
    friend std::ostream & operator<<(std::ostream &O, const Mint &m) { return O << mont.get(m.v); }
private:
    constexpr static int width = sizeof(T) * 8 - 1;
    // constexpr static int MOD = mod;
    T v;
    // Montegomery multiplication
    struct Mont {
        using ll = int_fast64_t;
        int R1Mod, R2Mod, NPrime;
        Mont() {
            const ll B = (1LL << 32);
            assert((MOD & 1) != 0);
            ll R = B % MOD;
            ll xinv = 1, bit = 2;
            for (int i = 1; i < 32; i++, bit <<= 1) { // Hensel lifting!
                ll y = xinv * MOD;
                if ((y & bit) != 0)
                    xinv |= bit;
            }
            assert(((MOD * xinv) & (B-1)) == 1);
            R1Mod = (int)R;
            R2Mod = (int)(R * R % MOD);
            NPrime = (int)(B - xinv);
        }
        int redc(int a, int b) const {
            ll T = (ll)a * b;
            ll m = (unsigned)T * NPrime;
            T += m * MOD;
            T >>= 32;
            if (T >= MOD)
                T -= MOD;
            return (int)T;
        }
        int from(int x) const { return redc(x, R2Mod); }
        int one() const { return R1Mod; }
        int get(int a) const { return redc(a, 1); }
    };
    static Mont mont;
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
Mint::Mont Mint::mont;

const int inf = 1e9, maxn = 10025;
// using Mint = Modular<int, mod>;

Mint modpow(Mint e, uint64_t p) {
    Mint r = 1;
    while (p) {
        if (p & 1) r = r * e;
        e = e * e;
        p >>= 1;
    }
    return r;
}

vector<Mint> mul(const vector<Mint> &A, const vector<Mint> &B) {
    vector<Mint> C(A.size() + B.size());
    for (size_t i = 0; i < A.size(); i++)
        for (size_t j = 0; j < B.size(); j++)
            C[i+j] += A[i] * B[j];
    return C;
}

vector<Mint> inverse(vector<Mint> F) {
    vector<Mint> P(F.size());
    P[0] = 1 / F[0];
    for (size_t i = 1; i < F.size(); i++) {
        // [x^i] (P * F) == 0
        Mint sum = 0;
        for (size_t j = 0; j < i; j++) {
            sum += P[j] * F[i-j];
        }
        P[i] = -sum * P[0];
    }
    return P;
}
Mint inv[maxn], ifac[maxn], fac[maxn];
vector<Mint> integral(vector<Mint> F) {
    F.insert(F.begin(), 0);
    for (size_t i = 1; i < F.size(); i++)
        F[i] *= inv[i];
    return F;
}
vector<Mint> derivative(vector<Mint> F) {
    for (size_t i = 1; i < F.size(); i++) F[i] *= i;
    F.erase(F.begin());
    return F;
}
vector<Mint> ln(vector<Mint> F) {
    return integral(mul(derivative(F), inverse(F)));
}
signed main() {
    inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = inv[MOD % i] * - (MOD / i);
    ifac[0] = fac[0] = 1;
    for (int i = 1; i < maxn; i++) ifac[i] = ifac[i-1] * inv[i];
    for (int i = 1; i < maxn; i++) fac[i] = fac[i-1] * i;
    ios_base::sync_with_stdio(0), cin.tie(0);
    // F = n^n / n! x^n - (F^2/2! + F^3/3! + ... );
    // exp(F) - 1 = C = \sum n^n / n! x^n
    // F = ln(C + 1)
    int n;
    cin >> n;
    vector<Mint> B(n+1);
    for (int i = 1; i <= n; i++)
        B[i] = modpow(i, i) * ifac[i];
    B[0] = 1;
    auto F = ln(B);
    F.resize(n+1);
    F.erase(F.begin());
    vector<Mint> ans = F;
    cout << ans[n-1] * fac[n] << '\n';
    for (int c = 2; c <= n; c++) {
        fft::mul(ans, F);
        ans.resize(n-c+1);
        F.resize(n-c+1);
        cout << ans[n-c] * fac[n] * ifac[c] << '\n';
    }
}
