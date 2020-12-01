#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
const int N = 100025;

unordered_map<int,rbt<int>> mp;
struct zkw{
    struct node {
        int val,win,isZero;
        node() : val(-1), win(0), isZero(0) {}
        node(int x) : val(x), win(1), isZero(x==0) {}
        inline friend node operator+(const node &a, const node &b) {
            node r;
            if(a.val == b.val) r.val=a.val, r.win=a.win+b.win;
            else if(a.win>b.win) r.val=a.val, r.win=a.win-b.win;
            else r.val=b.val, r.win=b.win-a.win;
            r.isZero = a.isZero&&b.isZero;
            return r;
        }
        friend void pr(const node &p) {
            cerr << p.val << ',' << p.win << '\n';
        }
    } seg[N<<1];
    int n;
    inline void init(int sz, int v[]) {
        n = sz;
        for(int i = 0; i < n; i++) seg[i+n] = node(v[i]), mp[v[i]].insert(i);
        for(int i = n-1; i >= 1; i--) seg[i] = seg[i<<1]+seg[i<<1|1];
    }
    void pull(int p) {
        for(; p; p>>=1) seg[p>>1] = seg[p]+seg[p^1];
    }
    inline void edit(int p, int k) {
        p+=n;
        mp[seg[p].val].erase(p-n);
        seg[p].val = k;
        seg[p].isZero = (seg[p].val == 0);
        mp[seg[p].val].insert(p-n);
        pull(p);
    }
    inline void brute(int i,int k) {
        if(seg[i].isZero) return;
        if(i < n) brute(i<<1,k), brute(i<<1|1,k), seg[i] = seg[i<<1]+seg[i<<1|1];
        //else edit(i-n,seg[i].val/k);
        else {
            mp[seg[i].val].erase(i-n);
            seg[i].val /= k;
            seg[i].isZero = (seg[i].val == 0);
            mp[seg[i].val].insert(i-n);
        }
    }
    inline void div(int l,int r,int k) {
        int L = l, R = r;
        for(l+=n,r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) brute(l++,k);
            if(r&1) brute(--r,k);
        }
        pull(L+n), pull(R-1+n);
    }
    inline int winner(int l,int r) {
        node res = node();
        for(l+=n,r+=n; l<r; l>>=1, r>>=1) {
            //debug(l), debug(r);
            if(l&1) res = res+seg[l++];
            if(r&1) res = res+seg[--r];
        }
        return res.val;
    }
} sgt;
int n,q,v[N];
signed main() {
    mp.reserve(N);
    mp.max_load_factor(0.25);
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> v[i];
    sgt.init(n,v);
    for(int i = 0; i < q; i++) {
        int c,x,v,l,r;
        cin >> c;
        if(c == 1) {
            cin >> x >> v, --x;
            sgt.edit(x,v);
        }else if(c == 2) {
            cin >> l >> r >> v, --l;
            if(v!=1) sgt.div(l,r,v);
        }else if(c == 3) {
            cin >> l >> r, --l;
            v = sgt.winner(l,r);
            int cnt = mp[v].order_of_key(r) - mp[v].order_of_key(l);
            if(cnt > (r-l)/2) cout << v << '\n';
            else cout << -1 << '\n';
        }
    }
}
