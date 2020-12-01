#pragma gcc optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#include <ext/rope>
#define pb emplace_back
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define ff first
#define ss second

using namespace std;
typedef long long ll;
const ll N = 20000, MOD = 1000007;
typedef pair<ll,ll> pll;

ll n;
pll v[N+1];
struct {
    ll b[N+1];
    void add(int pos,ll d){for(;pos<=N;pos+=pos&-pos) b[pos]+=d;}
    ll qry(int pos){ll res=0; for(;pos;pos-=pos&-pos) res+=b[pos]; return res;}
} BIT, CNT;
inline ll query(int pos){
    // count[pos]*pos - pre[pos] + (pre[N]-pre[pos])-(count[N]-count[pos])*pos
    return BIT.qry(N) - BIT.qry(pos)*2 + (CNT.qry(pos)*2 - CNT.qry(N))*pos;
}
inline void modify(int pos){BIT.add(pos,pos), CNT.add(pos,1);}
inline void undo(int pos){BIT.add(pos,-pos), CNT.add(pos,-1);}
void solve(){
    cin >> n;
    REP(i,0,n) cin >> v[i].ff >> v[i].ss;
    sort(v,v+n);
    ll ans = 0;
    REP(i,0,n){
        ans += v[i].ff*query(v[i].ss);
        modify(v[i].ss);
    }
    REP(i,0,n) undo(v[i].ss);
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    int t; cin >> t; while(t--) solve();
}

