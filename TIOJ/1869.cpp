#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<" = "<<(x)<<'\n')
#define all(v) begin(v),end(v)
#define pb emplace_back
#define ff first
#define ss second
#define mid (l+(r-l>>1))

using namespace std;
typedef int ll;
typedef long double ld;
typedef pair<ll,ll> pll;
constexpr long double PI = acos(-1),eps = 1e-8;
constexpr ll N = 1525;//, INF = 1e18, MOD = 1000000007, K = 300;

ll b[N][N],n,c;
void add(int x,int y,ll d){
    for(;x<=n;x+=x&-x) for(int p=y;p<=n;p+=p&-p) b[x][p] += d;
}
ll qry(int x,int y){
    ll res = 0;
    for(;x;x-=x&-x) for(int p=y;p;p-=p&-p) res += b[x][p];
    return res;
}
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n;
    while(cin >> c) {
        if(c == 1) {
            int x,y,z;
            cin >> x >> y >> z;
            add(x+1,y+1,z);
        }else if(c == 2) {
            int x1,y1,x2,y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << qry(x2+1,y2+1) - qry(x1,y2+1) - qry(x2+1,y1) + qry(x1,y1) << '\n';
        }
    }
}
