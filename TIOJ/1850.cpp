#include <cstdio>
#include <bitset>
const int N = 100000001;

int n,p,k;
std::bitset<N> vis;
void dfs(int s) {
    static int stk[N], top;
    static char ans[N], tail;
    vis[s] = 1;
    stk[top++] = s;
    while(top) {
        s = stk[--top];
        ans[tail++] = (s%p)^'0';
        for(int x = p-1; x >= 0; x--) {
            int f = (s*p+x)%n;
            if(!vis[f]) {
                vis[f] = 1;
                stk[top++] = f;
            }
        }
    }
    while(tail) putchar(ans[--tail]);
}
signed main() {
    scanf("%d%d",&p,&k);
    for(n = 1; k--; n *= p);
    dfs(0);
}
