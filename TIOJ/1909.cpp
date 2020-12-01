#include <bits/stdc++.h>
#define fread fread_unlocked
using namespace std;
const int N = 1000001;

inline int readchar() {
    const int B = 1048576;
    static char buf[B];
    static char *p = buf, *tail = buf;
    if(p == tail) {
        if((tail = buf + fread(buf, 1, B, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int next_int() {
    //bool neg = false;
    int x = 0, c = readchar();
    while('0'>c || c>'9') c=readchar();
    //if(c=='-') neg=1, c=readchar();
    while('0'<=c && c<='9') x=x*10+c-'0', c=readchar();
    return x;
}
int n,v[N],P[N];
int64_t sz[N],ans[N];
int head[N], nxt[N*2], to[N*2], cnt;
void addEdge(int a,int b) {
    ++cnt;
    nxt[cnt] = head[a];
    to[cnt] = b;
    head[a] = cnt;
}
void dfs(int i,int p=0) {
    sz[i] = 1;
    for(int id = head[i]; id; id=nxt[id]) {
        int j = to[id];
        if(j == p) continue;
        dfs(j,i);
        ans[i] += sz[i]*sz[j];
        sz[i] += sz[j];
    }
    ans[i] += sz[i] * (n-sz[i]);
}
int stk[N],p;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    n = next_int();
    for(int i = 1; i <= n; i++) v[i] = next_int();
    for(int i = 1; i <= n; i++) {
        int last = -1;
        while(p && v[stk[p-1]] <= v[i]) last = stk[--p];
        if(last!=-1) P[last] = i;
        if(p) P[i] = stk[p-1];
        stk[p++] = i;
    }
    for(int i = 1; i <= n; i++) if(P[i]) {
        addEdge(P[i],i);
        addEdge(i,P[i]);
    }
    dfs(1);
    int mx = max_element(ans+1,ans+n+1)-ans;
    cout << ans[mx]*2 << ' ' << mx << '\n';
}
