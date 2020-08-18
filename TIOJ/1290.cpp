#include <cstdio>
#include <cstring>

unsigned V,E,a,b,g[1010][1010],u,v,w;
main(){
    while(~scanf("%d%d%d%d",&V,&E,&a,&b)){
        for(int i = 1; i <= V; i++)
            for(register int j = 1; j < i; j++)
                g[i][j] = g[j][i] = 0x3f3f3f3f;
        while(E--) scanf("%d%d%d",&u,&v,&w), g[u][v]>w&&(g[u][v] = g[v][u] = w);
        if(a == b) {
            printf("0\n");
            continue;
        }
        for(int k = 1; k <= V; k++)
            for(register int i = 1; i <= V; i++)
                for(register int j = 1; j <= V; j++)
                    if(g[i][j] > g[i][k]+g[k][j])
                       g[i][j] = g[i][k]+g[k][j];
        if(g[a][b]!=0x3f3f3f3f) printf("%d\n",g[a][b]);
        else printf("He is very hot\n");
    }
}
