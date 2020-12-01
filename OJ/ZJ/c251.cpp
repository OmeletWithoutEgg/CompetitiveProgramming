#include <bits/stdc++.h>
#define mid (l+(r-l>>1))

using namespace std;

int n,q,l,r,k,op,p;
unsigned seg[1<<17];
unsigned laz[1<<17];
void pull(int i) { seg[i]=seg[i<<1]|seg[i<<1|1]; }
void upd(int i,int x) { seg[i]=laz[i]=x; }
void push(int i) { if(~laz[i]) upd(i<<1,laz[i]),upd(i<<1|1,laz[i]),laz[i]=~0; }
unsigned query(int ql,int qr,int i=1,int l=1,int r=n) {
    push(i);
    if(l > qr || r < ql || !seg[i]) return 0;
    if(ql <= l && r <= qr) return seg[i];
    return query(ql,qr,i<<1,l,mid)|query(ql,qr,i<<1|1,mid+1,r);
}
void modify(int ml,int mr,unsigned k,int i=1,int l=1,int r=n) {
    push(i);
    if(l > mr || r < ml) return;
    if(ml <= l && r <= mr) return upd(i,k),void();
    modify(ml,mr,k,i<<1,l,mid),modify(ml,mr,k,i<<1|1,mid+1,r);
    pull(i);
}
void init() {upd(1,0);}

signed main() {
    //ios_base::sync_with_stdio(0),cin.tie(0);
    int t;
    scanf("%d",&t);
    while(t--) {
        scanf("%d%d",&n,&q);
        init();
        for(int i = 0; i < q; i++) {
            scanf("%d",&op);
            if(op) scanf("%d%d%d",&l,&r,&p), modify(l,r,p?(1LL<<p-1):0);
            else scanf("%d%d",&l,&r),printf("%d\n",__builtin_popcount(query(l,r)));
        }
    }
}
/*
2
3 3
0 1 3
1 1 2 1
*/
