#include <bits/stdc++.h>
#define pb emplace_back
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
void qqbx(const char *s) {}
template <typename H, typename ...T> void qqbx(const char *s, const H &h, T ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if (sizeof...(T)) qqbx(++s, args...);
}

using namespace std;
typedef int64_t ll;
const int N = 200025, MOD = 1000000007;

struct LCT {
    struct node {
        int pa, ch[2];
        int mx, v;
        node(int pa = 0, int v = 0) : pa(pa), v(v), mx(v) { ch[0]=ch[1]=0; }
    } T[N];
    int dir(int x) {
        return T[T[x].pa].ch[1] == x;
    }
    int isroot(int x) {
        return T[T[x].pa].ch[dir(x)] != x;
    }
    void pull(int x) {
        T[x].mx = max({ T[x].v, T[T[x].ch[0]].mx, T[T[x].ch[1]].mx });
    }
    void rot(int x) {
        int y = T[x].pa, z = T[y].pa, d = dir(x);
        T[x].pa = z;
        if(!isroot(y)) T[z].ch[dir(y)] = x;
        T[T[x].ch[!d]].pa = y;
        T[y].ch[d] = T[x].ch[!d];
        T[y].pa = x;
        T[x].ch[!d] = y;
        pull(y), pull(x);
    }
    void splay(int x) {
        while(!isroot(x)) {
            int y = T[x].pa;
            if(!isroot(y))
                rot(dir(x) ^ dir(y) ? x : y);
            rot(x);
        }
    }
    int access(int x) {
        int last = 0;
        while(x) {
            splay(x);
            T[x].ch[1] = last;
            pull(x);
            last = x;
            x = T[x].pa;
        }
        return last;
    }
    int query(int a, int b) {
        access(a);
        int LCA = access(b);
        splay(a);
        if(a == LCA) return max( T[LCA].v, T[T[LCA].ch[1]].mx );
        return max({ T[a].mx, T[LCA].v, T[T[LCA].ch[1]].mx });
    }
    void update(int a, int d) {
        splay(a);
        T[a].v = d;
        pull(a);
    }
} lct;
vector<int> g[N];
int w[N];
void dfs(int i, int p) {
    lct.T[i] = LCT::node(p, w[i]);
    for(int j: g[i]) {
        if(j == p) continue;
        dfs(j, i);
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> w[i];
    for(int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].pb(b), g[b].pb(a);
    }
    dfs(1, 0);
    while(q--) {
        int com, a, b;
        cin >> com >> a >> b;
        if(com == 1) {
            cout << lct.query(a, b) << '\n';
        } else {
            lct.update(a, b);
        }
    }
}
