#include <cstdio>

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
const int N = 70025;
int dp[N];
signed main() {
    int k, n, m, M;
    while(k=nextint(),m=nextint(),n=nextint(), M=nextint()) {
        long long sum = 0, pw = 1;
        long long pwk = 1, ans = 1;
        for(int i = 0; i < m; i++) pwk = pwk*k%M;
        ++m;
        for(int i = 1; i <= n; i++) {
            if(i >= m)
                sum = (sum*k+dp[i-m]*pwk)%M;
            else
                sum = sum*k%M;
            dp[i] = sum+pw<M ? sum+pw : sum+pw-M;
            pw = pw*k%M;
        }
        for(int i = 1; i <= n; i++) ans = (ans*k+dp[i])%M;
        printf("%lld\n", ans);
    }
}

