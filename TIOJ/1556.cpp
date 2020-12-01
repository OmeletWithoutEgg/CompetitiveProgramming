#pragma g++ optimize("O3")
#pragma loop_opt(on)
#include <cstdio>
typedef long long ll;
signed main() {
    ll n,ans = 0;
    scanf("%lld", &n);
    for(ll i = 1, j, d; i <= n; i = j) {
        d = n/i;
        j = n/d+1;
        ans += (j-i) * d;
    }
    printf("%lld\n", ans-n);
}
