#pragma GCC optimize("Os")
#include <cstdio>
const int N = 525;
inline int nextint() {
    int x = 0, c = getchar();
    while(c < '0') c = getchar();
    while(c >= '0') x=x*10+(c^'0'), c = getchar();
    return x;
}
inline void out(int x) {
    static char stk[N], p;
    while(x) stk[p++] = (x%10) + '0', x /= 10;
    while(p) putchar(stk[--p]);
    putchar(' ');
}

int A[N], B[N], match[N], dp[N], fr[N];
int ans[N], p;
signed main() {
    int t = nextint();
    while(t--) {
        int n = nextint();
        for(int i = 1; i <= n; i++) A[i] = nextint();
        for(int i = 1; i <= n; i++) B[i] = nextint();
        for(int i = 1; i <= n; i++) {
            match[i] = 0;
            for(int j = 1; j <= n; j++) if(A[i] == B[j]) match[i] = j;
        }
        A[0] = 1e9;
        dp[0] = 0;
        match[0] = -1;
        int best = 0;
        for(int i = 1; i <= n; i++) if(match[i]) {
            dp[i] = -1;
            fr[i] = -1;
            for(int j = 0; j < i; j++) if(match[j]) {
                if(A[j] > A[i] && match[j] < match[i] && dp[j]+1 > dp[i]) {
                    dp[i] = dp[j]+1;
                    fr[i] = j;
                }
            }
            if(dp[i] > dp[best]) best = i;
        }
        while(best) ans[p++] = A[best], best = fr[best];
        while(p) out(ans[--p]);
        putchar('\n');
    }
}
