//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \\#################\\
//   \\#################\\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.

#pragma gcc optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<':'<<(x)<<'\n')
#define mkp make_pair
#define pb emplace_back
#define ff first
#define ss second
#define siz(v) (ll(v.size()))
#define all(v) begin(v),end(v)
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define rep(i,n) for(int i=0;i<(n);i++)
#define mid (l+(r-l>>1))

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
constexpr long double PI = acos(-1),eps = 1e-8;
constexpr ll N = 200100, INF = 1e18, MOD = 1000000007;

ll n,q,ql,v[N*8];
struct {
    ll b[N];
    ll qry(ll p){ll res=0;for(;p;p-=p&-p)res+=b[p];return res;}
    void add(ll p){for(;p<=n;p+=p&-p)++b[p];}
    void sub(ll p){for(;p<=n;p+=p&-p)--b[p];}
} BIT;
// 0 = query+, 1 = query-, 2 = add, 3 = del
struct Query{
    ll type;
    ll args[3];
    ll id;
    /*friend ostream& operator<<(ostream &O,Query &q){
        if(q.type == 0) return O<<"query+, "<<q.args[0]<<':'<<q.args[1]<<','<<q.args[2]<<'\n';
        if(q.type == 1) return O<<"query-, "<<q.args[0]<<':'<<q.args[1]<<','<<q.args[2]<<'\n';
        if(q.type == 2) return O<<"add num at "<<q.args[0]<<" with "<<q.args[1]<<'\n';
        if(q.type == 3) return O<<"del num at "<<q.args[0]<<" with "<<q.args[1]<<'\n';
    }*/
} Q[N*8];
vector<ll> ans;
void merges(int l,int m,int r){
    int i = l, j = m;
    vector<ll> tmp;
    //cout << "[" << l << ',' << r << ')' << '\n';
    auto LESS = [](int a,int b){return Q[a].args[0]!=Q[b].args[0] ? Q[a].args[0]<Q[b].args[0] : a<b;};
    while(i<m || j<r){
        if((j==r) || (i<m && LESS(v[i],v[j]))){
            auto &q = Q[v[i]];
            if(q.type == 2) BIT.add(q.args[1]);
            if(q.type == 3) BIT.sub(q.args[1]);
            tmp.push_back(v[i++]);
        }else {
            auto &q = Q[v[j]];
            if(q.type == 0) ans[q.id] += BIT.qry(q.args[2]) - BIT.qry(q.args[1]);
            if(q.type == 1) ans[q.id] -= BIT.qry(q.args[2]) - BIT.qry(q.args[1]);
            tmp.push_back(v[j++]);
            //for(int i = 1; i <= n; i++) cout << BIT.qry(i)-BIT.qry(i-1) << " \n"[i==n];
        }
    }
    for(int i = l; i < m; i++){
        auto &q = Q[v[i]];
        if(q.type == 2) BIT.sub(q.args[1]);
        if(q.type == 3) BIT.add(q.args[1]);
    }
    for(int i = l; i < r; i++) v[i] = tmp[i-l];
    //for(int i = l; i < r; i++) cout << Q[v[i]];
}
void CDQ(int l,int r){
    if(l+1 == r) return;
    int m = l+(r-l>>1);
    CDQ(l,m),CDQ(m,r);
    merges(l,m,r);
}
ll a,ida[N],b[N];
signed main(){
    cin >> n >> q;
    for(int i = 1; i <= n; i++) cin >> a, ida[a] = i;
    for(int i = 1; i <= n; i++) cin >> b[i], b[i] = ida[b[i]], Q[ql++] = {2,i,b[i]};
    // 1:a<=x_i<=b, l<=i<=r
    REP(_,0,q){
        ll op;
        cin >> op;
        if(op == 1){
            ll La,Ra,Lb,Rb;
            cin >> La >> Ra >> Lb >> Rb;
            Q[ql++] = {1,Lb-1,La-1,Ra,ans.size()};
            Q[ql++] = {0,Rb,La-1,Ra,ans.size()};
            ans.emplace_back();
        }else if(op == 2){
            ll x,y;
            cin >> x >> y;
            Q[ql++] = {3,x,b[x]};
            Q[ql++] = {3,y,b[y]};
            swap(b[x],b[y]);
            Q[ql++] = {2,x,b[x]};
            Q[ql++] = {2,y,b[y]};
        }
    }
    //for(int i = 0; i < ql; i++) cout << Q[i];
    iota(v,v+ql,0);
    CDQ(0,ql);
    for(ll a:ans) cout << a << '\n';
}

