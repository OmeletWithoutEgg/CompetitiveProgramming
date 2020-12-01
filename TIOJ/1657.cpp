#include <cstdio>

short n,m;
signed main() {
    while(scanf("%hd%hd", &n, &m) == 2) {
        for(register char i = 1; i <= n; i++)
            for(register char j = 1; j <= m; j++)
                printf("%d*%d=%d%c",i,j,i*j," \n"[j==m]);
    }
}
