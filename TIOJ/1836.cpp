#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#pragma loop_opt(on)
#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
#define get_pos(v,x) int(lower_bound(begin(v),end(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back

const int N = 22000, LG = 12;
 
using namespace std;
using ll = long long;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline ll nextll() {
    ll x = 0;
    char c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

struct FastOut {
    char *buf;
    int q;
    const int B;
    inline void writeln(ll x) {
        static char stk[20];
        char p = 0;
        if(!x) stk[p++] = '0';
        while(x) stk[p++] = x%10^'0', x/=10;
        while(p) buf[q++] = stk[--p];
        buf[q++] = '\n';
        if(q + 20 >= B) fwrite(buf, 1, q, stdout), q = 0;
    }
    FastOut(int B = 1<<20) : B(B), q(0), buf(new char[B]){}
    ~FastOut() {
        fwrite(buf, 1, q, stdout);
        delete [] buf;
    }
};

inline ll gcd(ll a, ll b) {
    if(!a || !b) return a | b;
    int s = __builtin_ctzll(a | b);
    a >>= s, b >>= s;
    while(a && b) {
        a >>= __builtin_ctzll(a);
        b >>= __builtin_ctzll(b);
        if(a > b) a -= b;
        else if(b > a) b -= a;
        else return a << s;
    }
    return (a|b) << s;
}

int R, C;
struct Segtree1d {
    // 1d, dynamic
    struct node {
        ll ans;
        node *l, *r;
        node() : ans(0), l(nullptr), r(nullptr) {}
        void pull() {
            ans = gcd( l ? l->ans : 0, r ? r->ans : 0);
        }
    } *root;
    static node mem[N * LG * LG], *ptr;
    void modify(int pos, ll v, node *&cur, int l, int r) {
        if(!cur) cur = new (ptr++) node();
        if(l+1 == r) {
            cur->ans = v;
            return;
        }
        int m = l+(r-l)/2;
        if(pos < m)
            modify(pos, v, cur->l, l, m);
        else
            modify(pos, v, cur->r, m, r);
        cur->pull();
    }
    ll query(int ql, int qr, node *cur, int l, int r) {
        if(l >= qr || r <= ql || !cur) return 0;
        if(ql <= l && r <= qr) return cur->ans;
        int m = l+(r-l)/2;
        return gcd(query(ql, qr, cur->l, l, m), query(ql, qr, cur->r, m, r));
    }
    Segtree1d() : root(nullptr) {}
    void modify(int pos, ll v) {
        modify(pos, v, root, 0, C);
    }
    ll query(int l, int r) {
        return query(l, r, root, 0, C);
    }
};
Segtree1d::node Segtree1d::mem[N * LG * LG], *Segtree1d::ptr = mem;

struct Segtree2d {
    Segtree1d st[N << 1];
    void modify(int x, int y, ll v) {
        for(st[x+=R].modify(y, v); x>1; x>>=1)
            st[x>>1].modify(y, gcd(st[x].query(y, y+1), st[x^1].query(y, y+1)));
    }
    ll query(int l, int r, int ly, int ry) {
        ll res = 0;
        for(l+=R, r+=R; l<r; l>>=1, r>>=1) {
            if(l&1) res = gcd(res, st[l++].query(ly, ry));
            if(r&1) res = gcd(res, st[--r].query(ly, ry));
        }
        return res;
    }
} sgt;
signed main() {
    int n;
    R = nextint(), C = nextint(), n = nextint();
    vector<int> ux, uy;
    vector<tuple<int,int,int,int,int,ll>> Q(n);
    for(auto &[t, x1, y1, x2, y2, k]: Q) {
        t = nextint();
        if(t == 1) {
            x1 = nextint();
            y1 = nextint();
            k = nextll();
            ux.pb(x1);
            uy.pb(y1);
        } else {
            x1 = nextint();
            y1 = nextint();
            x2 = nextint();
            y2 = nextint();
            if(x1 > x2) swap(x1, x2);
            if(y1 > y2) swap(y1, y2);
            ++x2, ++y2;
        }
    }
    sort_uni(ux), sort_uni(uy);
    R = ux.size(), C = uy.size();
    FastOut ouf;
    for(auto &[t, x1, y1, x2, y2, k]: Q) {
        if(t == 1) {
            int x = get_pos(ux, x1);
            int y = get_pos(uy, y1);
            sgt.modify(x, y, k);
        } else {
            x1 = get_pos(ux, x1);
            x2 = get_pos(ux, x2);
            y1 = get_pos(uy, y1);
            y2 = get_pos(uy, y2);
            ouf.writeln(sgt.query(x1, x2, y1, y2));
        }
    }
}
