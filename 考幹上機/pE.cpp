#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<':'<<x<<'\n')
#define REP(i,l,r) for(int i = l;i < r;i++)
#define ff first
#define ss second
#define N 5000

using namespace std;
typedef long long ll;

int n,q,x,k = 0,op,a,b;
set<ll> g[N] = {};
signed main(){
    cin >> n >> q >> x;
    REP(_,0,q){
        cin >> op >> a >> b;
        if(x)a^=k, b^=k;
        if(op == 0){ // add edge
            g[a].insert(b),g[b].insert(a);
        }else if(op == 1){ // delete edge
            g[a].erase(b),g[b].erase(a);
        }else if(op == 2){ // query of connected
            if(dfs(a,b))cout << "Y\n", k = a;
            else cout << "N\n", k = b;
        }
    }
}

