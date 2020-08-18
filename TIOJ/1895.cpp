#include "lib1895.h"

const int N = 2000025;
struct Segtree {
    int mx[N<<1],mn[N<<1],n;
    void mxeq(int p, int d) {
        if(mx[p] == -1 || mx[p] < d) mx[p] = d;
        if(mn[p] != -1 && mx[p] > mn[p]) mn[p] = -1;
    }
    void mneq(int p, int d) {
        if(mn[p] == -1 || mn[p] > d) mn[p] = d;
        if(mx[p] != -1 && mx[p] > mn[p]) mx[p] = -1;
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p>>h;
            if(mx[i>>1] != -1) {
                mxeq(i, mx[i>>1]);
                mxeq(i^1, mx[i>>1]);
            }
            if(mn[i>>1] != -1) {
                mneq(i, mn[i>>1]);
                mneq(i^1, mn[i>>1]);
            }
        }
    }
    void add(int l, int r, int d) {
        push(l+n), push(r-1+n);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) mxeq(l++, d);
            if(r&1) mxeq(--r, d);
        }
    }
    void rem(int l, int r, int d) {
        push(l+n), push(r-1+n);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) mneq(l++, d);
            if(r&1) mneq(--r, d);
        }
    }
    void pushdown(int res[]) {
        for(int i = 1; i < n; i++) {
            if(mx[i] != -1) {
                mxeq(i<<1, mx[i]);
                mxeq(i<<1|1, mx[i]);
            }
            if(mn[i] != -1) {
                mneq(i<<1, mn[i]);
                mneq(i<<1|1, mn[i]);
            }
        }
        //for(int i = 0; i < n; i++) res[i] =
    }
};
void buildWall(int n, int k, int op[], int l[], int r[], int h[], int ans[]) {
}
