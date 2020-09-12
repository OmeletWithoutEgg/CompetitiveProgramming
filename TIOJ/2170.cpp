#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")

#include <cstdio>

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}
const int N = 105;
int v[N], A[N][N];
int inv[65537];
signed main() {
    int n, mod;
    scanf("%d%d", &n, &mod);
    // mod - mod % i = i * (mod / i)
    inv[1] = 1;
    for(int i = 2; i < mod; i++) inv[i] = 1LL * (mod - mod / i) * inv[mod%i] % mod;
    for(int i = 0; i < n; i++) scanf("%d", v+i);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) scanf("%d", &A[j][i]);
    // Ax = v, solve x
    for(int k = 0; k < n; k++) {
        if(A[k][k] == 0) {
            // debug("SWAP!");
            int t = k;
            for(int i = k+1; i < n; i++) if(A[i][k] > A[t][k]) t = i;
            for(int j = 0; j < n; j++) swap(A[k][j], A[t][j]);
            swap(v[t], v[k]);
        }
        /* assert(A[k][k]); */
        for(int i = 0; i < n; i++) if(i != k) {
            int r = A[i][k] * inv[mod-A[k][k]] % mod;
            for(int j = 0; j < n; j++) A[i][j] = (A[i][j] + r * A[k][j]) % mod;
            v[i] = (v[i] + r * v[k]) % mod;
        }
    }
    /* for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) assert(i == j ? A[i][j] > 0 : A[i][j] == 0); */
    for(int i = 0; i < n; i++) printf("%d%c", v[i] * inv[A[i][i]] % mod, (i+1==n ? '\n' : ' '));
}
