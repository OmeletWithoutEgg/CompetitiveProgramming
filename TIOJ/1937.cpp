#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <immintrin.h>
#include <iostream>
#include <cstring>
using namespace std;

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

struct FastOut {
    constexpr static int B = 1 << 20;
    static char buf[B];
    int q;
    inline void writeint(unsigned int x, char c) {
        static char stk[20];
        char p = 0;
        if(!x) stk[p++] = '0';
        while(x) stk[p++] = x%10^'0', x/=10;
        while(p) buf[q++] = stk[--p];
        buf[q++] = c;
        if(q + 20 >= B) fwrite(buf, 1, q, stdout), q = 0;
    }
    ~FastOut() {
        fwrite(buf, 1, q, stdout);
    }
} ouf;
char FastOut::buf[B];

using m256 = __m256i;
struct alignas(32) mmint {
    m256 x;

    mmint() {}
    inline mmint(const m256& _x) : x(_x) {}
    inline operator m256&() { return x; }
    inline operator const m256&() const { return x; }
    inline int& operator[](int i) { return *(reinterpret_cast<int*>(&x) + i); }
    inline const int& operator[](int i) const {
        return *(reinterpret_cast<const int*>(&x) + i);
    }

    friend inline mmint operator+(const mmint& A, const mmint& B) {
        const m256 apb = _mm256_add_epi32(A, B);
        return apb;
    }

    friend inline mmint operator-(const mmint& A, const mmint& B) {
        const m256 ret = _mm256_sub_epi32(A, B);
        return ret;
    }

    inline mmint& operator+=(const mmint& A) { return (*this) = (*this) + A; }
    inline mmint& operator-=(const mmint& A) { return (*this) = (*this) - A; }

};

// #include "math-fast/mat-prod-strassen.hpp"

// B*Bの正方行列を高速に乗算するライブラリ。
// B*B行列a,bを タテB行 ヨコB/8行の行列と見なす.
// s : 正順に配置。すなわちa_{i,k}をs[i * (B / 8) + k]に配置する。
// t : 逆順に配置。すなわちb_{k,j}をt[j * B + k]に配置する。
// u : 正順に配置。すなわちc_{i,j}をu[i * (B / 8) + j]に配置する。
namespace fast_mat_prod_impl {
constexpr int B = 1 << 7;
constexpr int B8 = B / 8;

void mul_simd(mmint* __restrict__ s, mmint* __restrict__ t,
        mmint* __restrict__ u) {
#define INIT_X(x) \
    m256 prod##x = _mm256_setzero_si256();

#define INIT_Y(j, k, l) \
    m256 T = t[j * B + k + l];

#define PROD(x)                                              \
    const m256 S##x = _mm256_set1_epi32(s[(i + x) * B8 + k / 8][l]); \
    const m256 ST##x = _mm256_mullo_epi32(S##x, T);      \
    prod##x = _mm256_add_epi32(prod##x, ST##x);

#define REDUCE(x) \
    u[(i + x) * B8 + j] = prod##x;

    for (int i = 0; i < B; i += 8) {
        for (int j = 0; j < B8; j += 1) {
            INIT_X(0);
            INIT_X(1);
            INIT_X(2);
            INIT_X(3);
            INIT_X(4);
            INIT_X(5);
            INIT_X(6);
            INIT_X(7);
            for (int k = 0; k < B; k += 8) {
                for (int l = 0; l < 8; l++) {
                    INIT_Y(j, k, l);
                    PROD(0);
                    PROD(1);
                    PROD(2);
                    PROD(3);
                    PROD(4);
                    PROD(5);
                    PROD(6);
                    PROD(7);
                }
            }
            REDUCE(0);
            REDUCE(1);
            REDUCE(2);
            REDUCE(3);
            REDUCE(4);
            REDUCE(5);
            REDUCE(6);
            REDUCE(7);
        }
    }
}

#undef INIT
#undef PROD
#undef REDUCE

void strassen(int N, mmint* __restrict__ s, mmint* __restrict__ t,
        mmint* __restrict__ u) {
    for (int i = 0; i < N * N / 8; i++) u[i] = _mm256_setzero_si256();

    if (N == B) {
        mul_simd(s, t, u);
        return;
    }

    mmint* ps = s + N * N / 8;
    mmint* pt = t + N * N / 8;
    mmint* pu = u + N * N / 8;
    int nx = N * N / 32;
    int o11 = nx * 0, o12 = nx * 1, o21 = nx * 2, o22 = nx * 3;

    // P1
    for (int i = 0; i < nx; i++) ps[i] = s[o11 + i] + s[o22 + i];
    for (int i = 0; i < nx; i++) pt[i] = t[o11 + i] + t[o22 + i];
    strassen(N / 2, ps, pt, pu);
    for (int i = 0; i < nx; i++) u[o11 + i] = pu[i], u[o22 + i] = pu[i];

    // P2
    for (int i = 0; i < nx; i++) ps[i] = s[o21 + i] + s[o22 + i];
    for (int i = 0; i < nx; i++) pt[i] = t[o11 + i];
    strassen(N / 2, ps, pt, pu);
    for (int i = 0; i < nx; i++) u[o21 + i] = pu[i], u[o22 + i] -= pu[i];

    // P3
    for (int i = 0; i < nx; i++) ps[i] = s[o11 + i];
    for (int i = 0; i < nx; i++) pt[i] = t[o12 + i] - t[o22 + i];
    strassen(N / 2, ps, pt, pu);
    for (int i = 0; i < nx; i++) u[o12 + i] = pu[i], u[o22 + i] += pu[i];

    // P4
    for (int i = 0; i < nx; i++) ps[i] = s[o22 + i];
    for (int i = 0; i < nx; i++) pt[i] = t[o21 + i] - t[o11 + i];
    strassen(N / 2, ps, pt, pu);
    for (int i = 0; i < nx; i++) u[o11 + i] += pu[i], u[o21 + i] += pu[i];

    // P5
    for (int i = 0; i < nx; i++) ps[i] = s[o11 + i] + s[o12 + i];
    for (int i = 0; i < nx; i++) pt[i] = t[o22 + i];
    strassen(N / 2, ps, pt, pu);
    for (int i = 0; i < nx; i++) u[o11 + i] -= pu[i], u[o12 + i] += pu[i];

    // P6
    for (int i = 0; i < nx; i++) ps[i] = s[o21 + i] - s[o11 + i];
    for (int i = 0; i < nx; i++) pt[i] = t[o11 + i] + t[o12 + i];
    strassen(N / 2, ps, pt, pu);
    for (int i = 0; i < nx; i++) u[o22 + i] += pu[i];

    // P7
    for (int i = 0; i < nx; i++) ps[i] = s[o12 + i] - s[o22 + i];
    for (int i = 0; i < nx; i++) pt[i] = t[o21 + i] + t[o22 + i];
    strassen(N / 2, ps, pt, pu);
    for (int i = 0; i < nx; i++) u[o11 + i] += pu[i];
}

int S;
int S8;
void set_S(int _S) {
    S = _S;
    S8 = S / 8;
}
constexpr int max_S = 2048;
constexpr int max_S8 = max_S / 8;
mmint s[max_S * max_S8 * 4 / 3 + 25], t[max_S * max_S8 * 4 / 3 + 25], u[max_S * max_S8 * 4 / 3 + 25];

void place_s(int N, int a, int b, mmint* __restrict__ dst,
        mmint* __restrict__ src) {
    if (N == B) {
        for (int i = 0; i < B; i++) {
            memcpy(dst + i * B8, src + (a + i) * S8 + b / 8, B8 * sizeof(mmint));
        }
        return;
    }
    int nx = N * N / 32, M = N / 2;
    place_s(M, a + 0, b + 0, dst + nx * 0, src);
    place_s(M, a + 0, b + M, dst + nx * 1, src);
    place_s(M, a + M, b + 0, dst + nx * 2, src);
    place_s(M, a + M, b + M, dst + nx * 3, src);
}

void place_t(int N, int a, int b, mmint* __restrict__ dst,
        mmint* __restrict__ src) {
    if (N == B) {
        // t : 逆順に配置。すなわちb_{k,j}をt[j * B + k]に配置する。
        for (int k = 0; k < B; k++) {
            for (int j = 0; j < B8; j++) {
                dst[j * B + k] = src[(a + k) * S8 + j + b / 8];
            }
        }
        return;
    }
    int nx = N * N / 32, M = N / 2;
    place_t(M, a + 0, b + 0, dst + nx * 0, src);
    place_t(M, a + 0, b + M, dst + nx * 1, src);
    place_t(M, a + M, b + 0, dst + nx * 2, src);
    place_t(M, a + M, b + M, dst + nx * 3, src);
}

void place_rev(int N, int a, int b, mmint* __restrict__ dst,
        mmint* __restrict__ src) {
    if (N == B) {
        for (int i = 0; i < B; i++) {
            memcpy(src + (a + i) * S8 + b / 8, dst + i * B8, B8 * sizeof(mmint));
        }
        return;
    }
    int nx = N * N / 32, M = N / 2;
    place_rev(M, a + 0, b + 0, dst + nx * 0, src);
    place_rev(M, a + 0, b + M, dst + nx * 1, src);
    place_rev(M, a + M, b + 0, dst + nx * 2, src);
    place_rev(M, a + M, b + M, dst + nx * 3, src);
}

void prod(unsigned int* __restrict__ a, unsigned int* __restrict__ b,
        unsigned int* __restrict__ c) {
    place_s(S, 0, 0, s, reinterpret_cast<mmint*>(a));
    place_t(S, 0, 0, t, reinterpret_cast<mmint*>(b));
    // for (int i = 0; i < S * S8; i++) s[i] = mmint::itom(s[i]);
    // for (int i = 0; i < S * S8; i++) t[i] = mmint::itom(t[i]);
    strassen(S, s, t, u);
    // for (int i = 0; i < S * S8; i++) u[i] = mmint::mtoi(u[i]);
    place_rev(S, 0, 0, u, reinterpret_cast<mmint*>(c));
}

}  // namespace fast_mat_prod_impl

// end of #include "math-fast/mat-prod-strassen.hpp"

int main() {
    unsigned int* a = reinterpret_cast<unsigned int*>(fast_mat_prod_impl::t);
    unsigned int* b = reinterpret_cast<unsigned int*>(fast_mat_prod_impl::u);
    unsigned int* c = reinterpret_cast<unsigned int*>(fast_mat_prod_impl::s);

    unsigned int n, x;
    n = nextint();
    if (n == 1) {
        unsigned int y;
        x = nextint();
        y = nextint();
        ouf.writeint(x * y, '\n');
        return 0;
    }

    const int S = max(fast_mat_prod_impl::B, 1<<(__lg(n-1) + 1));
    // cerr << "S = " << S << endl;
    // cerr << "n = " << n << endl;
    fast_mat_prod_impl::set_S(S);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            x = nextint();
            a[i * S + j] = x;
        }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            x = nextint();
            b[i * S + j] = x;
        }
    fast_mat_prod_impl::prod(a, b, c);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            x = c[i * S + j];
            // cerr << "x = " << x << endl;
            ouf.writeint(x, (j+1==n ? '\n' : ' '));
        }
}
