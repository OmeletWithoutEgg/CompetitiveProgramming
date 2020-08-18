#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
const int N = 51, inf = 1e9;

int v[N][N],n,m,sum[N][N];
signed main() {
    while(scanf("%d%d", &n, &m) == 2) {
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) scanf("%d", &v[i][j]);
        for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) v[i][j]+=v[i][j-1];
        int best = -inf;
        for(int l = 0; l < m; l++) for(int r = l+1; r <= m; r++) sum[l][r] = 0;
        for(int i = 1; i <= n; i++) {
            for(int l = 0; l < m; l++) for(int r = l+1; r <= m; r++) {
                if(sum[l][r]<0) sum[l][r]=0;
                if(best < (sum[l][r] += v[i][r]-v[i][l])) best = sum[l][r];
            }
        }
        printf("%d\n", best);
    }
}

