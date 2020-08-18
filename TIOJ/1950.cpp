#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
const int N = 100001;
inline char readchar() {
    static const constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while('0'>c || c>'9') c = readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    return x;
}

struct Splay {
    struct node {
        int ch[2],pa;
        int lf[2];
    } T[N];
    void pull(int i){
        T[i].lf[0] = T[i].ch[0] ? T[T[i].ch[0]].lf[0] : i;
        T[i].lf[1] = T[i].ch[1] ? T[T[i].ch[1]].lf[1] : i;
    }
    bool isroot(int x){return T[x].pa==0;}
    bool dir(int x){return T[T[x].pa].ch[1] == x;}
    void rot(int x) {
        int y = T[x].pa, z = T[y].pa, d = dir(x);
        T[x].pa = z;
        if(!isroot(y)) T[z].ch[dir(y)] = x;
        T[T[x].ch[!d]].pa = y, T[y].ch[d] = T[x].ch[!d];
        T[x].ch[!d] = y, T[y].pa = x;
        pull(y), pull(x);
    }
    int splay(int x) {
        while(!isroot(x)) {
            int y = T[x].pa;
            if(!isroot(y)) {
                if(dir(x) ^ dir(y))
                    rot(x);
                else
                    rot(y);
            }
            rot(x);
        }
        return T[x].lf[0];
    }
    void cut(int x) {
        splay(x);
        T[T[x].ch[0]].pa = 0, T[x].ch[0] = 0, T[x].lf[0] = x;
    }
    void link(int x,int y) {
        if(splay(x) == splay(y)) return;
        T[y].pa = x, T[x].ch[1] = y;
        splay(y);
    }
    int poke(int x,int y) {
        if(splay(x) == splay(y)) {
            int a = splay(x), b = T[x].lf[1];
            cut(x);
            link(b,a);
            cut(y);
            return -1;
        }else {
            int a = T[x].lf[0], b = T[y].lf[0];
            cut(x);
            cut(y);
            link(T[x].lf[1],a);
            link(T[y].lf[1],b);
            link(T[a].lf[1],T[b].lf[0]);
            return 1;
        }
    }
    void init(int n) {
        for(int i = 1; i <= n; i++) T[i].lf[0] = T[i].lf[1] = i, T[i].pa = T[i].ch[0] = T[i].ch[1] = 0;
    }
    /*void dfs(int i) {
        if(!i) return;
        dfs(T[i].ch[0]);
        cout << i << ' ';
        dfs(T[i].ch[1]);
    }
    void dbg(int n) {
        //return;
        cout << "===\n";
        for(int i = 1; i <= n; i++) if(isroot(i)) dfs(i), cout << '\n';
        cout << "===\n\n";
    }*/
} seq;
int n,q,v[N],vis[N],pos[N],ans;
signed main() {
    n = nextint(), q = nextint();
    seq.init(n);
    for(int i = 1; i <= n; i++) pos[v[i] = nextint()] = i;
    for(int i = 1; i <= n; i++) if(!vis[i]) {
        int last = 0;
        for(int x = i; !vis[x]; x = pos[x]) {
            if(last) ans += seq.poke(v[last],v[x]);
            vis[x] = 1;
            last = x;
        }
    }
    printf("%d\n", ans);
    //tr.dbg(n);
    //return 0;
    while(q--) {
        int a = nextint(), b = nextint();
        ans += seq.poke(a,b);
        printf("%d\n", ans);
        //tr.dbg(n);
    }
}

