#pragma g++ optimize("Ofast")
#include <bits/stdc++.h>
#define pb emplace_back
#define get_pos(u,x) (lower_bound(begin(u),end(u),x) - begin(u))
using namespace std;
const int N = 1000025;

struct Segtree {
    int n;
    vector<int> mx, lz;
    void init(int v[], int _n) {
        n = _n;
        mx.resize(n*2), lz.resize(n);
        for(int i = 0; i < n; i++) mx[i+n] = v[i], lz[i] = 0;
        for(int i = n-1; i > 0; i--) mx[i] = max(mx[i<<1], mx[i<<1|1]);
    }
    void upd(int p, int d) {
        mx[p] += d;
        if(p < n) lz[p] += d;
    }
    void pull(int p) {
        for(; p>1; p>>=1) mx[p>>1] = max(mx[p],mx[p^1]) + lz[p>>1];
    }
    void push(int p) {
        for(int h = __lg(n); h >= 0; h--) {
            int i = p>>h;
            if(!lz[i>>1]) continue;
            upd(i,lz[i>>1]);
            upd(i^1,lz[i>>1]);
            lz[i>>1] = 0;
        }
    }
    void add(int l, int r, int d) {
        int L = l, R = r;
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) upd(l++, d);
            if(r&1) upd(--r, d);
        }
        pull(L+n), pull(R-1+n);
    }
    int query(int l, int r) {
        int res = 0;
        push(l+n), push(r-1+n);
        for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
            if(l&1) res = max(res, mx[l++]);
            if(r&1) res = max(res, mx[--r]);
        }
        return res;
    }
    /*void dbg() {
        cout << "-------\n";
        for(int i = 0; i < 10; i++) {
            push(i+N);
            cout << mx[i+N] << ' ';
        }
        cout << '\n';
    }*/
} sgt;

int S[N];
vector<int> countScans(vector<int> A, vector<int> X, vector<int> V) {
    int n = A.size(), q = X.size();
    vector<pair<long long,int>> u;
    for(int i = 0; i < n; i++) u.pb(1LL * A[i] * N + i, i);
    for(int i = 0; i < q; i++) u.pb(1LL * V[i] * N + X[i], i+n);
    sort(u.begin(), u.end());
    long long last = u.front().first;
    int j = 0;
    for(auto [val, id]: u) {
        if(val != last) ++j;
        if(id < n)
            A[id] = j;
        else
            V[id-n] = j;
        last = val;
    }
    ++j;
    vector<int> Q(q);
    /*for(int i = 0; i < n; i++) {
        sgt.add(A[i], A[i]+1, i);
        sgt.add(A[i]+1, j, -1);
    }*/
    for(int i = 0; i < n; i++) --S[A[i]+1];
    for(int i = 1; i < N; i++) S[i] += S[i-1];
    for(int i = 0; i < n; i++) S[A[i]] += i;
    sgt.init(S, N);

    for(int i = 0; i < q; i++) {
        int x = X[i];
        sgt.add(A[x],A[x]+1, -x);
        sgt.add(A[x]+1, N, 1);
        A[x] = V[i];
        sgt.add(A[x],A[x]+1, x);
        sgt.add(A[x]+1, N, -1);
        //sgt.dbg();
        Q[i] = sgt.mx[1];
    }
    return Q;
}

/*
*/
