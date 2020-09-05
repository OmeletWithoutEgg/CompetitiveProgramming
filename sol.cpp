#include <bits/stdc++.h>
#define pb emplace_back
#define debug(args...) qqbx(#args, args)
template <typename H, typename ...T> void qqbx(const char *s, const H &h, T&& ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
using namespace std;
typedef long long ll;
const int N = 100025, inf = 1e9;

struct LinkCutTree {
    struct node {
        int pa, ch[2];
        ll a, b, val;
        node(int p=0, int v=0) : pa(p), ch{0,0}, a(0), b(inf), val(v) {}
    } T[N];
    bool dir(int x) { return T[T[x].pa].ch[1] == x; }
    bool isroot(int x) { return !x || T[T[x].pa].ch[dir(x)] != x; }
    void rot(int x) {
        int y = T[x].pa, z = T[y].pa, d = dir(x);
        T[x].pa = z;
        if(!isroot(y)) T[z].ch[dir(y)] = x;
        if(T[x].ch[!d]) T[T[x].ch[!d]].pa = y;
        T[y].ch[d] = T[x].ch[!d];
        T[y].pa = x;
        T[x].ch[!d] = y;
    }
    void upd(int x, ll a, ll b) {
        T[x].val = min(T[x].val + a, b);
        T[x].a += a;
        T[x].b = min(T[x].b + a, b);
    }
    void push(int x) {
        if(!isroot(x)) push(T[x].pa);
        if(T[x].a == 0 && T[x].b == inf) return;
        for(int d: {0, 1}) if(T[x].ch[d]) upd(T[x].ch[d], T[x].a, T[x].b);
        T[x].a = 0;
        T[x].b = inf;
    }
    void splay(int x) {
        push(x);
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
            last = x;
            x = T[x].pa;
        }
        return last;
    }
    void modify(int x, int y, int a, int b) {
        access(x);
        int LCA = access(y);
        splay(x);
        if(x == LCA) {
            upd(T[x].ch[1], a, b);
        } else {
            upd(T[LCA].ch[1], a, b);
            upd(x, a, b);
        }
    }
    ll eval(int x) {
        splay(x);
        return T[x].val;
    }
} lct;
int eid[N];
signed main () {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<vector<tuple<int,int,int>>> g(n+1); // cost, edgeid, toid
    for(int i = 1; i < n; i++) {
        int a, b, w;
        cin >> a >> b >> w;
        g[a].pb(w, i, b);
        g[b].pb(w, i, a);
    }
    function<void(int, int)> dfs = [&](int i, int p) {
        for(auto [c, id, j]: g[i]) {
            if(j != p) {
                lct.T[j] = LinkCutTree::node(i, c);
                eid[id] = j;
                dfs(j, i);
            }
        }
    };
    dfs(1, 0);
    int q;
    cin >> q;
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int x, y, a, b;
            cin >> x >> y >> a >> b;
            lct.modify(x, y, a, b);
        } else if(t == 2) {
            int id;
            cin >> id;
            // --id / ++id ??
            debug(eid[id]);
            cout << lct.eval(eid[id]) << '\n';
        }
    }
}

/*
5
1 5 3
1 4 6
4 2 3
3 1 9
4
1 1 4 10 9
1 5 3 4 2
1 3 2 6 9
2 3

  *2   *8
5 -- 1 -- 3
     | *9
     4
     | *9
     2
*/
