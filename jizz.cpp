#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 505;
int vis[N];
vector<int> g[N];
int tot;
int ans;
void dfs(int cu,int sum)
{
    if (sum > ans) return;
    if (cu > tot)
    {
        ans = sum;
        return;
    }
    if (vis[cu]) dfs(cu+1,sum);
    else
    {
        vis[cu]++;
        dfs(cu+1,sum+1);
        vis[cu]--;
        for (auto x : g[cu])
        {
            if (!vis[x]) sum++;
            vis[x]++;
        }
        dfs(cu+1,sum);
        for (auto x : g[cu])
        {
            vis[x]--;
            if (!vis[x]) sum--;
        }
    }
}
int main()
{
    int n,m;
    while (scanf("%d%d",&n,&m) != EOF)
    {
        tot = 0;
        ans = 10000;
        memset(vis,0,sizeof(vis));
        for (int i = 1;i <= n;i++) g[i].clear();
        for (int i = 0;i < m;i++)
        {
            int x,y;
            if(scanf("%d%d",&x,&y) != 2) exit(0);
            g[x].push_back(y);
            g[y].push_back(x);
        }
        tot = min(30,n);
        ans = tot;
        dfs(1,0);
        printf("tot = %d\n", tot);
        printf("%d\n",ans);
    }
    return 0;
}
