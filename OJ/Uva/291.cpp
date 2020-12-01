#include <bits/stdc++.h>

using namespace std;

int g[5][5] = {
    {0,1,1,0,1},
    {1,0,1,0,1},
    {1,1,0,1,1},
    {0,0,1,0,1},
    {1,1,1,1,0}
};
set<string> ans;
void dfs(int v,string s = ""){
    if(s.size()>=8)ans.insert(s);
    s += v + '1';
    for(int i = 0;i < 5;i++)if(g[i][v]){
        g[i][v]--,g[v][i]--,dfs(i,s),++g[i][v],++g[v][i];
    }
}
main(){
    dfs(0);
    for(auto s:ans){
        cout << s+'2' << '\n';
    }
    return 0;
}
