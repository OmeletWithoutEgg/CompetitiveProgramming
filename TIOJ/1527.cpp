#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;
using ld = double;
const int maxn = 1005;

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
inline double nextdouble() {
    double x = 0, p = 1;
    int c = readchar(), neg = false;
    while (c < '0' && c != '-') c = readchar();
    if (c == '-') neg = true, c = readchar();
    while (c >= '0') x = x*10 + (c^'0'), c = readchar();
    if (c != '.')
        return neg ? -x : x;
    c = readchar();
    while (c >= '0') x = x*10 + (c^'0'), p *= 10, c = readchar();
    x /= p;
    return neg ? -x : x;
}
ld a[maxn][maxn];
ld sum[maxn][maxn];
ld ans[maxn][maxn];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int m, n;
    ld k, k2;
    n = nextint(), m = nextint();
    k = nextdouble();
    ld invk = 1.0 / k;
    ld invk2 = invk / k;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            a[i][j] = nextdouble();

    // i < x, j < y
    for (int i = 0; i <= n+1; i++)
        for (int j = 0; j <= m+1; j++)
            sum[i][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            sum[i][j] = (sum[i-1][j] + sum[i][j-1]) * invk - sum[i-1][j-1] * invk2 + a[i-1][j-1] * invk2;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans[i][j] += sum[i][j];

    // i >= x, j < y
    for (int i = 0; i <= n+1; i++)
        for (int j = 0; j <= m+1; j++)
            sum[i][j] = 0;
    for (int i = n; i >= 1; i--)
        for (int j = 1; j <= m; j++)
            sum[i][j] = (sum[i+1][j] + sum[i][j-1]) * invk - sum[i+1][j-1] * invk2 + a[i][j-1] * invk;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans[i][j] += sum[i][j];

    // i < x, j >= y
    for (int i = 0; i <= n+1; i++)
        for (int j = 0; j <= m+1; j++)
            sum[i][j] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= 1; j--)
            sum[i][j] = (sum[i-1][j] + sum[i][j+1]) * invk - sum[i-1][j+1] * invk2 + a[i-1][j] * invk;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans[i][j] += sum[i][j];
    // i >= x, j >= y
    for (int i = 0; i <= n+1; i++)
        for (int j = 0; j <= m+1; j++)
            sum[i][j] = 0;
    for (int i = n; i >= 1; i--)
        for (int j = m; j >= 1; j--)
            sum[i][j] = (sum[i+1][j] + sum[i][j+1]) * invk - sum[i+1][j+1] * invk2 + a[i][j];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            ans[i][j] += sum[i][j];

    ld best = -1e18;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            best = max(best, ans[i][j]);
    cout << fixed << setprecision(3);
    cout << best << '\n';
}
