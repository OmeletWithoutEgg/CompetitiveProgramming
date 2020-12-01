struct segtree {
    ll mx[N<<1],lz[N],n = N;
    void go(int p, ll d) {
        mx[p] += d;
        if(p<n) lz[p] += d;
    }
    void pull(int p) {
        for(; p > 1; p >>= 1) mx[p>>1] = max(mx[p],mx[p^1])+lz[p>>1];
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p>>h;
            if(!lz[i>>1]) continue;
            go(i, lz[i>>1]);
            go(i^1, lz[i>>1]);
            lz[i>>1] = 0;
        }
    }
    void add(int l, int r, ll d) {
        int L = l, R = r;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) go(l++, d);
            if(r&1) go(--r, d);
        }
        pull(L+n), pull(R-1+n);
    }
    ll query(int l, int r) {
        push(l+n), push(r-1+n);
        ll res = -INF;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res = max(res, mx[l++]);
            if(r&1) res = max(res, mx[--r]);
        }
        return res;
    }
} sgt;
