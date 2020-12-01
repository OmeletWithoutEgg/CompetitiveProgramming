#include <cstdio>

#define int long long
inline char readchar() {
    constexpr int B = 65536;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar(), f = false;
    while(c < '0' && c != '-') c = readchar();
    if(c == '-') f = true, c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return f ? -x : x;
}
const int N = 1025;
int w[N];
long long dp[N];
inline long long abs(long long a){return a>0 ? a : -a;}
inline long long min(long long a, long long b){return a>b ? b : a;}
signed main(){
    int t = nextint();
    while(t--) {
        int n = nextint();
        for(int i = 0; i < n; i++) w[i] = nextint();
        dp[0] = 0;
        dp[1] = abs(w[1]-w[0]);
        for(int i = 2; i < n; i++)
            dp[i] = min(dp[i-1] + abs(w[i]-w[i-1]), dp[i-2] + abs(w[i]-w[i-2]));
        printf("%lld\n", dp[n-1]);
    }
}

