#include <cstdio>

typedef long long ll;
const ll N = (1<<21)+1, MOD = 1000000007;

ll frac[N] = {1},t,n;
ll inv(ll e){
    ll r = 1, p = MOD-2; while(p)(p&1)&&(r=r*e%MOD),e=e*e%MOD,p>>=1; return r;
}
signed main() {
    for(int i=1;i<=N;i++) frac[i] = frac[i-1]*i%MOD;
    scanf("%lld",&t);
    while(t--) scanf("%lld",&n),printf("%lld\n",frac[n<<1]*inv(frac[n+1])%MOD*inv(frac[n])%MOD);
}
