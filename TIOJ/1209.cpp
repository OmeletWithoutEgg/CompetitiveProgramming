#include <bits/stdc++.h>
#define REP(i,l,r) for(int i = l;i < r;i++)
#define N 500000

using namespace std;

int lab[N+1] = {},x,y,res;
vector<int> g[N+1] = {};
void dfs(int cur,int l = 1){
    //cout << cur << '\n';
    for(auto nxt:g[cur]){
        if(!lab[nxt])lab[nxt]=-l,dfs(nxt,-l);
        else if(lab[nxt] == l)return res=0,void();
    }
}
signed main(){
    int n,m;
    while(~scanf("%d%d",&n,&m),n||m){
        REP(i,0,n) lab[i] = 0, g[i].clear();
        REP(_,0,m) scanf("%d%d",&x,&y), --x, --y, g[x].push_back(y), g[y].push_back(x);
        res = 1;
        REP(i,0,n)if(!lab[i])lab[i]=1, dfs(i);
        //REP(i,0,n)printf("%d ",lab[i]);printf("\n");
        puts(res?"Yes":"No");
    }
}
