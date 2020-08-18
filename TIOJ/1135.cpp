#include <cstdio>
#include <tuple>

typedef long long ll;
std::tuple<ll,ll,ll> extgcd(ll a, ll b) {
    if(!b) return {1, 0, a};
    auto [x, y, g] = extgcd(b, a%b);
    return {y, x-(a/b)*y, g};
}
void solve() {
    ll a, b, c, k;
    scanf("%lld%lld%lld%lld", &a, &b, &c, &k);
    ll m = 1LL<<k, dif = (b-a+m)%m;
    auto [t, s, g] = extgcd(c, m);
    if(dif % g) return puts("FOREVER"), void();
    dif /= g, c /= g, m /= g;
    t = (t*dif%m+m)%m;
    printf("%lld\n", t);
}
signed main() {
    int t;
    scanf("%d", &t);
    while(t--) solve();
}
