#include <bits/stdc++.h>
// challenge: not using namespace std

struct Segtree {
    struct tag {
        int64_t a, b; // ax + b
        tag & operator+=(const tag &rhs) {
            // return rhs(*this(x))
            a *= rhs.a;
            b = rhs.a * b + rhs.b;
            return *this;
        }
        tag() : a(1), b(0) {}
        tag(int a, int b) : a(a), b(b) {}
    };
    struct node {
        int64_t mx, sum, len;
        node(int c = 0) : mx(c), sum(c), len(1) {}
        friend node operator+(const node &lhs, const node &rhs) {
            node c;
            c.mx = std::max(lhs.mx, rhs.mx);
            c.sum = lhs.sum + rhs.sum;
            c.len = lhs.len + rhs.len;
            return c;
        }
        node & operator+=(const tag &t) {
            mx = t.a * mx + t.b;
            sum = t.a * sum + t.b * len;
            return *this;
        }
    };

    std::vector<node> st;
    std::vector<tag> lz;
    size_t sz;
    Segtree(const std::vector<int> &a) : st(a.size()*2), lz(a.size()), sz(a.size()) {
        for(size_t i = 0; i < sz; i++) st[i + sz] = node(a[i]);
        for(size_t i = sz-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
    }
    void pull(size_t p) {
        for(; p>1; p>>=1)
            st[p>>1] = st[p] + st[p^1], st[p>>1] += lz[p>>1];
    }
    void upd(size_t p, tag t) {
        st[p] += t;
        if(p < sz) lz[p] += t;
    }
    void push(size_t p) {
        for(int h = std::__lg(sz); h >= 0; h--) {
            size_t i = p >> h;
            upd(i, lz[i>>1]);
            upd(i^1, lz[i>>1]);
            lz[i>>1] = tag();
        }
    }
    void add(size_t l, size_t r, tag t) {
        size_t tl = l, tr = r;
        push(l + sz), push(r - 1 + sz);
        for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if(l & 1) upd(l++, t);
            if(r & 1) upd(--r, t);
        }
        pull(tl + sz), pull(tr - 1 + sz);
    }
    node query(size_t l, size_t r) {
        node res;
        res.len = res.sum = res.mx = 0;
        push(l + sz), push(r - 1 + sz);
        for(l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if(l & 1) res = res + st[l++];
            if(r & 1) res = res + st[--r];
        }
        return res;
    }
};

signed main() {
    std::ios_base::sync_with_stdio(0), std::cin.tie(0);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for(int i = 0; i < n; i++)
        std::cin >> a[i];
    Segtree sgt(a);
    while(q--) {
        int k, l, r;
        std::cin >> k >> l >> r;
        --l;
        if(k == 1) {
            int x;
            std::cin >> x;
            sgt.add(l, r, Segtree::tag(0, x));
        } else if(k == 2) {
            int x;
            std::cin >> x;
            sgt.add(l, r, Segtree::tag(1, x));
        } else if(k == 3) {
            std::cout << sgt.query(l, r).sum << '\n';
        } else if(k == 4) {
            std::cout << sgt.query(l, r).mx << '\n';
        }
    }

}
