#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <iostream>
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
using namespace std;
constexpr int N = (1<<18)-1;

int nxt[N*2],cap[N*2],to[N*2],head[N],deg[N],tot,stk[N],p;
int pa[N], pa_d[N], id[N], mxS[N], mxF[N], n, best;
inline int min(int a,int b){return a<b?a:b;}
inline void addEdge(int a,int b,int w){
    ++tot;
    nxt[tot] = head[a];
    to[tot] = b;
    cap[tot] = w;
    head[a] = tot;
}
void dfs(int r){
    stk[p++] = r;
    while(p){
        int i = stk[--p];
        id[tot++] = i;
        for(int k = head[i]; k; k = nxt[k]) {
            int j = to[k], c = cap[k];
            if(j == pa[i]) continue;
            pa[j] = i;
            pa_d[j] = c;
            stk[p++] = j;
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 0, a, b, w; i < n-1; i++) {
        cin >> a >> b >> w;
        addEdge(a,b,w), addEdge(b,a,w);
        ++deg[a], ++deg[b];
    }
    tot = 0;
    dfs(1);
    for(int k = n-1; k >= 0; k--) {
        int i = id[k], c = pa_d[i];
        if(deg[i] == 1) mxS[pa[i]] += c; // leaf
        mxS[pa[i]] += min(c, mxS[i]);
    }
    best = mxF[1] = mxS[1];
    if(deg[1] == 1) mxF[1] *= 2;
    for(int k = 1; k < n; k++) {
        int i = id[k], c = pa_d[i];
        if(deg[i] == 1) mxF[i] = min(c, mxF[pa[i]]-c); //leaf
        else mxF[i] = mxS[i] + min(c, mxF[pa[i]]-min(c,mxS[i]));
        if(best < mxF[i]) best = mxF[i];
    }
    cout << best << '\n';
}
