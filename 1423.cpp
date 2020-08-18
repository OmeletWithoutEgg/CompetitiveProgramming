#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")

#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int N = 375;
struct Point {
    int x, y;
    friend Point operator-(const Point &p) {
        return {-p.x, -p.y};
    }
    friend Point operator-(const Point &a, const Point &b) {
        return {a.x - b.x, a.y - b.y};
    }
    friend bool operator<(const Point &a, const Point &b) {
        int qa = (a.y == 0 ? (a.x > 0 ? 0 : 2) : (a.y > 0 ? 1 : 3));
        int qb = (b.y == 0 ? (b.x > 0 ? 0 : 2) : (b.y > 0 ? 1 : 3));
        int C = a.x * b.y - a.y * b.x;
        return qa != qb ? qa < qb : C > 0;
    }
    friend bool operator==(const Point &a, const Point &b) { return a.x * b.y == a.y * b.x; }
} p[N], d[N], u[N*2];
int sum[N*2];
int calc(int n) {
    for(int i = 0; i < n; i++) u[i] = d[i];
    for(int i = 0; i < n; i++) u[i+n] = -d[i];
    sort(u,u+n*2);
    int h = unique(u,u+n*2) - u;
    for(int i = 0; i <= h; i++) sum[i] = 0;
    for(int i = 0; i < n; i++) {
        int pos = lower_bound(u, u+h, d[i]) - u + 1;
        sum[pos] += 1;
    }
    for(int i = 1; i <= h; i++) sum[i] += sum[i-1];
    int res = 0;
    for(int i = 0; i < n; i++) {
        int l = lower_bound(u, u+h, d[i]) - u + 1;
        int r = lower_bound(u, u+h, -d[i]) - u + 1;
        if(l > r) swap(l, r);
        int a = sum[r-1] - sum[l], b = (sum[h] - sum[r]) + sum[l-1];
        res += a * b;
    }
    return res;
}
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar(), f = 0;
    while(c < '0' && c != '-') c = readchar();
    if(c == '-') c = readchar(), f = 1;
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return f ? -x : x;
}
signed main() {
    int n = nextint();
    for(int i = 0; i < n; i++)
        p[i].x = nextint(), p[i].y = nextint();
    ll ans = 0;
    for(int i = 0; i < n; i++) {
        int s = 0;
        for(int j = 0; j < n; j++) if(j != i) d[s++] = p[j] - p[i];
        ans += calc(s);
    }
    ans /= 2;
    printf("%lld\n", ans);
}
