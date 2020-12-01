#include <cstdio>
#include <cstdlib>

const int N = 200025;
int n, q, v[N];
struct SplayTree {
    struct node {
        int val, sz;
        int sum;
        int ch[2], pa;
        //bool rev;
    } S[N];
    bool dir(int i) {return i==S[S[i].pa].ch[1];}
    /*void filp(int i) {
        int t = S[i].ch[0]; S[i].ch[0]=S[i].ch[1]; S[i].ch[1]=t;
        if(i) S[i].rev = !S[i].rev;
    }
    void push(int i) {
        if(S[i].rev) {
            flip(S[i].ch[0]);
            flip(S[i].ch[1]);
            S[i].rev = false;
        }
    }
    void pushdown(int i) {
        if(S[i].pa) pushdown(S[i].pa);
        push(i);
    }*/
    void pull(int i) {
        S[i].sum = S[S[i].ch[0]].sum + S[i].val + S[S[i].ch[1]].sum;
        S[i].sz = S[S[i].ch[0]].sz + 1 + S[S[i].ch[1]].sz;
    }
    void rot(int x) {
        int y = S[x].pa, z = S[y].pa, d = dir(x);
        if(z) S[z].ch[dir(y)] = x;
        S[x].pa = z;
        S[y].ch[d] = S[x].ch[!d];
        if(S[x].ch[!d]) S[S[x].ch[!d]].pa = y;
        S[x].ch[!d] = y;
        S[y].pa = x;
        pull(x), pull(y);
    }
    void splay(int x) {
        while(int y = S[x].pa) {
            if(S[y].pa) rot(dir(x)!=dir(y) ? x : y);
            rot(x);
        }
    }
    int kth(int k) {
        splay(1);
        //printf("k = %d\n", k);
        for(int i = 1; ; ) {
            //printf("i = %d\n", i);
            //system("PAUSE");
            int s = S[S[i].ch[0]].sz + 1;
            //printf("%d\n", s);
            if(s == k) return splay(i), i;
            if(k < s) i = S[i].ch[0];
            else i = S[i].ch[1], k -= s;
        }
    }
    int getrank(int i) {
        splay(i);
        return S[S[i].ch[0]].sz + 1;
    }
    int endpoint(int i, bool d) {
        for(splay(i); S[i].ch[d]; i = S[i].ch[d]);
        return splay(i), i;
    }
    int split(int i, bool d) {
        splay(i);
        int res = S[i].ch[d];
        S[res].pa = S[i].ch[d] = 0, pull(i);
        return endpoint(res, !d);
    }
    void join(int a, int b) {
        splay(a), splay(b);
        if(!a || !b || S[a].pa || a == b) return;
        //printf("a = %d b = %d\n", a, b);
        S[b].pa = a, S[a].ch[1] = b, pull(a);
    }
    int getsum(int l, int r) { // [l, r]
        int a = split(l, 0), b = split(r, 1);
        int res = S[r].sum;
        join(a, l), join(r, b);
        return res;
    }
    //#define debug(x) printf(#x " = %d\n", x);
    void jizz(int l1, int r1, int l2, int r2) {
        //printf("IN\n");
        //debug(l1); debug(r1);
        int a1 = split(l1, 0), b1 = split(r1, 1);
        int a2 = split(l2, 0), b2 = split(r2, 1);
        //dbg(a1); dbg(b1); dbg(a2); dbg(b2);
        join(a1, l2), join(r2, b1);
        join(a2, l1), join(r1, b2);
        if(b1 == l2) join(r2, l1);
        //if(b2 == l1) join(r1, l2);
        //dbg();
        //printf("OUT\n");
    }
    void modify(int i, int d) {
        splay(i);
        S[i].val = d;
        pull(i);
    }
    void init(int n, int v[]) {
        for(int i = 1; i <= n; i++) S[i].sz = 1, S[i].val = S[i].sum = v[i];
        for(int i = 1; i <= n-1; i++) {
            splay(i);
            S[i].ch[1] = i+1, S[i+1].pa = i;
            pull(i);
        }
        /*
        std::function<int(int,int)> build = [&](int l, int r) {
            if(l > r) return 0;
            if(l == r) return l;
            int m = (l+r)/2;
            int L = build(l, m-1), R = build(m+1, r);
            S[m].ch[0] = L, S[m].ch[1] = R, S[L].pa = S[R].pa = m, pull(m);
            return m;
        };
        build(1, n);
        */
    }
    void dfs(int i) {
        if(!i) return;
        dfs(S[i].ch[0]);
        printf("%d ", i);
        dfs(S[i].ch[1]);
    }
    void dbg(int i = 1) {
        printf("SPLAY %d: ", i);
        splay(i);
        dfs(i);
        puts("");
    }
} sp;
struct segtree {
    int n;
    int sum[N<<1];
    void init(int _n, int v[]) {
        n = _n;
        for(int i = 0; i < n; i++) sum[i+n] = v[i];
        for(int i = n-1; i > 0; i--) sum[i] = sum[i<<1]+sum[i<<1|1];
    }
    void modify(int p, int d) {
        for(sum[p+=n] = d; p > 1; p >>= 1)
            sum[p>>1] = sum[p]+sum[p^1];
    }
    int query(int l, int r) { // [l, r) 0 base
        int res = 0;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res += sum[l++];
            if(r&1) res += sum[--r];
        }
        return res;
    }
} sgt;
signed main() {
    scanf("%d%d\n", &n, &q);
    for(int i = 1; i <= n; i++) scanf("%d", v+i);
    sp.init(n, v);
    sgt.init(n+1, v);
    while(q--) {
        int t;
        scanf("%d", &t);
        if(t == 1) {
            int i, j;
            scanf("%d%d", &i, &j);
            sp.jizz(i,i,j,j);
        }else if(t == 2) {
            int i, j;
            scanf("%d%d", &i, &j);
            i = sp.kth(i), j = sp.kth(j);
            sp.jizz(i,i,j,j);
        }else if(t == 3) {
            int i, d;
            scanf("%d%d", &i, &d);
            sp.modify(i, d);
            sgt.modify(i, d);
        }else if(t == 4) {
            int i, d;
            scanf("%d%d", &i, &d);
            i = sp.kth(i);
            sp.modify(i, d);
            sgt.modify(i, d);
        }else if(t == 5) {
            int l1, r1, l2, r2;
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            l1 = sp.kth(l1), r1 = sp.kth(r1), l2 = sp.kth(l2), r2 = sp.kth(r2);
            sp.jizz(l1, r1, l2, r2);
        }else if(t == 6) {
            int i;
            scanf("%d", &i);
            printf("%d\n", sp.kth(i));
        }else if(t == 7) {
            int i;
            scanf("%d", &i);
            printf("%d\n", sp.getrank(i));
        }else if(t == 8) {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%d\n", sgt.query(l, r+1));
        }else if(t == 9) {
            int l, r;
            scanf("%d%d", &l, &r);
            l = sp.kth(l), r = sp.kth(r);
            printf("%d\n", sp.getsum(l, r));
        }
        //sp.dbg();
    }
    return 0;
}
