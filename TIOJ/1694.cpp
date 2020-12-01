#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll N = 25000, Q = 200000, K = 500;

ll n,q,v[N+1];
ll ans[Q+1];
struct Query{
    ll l,r,b,id;
} QS[Q+1];
struct {
    ll b[N+1];
    ll qry(int pos){
        ll res = 0;
        for(;pos;pos-=pos&-pos) res+=b[pos];
        return res;
    }
    void debug(){
        for(int i=1;i<=n;i++) cout << "c[" << i << "]:" << qry(i)-qry(i-1) << ", ";
        cout << "\n================================================\n";
    }
    void add(int pos,ll x){
        for(;pos<=n;pos+=pos&-pos) b[pos]+=x;
        //debug();
    }
} BIT; // 1 base
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 1;i <= n;i++) cin >> v[i];
    for(int i = 0;i < q;i++) cin >> QS[i].l >> QS[i].r, QS[i].b = QS[i].l/K, QS[i].id = i;
    sort(QS,QS+q,[](Query &a,Query &b){
        return a.b!=b.b? a.b<b.b : (a.r<b.r)^(a.b&1);
    });
    ll res = 0, l = 1, r = 1;
    BIT.add(v[1],1);
    for(int i=0;i<q;i++){
        auto &Q = QS[i];
        while(r < Q.r) r++, res += BIT.qry(n)-BIT.qry(v[r]), BIT.add(v[r],1);
        while(l > Q.l) l--, res += BIT.qry(v[l]), BIT.add(v[l],1);
        while(r > Q.r) BIT.add(v[r],-1), res -= BIT.qry(n)-BIT.qry(v[r]), r--;
        while(l < Q.l) BIT.add(v[l],-1), res -= BIT.qry(v[l]), l++;
        //cout << '\n';
        ans[Q.id] = res;
    }
    for(int i=0;i<q;i++) cout << ans[i] << '\n';
}
