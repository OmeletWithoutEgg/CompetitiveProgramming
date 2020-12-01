#include <bits/stdc++.h>
#define REP(i,l,r) for(ll i=(l);i<(r);i++)

using namespace std;
typedef long long ll;
const ll N = 50000;

ll n,m,q,l,r;
ll k,v[N+1] = {},u[N+1] = {};
struct Query{
    ll l,r,id;
    ll k;
    Query(ll l,ll r,ll id,ll k):l(l),r(r),id(id),k(k){}
};
vector<Query> Q[600];
bitset<100001> ans;
ll num[N+1],cnt[N+1],mx;
void upd(ll x,ll d){
    num[cnt[x]]--;
    cnt[x] += d;
    num[cnt[x]]++;
    if(num[mx] == 0) --mx;
    if(mx < cnt[x]) mx = cnt[x];
}
signed main(){
    scanf("%lld%lld",&n,&q);
    ll K = q>10000 ? 400 : 128;
    REP(i,1,n+1) scanf("%lld",v+i), u[i] = v[i];
    REP(i,0,q) scanf("%lld%lld%lld",&l,&r,&k), Q[l/K].emplace_back(l,r,i,k);

    sort(u,u+n), m = unique(u,u+n)-u;
    REP(i,1,n+1) v[i] = lower_bound(u,u+m,v[i])-u;

    l = r = 1, num[0] = n, upd(v[1], 1);
    for(int i=0;i<N/K;i++){
        sort(Q[i].begin(),Q[i].end(),[i](Query &a,Query &b){return (a.r<b.r)^(i&1);});
        for(auto q:Q[i]){
            while(r<q.r) upd(v[++r], 1);
            while(l>q.l) upd(v[--l], 1);
            while(r>q.r) upd(v[r--],-1);
            while(l<q.l) upd(v[l++],-1);
            //cout << "mx:" << mx << '\n';
            if((q.r-q.l+1) <= mx*q.k) ans[q.id] = true;
        }
    }
    REP(i,0,q) puts(ans[i]?"Yes":"No");
}
