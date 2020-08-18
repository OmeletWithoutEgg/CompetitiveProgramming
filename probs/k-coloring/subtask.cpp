#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
const int N = 20, MOD = 1000000007;

inline int __lg(int x) {return 31-__builtin_clz(x);}
inline int add(int a,int b) {return a+b<MOD ? a+b : a+b-MOD;}
inline int sub(int a,int b) {return a-b<0 ? a-b+MOD : a-b;}
int k,n,m,a,b;
int valid[1<<N];
int g[N][N];
int dp[2][1<<N];
signed main() {
    scanf("%d%d%d",&n,&m,&k);
    for(int i = 0; i < m; i++) scanf("%d%d",&a,&b), --a, --b, g[a][b] = g[b][a] = true;
    valid[0] = true;
    for(int i = 0; i < n; i++) valid[1<<i] = true;
    for(int s = 0; s < (1<<n); s++) {
        for(int i = 0; i < n; i++) if(s & (1<<i)) {
            int f = s^(1<<i);
            if(valid[f]) {
                valid[s] = true;
                for(int j = 0; j < n; j++) if(f & (1<<j)) if(g[i][j]) valid[s] = false;
                if(valid[s]) break;
            }
        }
    }
    int ans = 1e9;
    int sum = 0;
    int S = 1<<n;
    dp[0][0] = 1;
    for(int c = 1; c <= k || c <= n; c++) {
        for(int s = 0; s < S; s++) {
            dp[1][s] = dp[0][s];
            for(int f = s; f; f = (f-1)&s) dp[1][s] = (dp[1][s] + dp[0][s^f] * valid[f]) % MOD;
        }
        if(dp[1][S-1] && ans>c) ans = c;
        if(c == k) sum = dp[1][S-1];
        for(int s = 0; s < S; s++) dp[0][s] = dp[1][s], dp[1][s] = 0;
    }
    printf("%d\n%d\n",ans,sum);
}

