#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>

typedef unsigned long long ll;
const ll MOD = 1LL<<32;
void mul(ll a[2][2], ll b[2][2]) {
    ll t[2][2] = {};
    for(int i = 0; i < 2; i++) for(register int j = 0; j < 2; j++) for(int k = 0; k < 2; k++) t[i][j]+=a[i][k]*b[k][j]%MOD;
    for(int i = 0; i < 2; i++) for(register int j = 0; j < 2; j++) a[i][j] = t[i][j] % MOD;
}
signed main() {
    ll a,b,x,y;
    int n;
    while(scanf("%d",&n), n>=0) {
        scanf("%u%u%u%u", &a, &b, &x, &y);
        ll e[2][2] = {{0,1},{x,y}}, r[2][2] = {{1,0},{0,1}};
        while(n) {
            if(n&1) mul(r,e);
            mul(e,e), n>>=1;
        }
        ll ret = (a*r[0][0]+b*r[0][1])%MOD;
        printf("%u\n", ret);
    }
}

