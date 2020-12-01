#pragma GCC optimize("Ofast")
#include <iostream>
#include <cstring>

using namespace std;
const int N = 1000025;

int Next[N*2],To[N*2],Head[N],tot;
int prv[N];
unsigned dis[N];
int n,m,a,b,k;
int Q[N],head,tail,tmp;
inline void addEdge(int a,int b){
    Next[tot] = Head[a];
    To[tot] = b;
    Head[a] = tot;
    tot++;
}
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> a >> b;
    for(int i = 1; i <= n; i++) Head[i] = -1;
    memset(dis,-1,sizeof dis);
    for(int i = 0, u, v; i < m; i++) {
        cin >> u >> v;
        addEdge(u,v), addEdge(v,u);
    }
    Q[0] = b, dis[b] = 0, head = 0, tail = 1;
    for(;;) {
        for(k = head, tmp = tail; k < tail; k++) {
            int i = Q[k];
            for(int t = Head[i]; ~t; t = Next[t]) {
                int j = To[t];
                if (dis[j] > dis[i]+1) {
                    dis[j] = dis[i]+1;
                    prv[j] = i;
                    Q[tmp++] = j;
                }else if(dis[j] == dis[i]+1 && prv[j] > i) prv[j] = i;
            }
        }
        if(~dis[a]) {
            cout << dis[a]-1 << '\n';
            for(int x = a; prv[x]; x = prv[x]) cout << x << '-';
            cout << b << '\n';
            return 0;
        }
        head = tail, tail = tmp;
    }
}
