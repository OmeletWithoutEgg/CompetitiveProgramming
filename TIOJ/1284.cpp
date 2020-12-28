#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <algorithm>
#include <utility>
#include <cstdio>

using namespace std;
using ll = long long;
using ld = double;
using pii = pair<int,int>;
const int N = 100025;
const ll INF = 1e18;

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

ll ori(pii a, pii b, pii c) {
    return 1LL * (a.second - b.second) * (c.first - a.first) - 1LL * (a.second - c.second) * (b.first - a.first);
}
ld calc(pii L, ld x) {
    return L.first * x + L.second;
}
ld intersect(pii a, pii b) {
    return (a.second - b.second) / ld(b.first - a.first);
}
pii car[N];
pii lo[N], up[N];
int uit, lit;
signed main() {
    int n = nextint();
    for(int i = 0; i < n; i++) {
        car[i].first = nextint();
        car[i].second = nextint();
    }
    sort(car, car+n);
    for(int i = 0; i < n; i++) {
        while(uit >= 2 && ori(up[uit-2], up[uit-1], car[i]) >= 0) --uit;
        up[uit++] = car[i];
    }
    for(int i = n-1; i >= 0; i--) {
        while(lit >= 2 && ori(lo[lit-2], lo[lit-1], car[i]) >= 0) --lit;
        lo[lit++] = car[i];
    }
    int mx = -1e9, mn = 1e9;
    for(int i = 0; i < n; i++) mx = max(mx, car[i].second), mn = min(mn, car[i].second);
    ld ans = mx - mn;
    int i = 0, j = 0;
    while(i+1 < lit || j+1 < uit) {
        ld xi = i+1 < lit ? intersect(lo[i], lo[i+1]) : INF;
        ld xj = j+1 < uit ? intersect(up[j], up[j+1]) : INF;
        if(xi < xj) {
            if(xi >= 0) ans = min(ans, calc(up[j], xi) - calc(lo[i], xi));
            i++;
        } else {
            if(xj >= 0) ans = min(ans, calc(up[j], xj) - calc(lo[i], xj));
            j++;
        }
    }
    printf("%.2lf\n", ans);
}
