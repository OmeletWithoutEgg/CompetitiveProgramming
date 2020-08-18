#include <cstdio>
const int N = 51, K = 11;

int n,k,P[N][K],L[N][K],U[N][K];
bool canwin(int a[K],int b[K],int flag) {
    for(int i = 0; i < k+1; i++) if(a[i] <= b[i+k]) return flag;
    return true;
}
signed main() {
    scanf("%d%d", &k, &n);
    for(int t = 1,S; t <= n; t++) {
        scanf("%d", &S);
        for(int i = 0; i < k*2+1; i++) scanf("%d", &P[S][i]);
        for(int i = 0; i < k*2+1; i++) scanf("%d", &U[S][i]);
        for(int i = 0; i < k*2+1; i++) scanf("%d", &L[S][i]);
    }
    int A = 0, B = 0;
    for(int i = 1; i <= n; i++) {
        bool ok = 1;
        for(int j = 1; j <= n; j++) if(j!=i && !canwin(P[i],P[j],i<j)) ok = 0;
        if(ok && i > A) A = i;
    }
    for(int i = 1; i <= n; i++) {
        bool ok = 1;
        for(int j = 1; j <= n; j++) if(j!=i && !canwin(U[i],L[j],i<j)) ok = 0;
        if(ok && i > B) B = i;
    }
    printf("%d %d\n", A, B);
}

