#include <bits/stdc++.h>
#define pb push_back
#define mkp make_pair
#define N 100005

using namespace std;
typedef pair<int,int> pii;

int n;
int P,disP;//node p
vector<pii> g[N+1];
bitset<N+1> ntVis;
void dfs(int root){
    ntVis.reset();
    pii stk[N+1];
    int siz = 0;
    stk[siz++] = mkp(root,0);
    while(siz){
        pii cur = stk[--siz];
        ntVis[cur.first] = true;
        //cout << "dis[" << cur.first << "]:" << cur.second << '\n';
        if(disP < cur.second)P = cur.first,disP = cur.second;
        for(auto p:g[cur.first])if(!ntVis[p.first])stk[siz++] = mkp(p.first,cur.second + p.second);
    }
}
int main(){
    while(cin >> n,n){
        for(int i = 0;i < n;i++)g[i].clear();
        int t,f,w;
        for(int i = 0;i < n-1;i++)cin >> t >> f >> w,--t,--f,g[t].pb({f,w}),g[f].pb({t,w});
        /*for(int i = 0;i < n;i++){
            cout << i << ':';
            for(auto p:g[i])cout << p.first << ' ';
            cout << '\n';
        }*/
        P = 0;disP = 0;
        dfs(0);
        int tmp = P;P = 0,disP = 0;
        dfs(tmp);
        cout << disP << '\n';
    }
    return 0;
}

