#include <bits/stdc++.h>
using namespace std;
const int N = 400025;
typedef long long ll;

int head[N],to[N],nxt[N],tot;
ll c[N];
void addEdge(int a,int b,ll d) {
    ++tot;
    nxt[tot] = head[a];
    to[tot] = b;
    c[tot] = d;
    head[a] = tot;
}
int stk[N],p;
int pa[20][N],dep[N];
ll pa_d[20][N];
void dfs(int i) {
    stk[p++] = i;
    while(p) {
        i = stk[--p];
        for(int id = head[i]; id; id = nxt[id]) {
            int j = to[id];
            if(j == pa[0][i]) continue;
            dep[j] = dep[i]+1;
            pa[0][j] = i;
            pa_d[0][j] = c[id];
            stk[p++] = j;
        }
    }
}
ll query(int a,int b) {
    if(dep[a] < dep[b]) swap(a,b);
    int dif = dep[a]-dep[b];
    ll res = 0;
    for(int i = 19; i >= 0; i--) if(dif & (1<<i)) res |= pa_d[i][a], a = pa[i][a];
    if(a == b) return res;
    for(int i = 19; i >= 0; i--) if(pa[i][a] != pa[i][b]) {
        res |= pa_d[i][a]|pa_d[i][b];
        a = pa[i][a], b = pa[i][b];
    }
    return res|pa_d[0][a]|pa_d[0][b];
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n,q;
    cin >> n;
    for(int i = 1; i < n; i++) {
        int a,b;
        ll d;
        cin >> a >> b >> d;
        addEdge(a,b,d), addEdge(b,a,d);
    }
    dfs(1);
    for(int L = 1; L < 20; L++) for(int i = 1; i <= n; i++)
        pa[L][i] = pa[L-1][pa[L-1][i]], pa_d[L][i] = pa_d[L-1][i] | pa_d[L-1][pa[L-1][i]];
    cin >> q;
    for(int i = 0; i < q; i++) {
        int a,b;
        cin >> a >> b;
        cout << query(a,b) << '\n';
    }
}

