#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while('0'>c || c>'9') c = readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    return x;
}

int v[5001];
inline void solve() {
    int n = nextint();
    for(int i = 1; i <= n; i++) v[i] = nextint();
    int ans = 0;
    for(int i = 1; i <= n; i++) {
        int mx = -1, mn = n+1;
        for(int j = i; j <= n; j++) {
            mx = (mx > v[j] ? mx : v[j]);
            mn = (mn < v[j] ? mn : v[j]);
            int MX = v[i] > v[j] ? v[i] : v[j];
            int MN = v[i] < v[j] ? v[i] : v[j];
            if(i!=j && MX-MN == j-i && MX == mx && MN == mn) ++ans;
        }
    }
    printf("%d\n", ans);
}
signed main() {
    int t = nextint();
    while(t--) solve();
}
