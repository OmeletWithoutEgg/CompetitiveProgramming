#include "hexagon.h"

#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\033[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
using namespace std;
using ll = long long;
const int maxn = 100025;
const int mod = 1000000007;

int F[6] = {0, 3, 3, 0, -3, -3};
int G[6] = {0, 1, 2, 3, 4, 5};

struct Point {
    ll u, v;
    Point () : u(), v() {}
    Point (ll a, ll b) : u((a%mod+mod)%mod), v((b%mod+mod)%mod) {}
    friend Point operator+(const Point &a, const Point &b) {
        return { (a.u+b.u)%mod, (a.v+b.v)%mod };
    }
};
Point POLAR(int len, int angle) {
    --angle;
    if (angle == 0)
        return { len, 0 };
    if (angle == 1)
        return { len, len };
    if (angle == 2)
        return { 0, len };
    if (angle == 3)
        return { -len, 0 };
    if (angle == 4)
        return { -len, -len };
    if (angle == 5)
        return {0, -len };
}
ll CROSS(Point a, Point b) {
    return (a.u * b.v % mod - a.v * b.u % mod + mod) % mod;
}
ll modpow(ll a, ll p) {
    ll r = 1;
    while (p) {
        if (p & 1)
            r = r*a%mod;
        a = a*a%mod;
        p >>= 1;
    }
    return r;
}
int draw_territory(int N, int A, int B,
                   vector<int> D, vector<int> L) {

    vector<Point> P(N);
    for (int i = 1; i < N; i++) {
        P[i] = P[i-1] + POLAR(L[i], D[i]);
    }
    // double area = 0;
    // double hexa = sqrt(3) / 2;
    ll area = 0;
    for (int i = 0; i < N; i++) {
        int j = (i+1)%N;
        area += CROSS(P[i], P[j]) * 3LL;
        area += (L[i] - 1) * 3LL; // hexa / 2.0
        int angle = (D[j] - D[i] + 6 + 3) % 6;
        area += angle; // hexa / 6.0
        area %= mod;
    }
    area = area * modpow(6, mod-2) % mod;
    return A * area % mod;
}
