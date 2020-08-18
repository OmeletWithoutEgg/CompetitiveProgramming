#include <cstdio>
typedef long long ll;
const ll inf = 1e18;

int n,m,a,b,w,q;
ll g[501][501];
int main() {
    scanf("%d%d",&n,&m);
    for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) if(i!=j) g[i][j]=inf;
    while(m--) {
        scanf("%d%d%d",&a,&b,&w);
        --a, --b;
        if(g[a][b] > w) g[a][b]=g[b][a]=w;
    }
    for(int k = 0; k < n; k++) for(int i = 0; i < n; i++) for(int j = 0; j < n; j++)
        if(g[i][j] > g[i][k]+g[k][j]) g[i][j] = g[i][k]+g[k][j];
    scanf("%d",&q);
    while(q--) {
        scanf("%d%d", &a, &b);
        --a, --b;
        if(g[a][b]==inf)
            printf("-1\n");
        else
            printf("%lld\n", g[a][b]);
    }
}
