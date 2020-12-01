#include <bits/stdc++.h>
#define mid (l+(r-l>>1))
#define mem(v,x) memset(v,x,sizeof v)
#define debug(x) (cerr<<#x<<" = "<<x<<'\n')
#define as(s) if(!(s))

using namespace std;
const int N = 800025;

int n,L[N],R[N];
struct segTree {
    int mx[N<<2];
    int to[N<<2],add[N<<2];
    void init(){mem(to,-1),mem(add,0),mem(mx,0);}
    void upd(int i,int k) {
        mx[i] = max(mx[i], k);
        to[i] = max(to[i], k);
    }
    void push(int i) {
        as(to[i]==-1 || add[i]==0) debug(i);
        if(add[i]) mx[i<<1]+=add[i], mx[i<<1|1]+=add[i], add[i<<1]+=add[i], add[i<<1|1]+=add[i], add[i]=0;
        if(~to[i]) upd(i<<1,to[i]), upd(i<<1|1,to[i]), to[i]=-1;
        assert(to[i]==-1 && add[i]==0);
    }
    void pull(int i) {
        mx[i]=max(mx[i<<1],mx[i<<1|1]);
    }
    void lift(int ql,int qr,int l=0,int r=n,int i=1) {
        if(l >= qr || r <= ql) return;
        push(i);
        if(ql <= l && r <= qr) return mx[i]++, add[i]++, void();
        lift(ql,qr,l,mid,i<<1), lift(ql,qr,mid,r,i<<1|1);
        pull(i);
    }
    void edit(int ql,int qr,int k,int l=0,int r=n,int i=1) {
        if(l >= qr || r <= ql) return;
       // debug(l), debug(r);
        push(i);
        if(ql <= l && r <= qr) return upd(i,k), void();
        edit(ql,qr,k,l,mid,i<<1), edit(ql,qr,k,mid,r,i<<1|1);
        pull(i);
    }
    int query(int ql,int qr,int l=0,int r=n,int i=1) {
        if(l >= qr || r <= ql) return 0;
        push(i);
        if(ql <= l && r <= qr) return mx[i];
        return max(query(ql,qr,l,mid,i<<1), query(ql,qr,mid,r,i<<1|1));
    }
} seg;
signed main() {
    int ans = 0;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> L[i] >> R[i];
    seg.init();
    for(int i = 0; i < n; i++) {
        seg.lift(L[i],R[i]+1);
        int dp = seg.query(0,R[i]+1);
        seg.edit(R[i]+1,n,dp);
        //for(int i = 0; i < n; i++) cout << seg.query(i,i+1) << ' '; cout << '\n';
        ans = max(ans, dp);
    }
    cout << ans << '\n';
}
