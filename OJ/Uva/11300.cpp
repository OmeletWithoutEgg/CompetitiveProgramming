#pragma gcc optimze("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<':'<<x<<'\n')
#define mkp make_pair
#define pb emplace_back
#define ff first
#define ss second
#define siz(v) (ll(v.size()))
#define all(v) begin(v),end(v)
#define rall(v) rbegin(v),rend(v)
#define REP(i,l,r) for(int i=(l);i<(r);i++)
#define PER(i,l,r) for(int i=(r)-1;i>=(l);i--)
#define mid (l+(r-l>>1))

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
constexpr long double PI = acos(-1),eps = 1e-8;
constexpr ll N = 1000000, M = 10000, INF = 1e18, MOD = 1000000007;

ll n,a[N] = {},res,avg = 0,x;
signed main(){
    while(~scanf("%lld",&n)){
        avg = res = 0;
        REP(i,0,n) scanf("%lld",a+i), avg+=a[i];
        avg /= n;
        REP(i,0,n-1) a[i+1]+=a[i]-avg;
        //REP(i,0,n)debug(a[i]);
        nth_element(a,a+n/2,a+n);
        x = a[n/2];
        REP(i,0,n) res += abs(a[i]-x);
        printf("%lld\n",res);
    }
}

/*
3
100 100 100
4
1 2 5 4
*/
