// https://gist.github.com/simonlindholm/51f88e9626408723cf906c6debd3814b
// Barret reduction
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull reduce(ull a) {
        ull q = (ull)((L(m) * a) >> 64), r = a - q * b;
        return r >= b ? r - b : r;
    }
};

// Montegomery multiplication
class Mint {
    using T = int;
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
#define VALOP(op) friend Mint operator op (Mint a, const Mint &b) { return a op##= b; }
    VALOP(+) 
    VALOP(-) 
    VALOP(*)
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
        int Mod, R1Mod, R2Mod, NPrime;
        Mont(int mod) : Mod(mod) {
            const ll B = (1LL << 32);
            assert((mod & 1) != 0);
            ll R = B % mod;
            ll xinv = 1, bit = 2;
            for (int i = 1; i < 32; i++, bit <<= 1) { // Hensel lifting!
                ll y = xinv * mod;
                if ((y & bit) != 0)
                    xinv |= bit;
            }
            assert(((mod * xinv) & (B-1)) == 1);
            R1Mod = (int)R;
            R2Mod = (int)(R * R % mod);
            NPrime = (int)(B - xinv);
        }
        int redc(int a, int b) {
            ll T = (ll)a * b;
            ll m = (unsigned)T * NPrime;
            T += m * Mod;
            T >>= 32;
            if (T >= Mod)
                T -= Mod;
            return (int)T;
        }
        int from(int x) { assert (x < Mod); return redc(x, R2Mod); }
        int one() { return R1Mod; }
        int get(int a) { return redc(a, 1); }
        int mul(int a, int b) { return redc(a, b); }
    };
    static Mont mont;
};
Mint::Mont Mint::mont(MOD);
