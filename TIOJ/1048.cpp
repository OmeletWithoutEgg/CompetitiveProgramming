#include <cstdio>

int n,m,fr[13]={1};
int used[13];
int pick(int r) {
    for(int i = 0; i < n; i++) if(!used[i] && r--==0) return used[i]=1, i;
}
signed main() {
    for(int i = 1; i <= 12; i++) fr[i] = fr[i-1]*i;
    while(~scanf("%d%d", &n, &m) && n && m) {
        --m;
        m %= fr[n];
        for(int i = 0; i < n; i++) used[i] = 0;
        for(int i = n-1; i >= 0; i--) {
            int r = m/fr[i];
            printf("%c%c", char('A'+pick(r)), " \n"[i==0]);
            m%=fr[i];
        }
    }
}
