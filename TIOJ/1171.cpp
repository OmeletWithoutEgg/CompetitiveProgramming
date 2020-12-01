#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N = 100025;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    bool neg=false;
    int x = 0, c = readchar();
    while(('0'>c||c>'9')&&c!='-') c = readchar();
    if(c=='-') neg=true, c=readchar();
    while('0'<=c&&c<='9') x=x*10+c-'0', c=readchar();
    if(neg) x = -x;
    return x;
}

struct segtree {
    ll w[N<<1],sum[N<<1];
    int laz[N],n;
    void init(ll _w[],int _n) {
        n = _n;
        for(int i = 0; i < n; i++) w[i+n] = _w[i];
        for(int i = n-1; i > 0; i--) w[i] = w[i<<1]+w[i<<1|1];
    }
    void upd(int p,int d) {
        sum[p] += d*w[p];
        if(p < n) laz[p] += d;
    }
    void pull(int p) {
        while(p>1) sum[p>>1] = sum[p] + sum[p^1] + laz[p>>1]*w[p>>1], p>>=1;
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p>>h;
            if(!laz[i>>1]) continue;
            upd(i,laz[i>>1]);
            upd(i^1,laz[i>>1]);
            laz[i>>1] = 0;
        }
    }
    void edit(int l,int r,int d) {
        int L = l, R = r;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) upd(l++,d);
            if(r&1) upd(--r,d);
        }
        pull(L+n), pull(R-1+n);
    }
    ll query(int l,int r) {
        ll res = 0;
        push(l+n), push(r-1+n);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res += sum[l++];
            if(r&1) res += sum[--r];
        }
        return res;
    }
} sgt;
struct HeavyLightDecomposition {
    struct Edge {int cost,to;};
    vector<Edge> g[N];
    int sz[N],mxs[N],id[N],tot,link_top[N],pa[N];
    ll weight[N],dis[N],pa_d[N],sumd,sumc;
    void addEdge(int a,int b,int c) {
        g[a].push_back({c,b});
        g[b].push_back({c,a});
    }
    void dfs(int i) {
        sz[i] = 1;
        mxs[i] = 0;
        for(auto &edge:g[i]) {
            int j = edge.to;
            int c = edge.cost;
            if(j == pa[i]) continue;
            pa[j] = i;
            pa_d[j] = c;
            dis[j] = dis[i] + c;
            dfs(j);
            sz[i]+=sz[j];
            if(mxs[i]==0 || sz[j] > sz[mxs[i]]) mxs[i] = j;
        }
    }
    void deco(int i,int t) {
        link_top[i] = t;
        weight[id[i] = tot++] = pa_d[i];
        if(mxs[i]) deco(mxs[i],t);
        for(auto &edge:g[i]) {
            int j = edge.to;
            if(j == pa[i] || j == mxs[i]) continue;
            deco(j,j);
        }
    }
    void init(int n) {
        dfs(1);
        deco(1,1);
        sgt.init(weight,n);
    }
    void poke(int x) {
        sumd += dis[x];
        ++sumc;
        while(x) {
            int y = link_top[x];
            sgt.edit(id[y],id[x]+1,1);
            x = pa[y];
        }
    }
    ll query(int x) {
        ll res = sumc * dis[x] + sumd;
        while(x) {
            int y = link_top[x];
            res -= 2*sgt.query(id[y],id[x]+1);
            x = pa[y];
        }
        return res;
    }
} HLD;
bool app[N];
signed main() {
    int n = nextint();
    int q = nextint();
    for(int i = 1; i < n; i++) {
        int a = nextint()+1;
        int b = nextint()+1;
        int c = nextint();
        HLD.addEdge(a,b,c);
    }
    HLD.init(n);
    while(q--) {
        int t = nextint();
        int x = nextint()+1;
        if(t == 1) {
            if(!app[x]) app[x] = 1, HLD.poke(x);
        }else if(t == 2) {
            printf("%lld\n", HLD.query(x));
        }
    }
}

/*
4 2
0 1 40
1 2 11
1 3 18
1 2
2 3
*/

