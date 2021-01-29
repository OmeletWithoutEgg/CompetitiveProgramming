#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local

using namespace std;
const int N = 200025, inf = 1e9;
const int64_t INF = 1e18;

struct Segtree {
    struct tag {
        int64_t a;
        int64_t b;
        // x := min(x+a, b)
        tag() : a(0), b(INF) {}
        tag(int64_t a, int64_t b) : a(a), b(b) {}
        tag & operator+=(const tag &rhs) {
            // min(min(x+a+c, b+c), d);
            a += rhs.a;
            b = min(rhs.b, b+rhs.a);
            return *this;
        }
        bool operator==(tag t) {
            return a==t.a && b==t.b;
        }
    } lz[N<<2];
    struct node {
        int64_t mx, smx;
        int len, mxcnt;
        int64_t sum;
        node() : mx(-INF), smx(-INF), len(0), mxcnt(0), sum(0) {}
        node(int x) : mx(x), smx(-INF), len(1), mxcnt(1), sum(x) {}
        friend node operator+(const node &lhs, const node &rhs) {
            node c;
            c.mx = max(lhs.mx, rhs.mx);
            c.smx = (lhs.mx == rhs.mx ? max(lhs.smx, rhs.smx) : max({ lhs.smx, rhs.smx, min(lhs.mx, rhs.mx) }));
            c.len = lhs.len + rhs.len;
            c.mxcnt = (lhs.mx==c.mx ? lhs.mxcnt : 0) + (rhs.mx==c.mx ? rhs.mxcnt : 0);
            c.sum = lhs.sum + rhs.sum;
            assert(c.mx != c.smx);
            return c;
        }
        bool operator==(const node rhs) const {
            return mx == rhs.mx && smx == rhs.smx && len == rhs.len && mxcnt == rhs.mxcnt && sum == rhs.sum;
        }
        friend ostream & operator<<(ostream &O, node p) {
            return O << "mx = " << p.mx << "; smx = " << p.smx << "; len = " << p.len;
        }
        node & operator+=(const tag &t) {
            mx += t.a;
            smx += t.a;
            sum += t.a * len;
            assert(t.b >= smx);
            if(t.b < mx) {
                sum -= mxcnt * (mx - t.b);
                mx = t.b;
            }
            return *this;
        }
    } st[N<<2];

    void push(int p) {
        // if(lz[p] == tag()) return;
        debug("PUSH", p);
        st[p<<1] += lz[p];
        lz[p<<1] += lz[p];
        st[p<<1|1] += lz[p];
        lz[p<<1|1] += lz[p];
        lz[p] = tag();
    }
    void pull(int p) {
        debug("PULL", p);
        st[p] = st[p<<1] + st[p<<1|1];
        // debug("SAFE");
        assert(lz[p] == tag());
        // st[p] += lz[p]; // ?
    }
    void build(int a[], int l, int r, int id) {
        if(l+1 == r) {
            st[id] = node(a[l]);
        } else {
            int m = l+(r-l)/2;
            build(a, l, m, id<<1);
            build(a, m, r, id<<1|1);
            pull(id);
        }
    }
    void modify(tag t, int ql, int qr, int l, int r, int id) {
        if(r <= ql || l >= qr) return;
        if(l+1 != r) push(id);
        if(ql <= l && r <= qr && (t.b > st[id].smx + t.a)) {
            debug(lz[id].a, lz[id].b);
            // assert(lz[id] == tag());
            st[id] += t;
            lz[id] += t;
            // debug(l, r, st[id].sum);
            return;
        }
        int m = l+(r-l)/2;
        modify(t, ql, qr, l, m, id<<1);
        modify(t, ql, qr, m, r, id<<1|1);
        if(l+1 != r) pull(id);
    }
    node query(int ql, int qr, int l, int r, int id) {
        // debug(ql, qr, l, r, id);
        if(r <= ql || l >= qr) return node();
        if(l+1 != r) debug("QUERY-PUSH", l, r), push(id);
        if(ql <= l && r <= qr)
            return st[id];
        int m = l+(r-l)/2;
        return query(ql, qr, l, m, id<<1) + query(ql, qr, m, r, id<<1|1);
    }
    void pr(int n) {
        for(int i = 0; i < n; i++)
            cout << query(i, i+1, 0, n, 1).mx << ' ';
        cout << '\n';
    }
};
struct Naive {
    int64_t v[N];
    void build(int a[], int l, int r, int c) {
        for(int i = l; i < r; i++)
            v[i] = a[i];
    }
    void modify(Segtree::tag t, int l, int r, int a, int b, int c) {
        for(int i = l; i < r; i++)
            v[i] = min(v[i] + t.a, t.b);
    }
    Segtree::node query(int l, int r, int a, int b, int d) {
        Segtree::node c;
        assert(c.sum == 0 && c.mx == -INF);
        for(int i = l; i < r; i++)
            c.mx = max(c.mx, v[i]), c.sum += v[i];
        return c;
    }
    void pr(int n) {
        for(int i = 0; i < n; i++)
            cout << v[i] << ' ';
        cout << '\n';
    }
};
#ifdef NAIVE
Naive sgt;
#else
Segtree sgt;
#endif // local
int a[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> a[i];
    sgt.build(a, 0, n, 1);
    while(q--) {
        int k, l, r;
        cin >> k >> l >> r;
        --l;
        if(k == 1) {
            int x;
            cin >> x;
            sgt.modify(Segtree::tag(0, x), l, r, 0, n, 1);
        } else if(k == 2) {
            int x;
            cin >> x;
            sgt.modify(Segtree::tag(x, INF), l, r, 0, n, 1);
        } else if(k == 3) {
            cout << sgt.query(l, r, 0, n, 1).sum << '\n';
        } else if(k == 4) {
            cout << sgt.query(l, r, 0, n, 1).mx << '\n';
        } else
            throw;
        debug(q);
        // for(int i = 0; i < n; i++) cerr << sgt.query(i, i+1, 0, n, 1).mx << ' ' << sgt.query(i, i+1, 0, n, 1).sum << '\n';
        // if(q <= 3) sgt.pr(n);
    }
}
