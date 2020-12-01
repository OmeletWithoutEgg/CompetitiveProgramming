#pragma g++ optimize("Os")
#include <cstdio>
const int N = 20;

inline int __lg(int x) {return 31-__builtin_clz(x);}
int k,n,a,b;
int valid[1<<N];
char g[N][N];
int dp[2][1<<N];
int Fhat[1<<N][N],Ghat[1<<N][N],Rhat[1<<N][N];
void RMT(int F[],int n,int R[][N]) {
    for(int s = 0; s < (1<<n); s++) R[s][__builtin_popcount(s)] = F[s];
    for(int i = 0; i < n; i++) for(int s = 0; s < (1<<n); s++) if(s & (1<<i)) {
        for(int k = 0; k <= n; k++) R[s][k] += R[s^(1<<i)][k];
    }
}
void IRMT(int R[][N],int n,int F[]) {
    for(int i = 0; i < n; i++) for(int s = 0; s < (1<<n); s++) if(s & (1<<i)) {
        for(int k = 0; k <= n; k++) R[s][k] -= R[s^(1<<i)][k];
    }
    for(int s = 0; s < (1<<n); s++) F[s] = R[s][__builtin_popcount(s)];
}
void convolution(int F[],int G[],int n,int R[]) {
    for(int s = 0; s < (1<<n); s++) for(int k = 0; k <= n; k++) Rhat[s][k] = Fhat[s][k] = Ghat[s][k] = 0;
    RMT(F,n,Fhat);
    RMT(G,n,Ghat);
    for(int k = 0; k <= n; k++) for(int s = 0; s < (1<<n); s++) for(int i = 0; i <= k; i++) Rhat[s][k] += Fhat[s][i]*Ghat[s][k-i];
    IRMT(Rhat,n,R);
}
signed main() {
    scanf("%d%d",&n,&k);
    while(~scanf("%d%d",&a,&b)) --a, --b, g[a][b] = g[b][a] = true;
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
        convolution(dp[0],valid,n,dp[1]);
        /*
        for(int s = 0; s < S; s++) {
            dp[1][s] = dp[0][s];
            for(int f = s; f; f = (f-1)&s) dp[1][s] += dp[0][s^f] * valid[f]; // dp[1][S]= \sum_{a&b=0,a|b=S}valid[a]*dp[0][b];
        }
        */
        if(dp[1][S-1] && ans>c) ans = c;
        if(c == k) sum = dp[1][S-1];
        for(int s = 0; s < S; s++) dp[0][s] = dp[1][s], dp[1][s] = 0;
    }
    printf("%d\n%d\n",sum,ans);
}
