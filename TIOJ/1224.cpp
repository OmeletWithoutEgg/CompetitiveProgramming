#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<" = "<<x<<'\n')

using namespace std;
constexpr int N = 1002525;

int seg[N << 2], laz[N << 2], n, ql, qr, k, id[N];
struct OP{
    int x, d, u, v;
} Q[N];
void modify(int i=1,int l=0,int r=N){
    //if(l >= qr || r <= ql) return;
    if(ql <= l && r <= qr) laz[i] += k;
    else {
        int mid = l+(r-l>>1);
        if(ql < mid) modify(i<<1,l,mid);
        if(qr > mid) modify(i<<1|1,mid,r);
    }
    seg[i] = laz[i] ? r-l : seg[i<<1]+seg[i<<1|1];
}
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    for(int i = 0, L, R, D, U; i < n; i++) {
        cin >> Q[i*2].x >> Q[i*2+1].x >> D >> U;
        Q[i*2].d = Q[i*2+1].d = D, Q[i*2].u = Q[i*2+1].u = U;
        Q[i*2].v = 1, Q[i*2+1].v = -1;
    }
    n <<= 1;
    iota(id,id+n,0);
    sort(id,id+n,[](int a,int b){return Q[a].x < Q[b].x;});
    int lastX = 0;
    int64_t res = 0;
    for(int i = 0; i < n; i++) {
        auto &q = Q[id[i]];
        res += int64_t(q.x - lastX) * seg[1];
        ql = q.d, qr = q.u, k = q.v;
        modify();
        lastX = q.x;
    }
    cout << res << '\n';
}
