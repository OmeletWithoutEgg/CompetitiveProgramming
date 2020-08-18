#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
const int N = 19, MOD = 1000000007;

inline int __lg(int x) {return 31-__builtin_clz(x);}
inline int add(int a,int b) {return a+b<MOD ? a+b : a+b-MOD;}
inline int sub(int a,int b) {return a-b<0 ? a-b+MOD : a-b;}
void RMT(int F[],int S,int R[][N]) {
    int L = __lg(S);
    for(int i = 0; i < S; i++) for(int k = 0; k <= L; k++) R[i][k] = 0;
    for(int i = 0; i < S; i++) R[i][__builtin_popcount(i)] = F[i];
    for(int s = 1; s < S; s<<=1) for(int i = 0; i < S; i++) if(i & s) for(int k = 0; k <= L; k++) R[i][k] = add(R[i][k], R[i^s][k]);
}
void IRMT(int R[][N],int S,int F[]) {
    int L = __lg(S);
    for(int s = 1; s < S; s<<=1) for(int i = 0; i < S; i++) if(i & s) for(int k = 0; k <= L; k++) R[i][k] = sub(R[i][k], R[i^s][k]);
    for(int i = 0; i < S; i++) F[i] = R[i][__builtin_popcount(i)];
}
void Oconv(int A[][N],int B[][N],int S,int C[][N]) {
    int L = __lg(S);
    for(int i = 0; i < S; i++) for(int k = 0; k <= L; k++) {
        C[i][k] = 0;
        for(int j = 0; j <= k; j++) C[i][k] = (C[i][k] + 1LL*A[i][j]*B[i][k-j]) % MOD;
    }
}
int adj[N][N];
int F[1<<N],R[1<<N];
int Fhat[5][1<<N][N],Rhat[1<<N][N],tmp[1<<N][N];
signed main() {
    int k,n,m;
    scanf("%d%d%d",&n,&m,&k);
    int S = 1<<n;
    for(int i = 0,a,b; i < m; i++) scanf("%d%d",&a,&b), --a, --b, adj[a][b] = adj[b][a] = true;
    F[0] = true;
    for(int s = 0; s < S; s++) {
        for(int i = 0; i < n; i++) if(s & (1<<i)) {
            int f = s^(1<<i);
            if(!F[f]) continue;
            F[s] = true;
            for(int j = 0; j < n; j++) if(f & (1<<j)) if(adj[i][j]) F[s] = false;
            if(F[s]) break;
        }
    }
    RMT(F,S,Fhat[0]);
    for(int L = 1; L < 5; L++) Oconv(Fhat[L-1],Fhat[L-1],S,Fhat[L]);

    for(int i = 0; i < S; i++) R[i] = (i==0);
    RMT(R,S,Rhat);
    for(int L = 4; L >= 0; L--) if(k & (1<<L)) {
        Oconv(Fhat[L],Rhat,S,tmp);
        for(int i = 0; i < S; i++) for(int k = 0; k <= n; k++) Rhat[i][k] = tmp[i][k];
    }
    IRMT(Rhat,S,R);
    int sum = R[S-1];

    for(int i = 0; i < S; i++) R[i] = (i==0);
    RMT(R,S,Rhat);
    int ans = 0;
    for(int L = 4; L >= 0; --L) if(ans+(1<<L) <= n) {
        Oconv(Fhat[L],Rhat,S,tmp);
        IRMT(tmp,S,R);
        if(!R[S-1]) {
            ans += 1<<L;
          	RMT(R,S,Rhat);
        }
    }
    ++ans;

    /*
    R[0] = 1;
    int ans = -1, sum = -1;
    for(int c = 1; c <= k || c <= n; c++) {
        RMT(R,S,Rhat);
        RMT(F,S,Fhat);
        Oconv(Rhat,Fhat,S,tmp);
        IRMT(tmp,S,R);
        if(R[S-1] && ans==-1) ans = c;
        if(c==k) sum = R[S-1];
    }
    */
    printf("%d\n%d", ans, sum);
}
