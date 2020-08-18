#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>

typedef long long ll;

const int L = 10000;
int solve() {
    int x, y, z;
    scanf("%d%d%d", &x, &y, &z);
    if(x == 0 && y == 0) return -1;
    if(x > L) return 0;
    if(!z) return !x;
    return (L-x) * ll(z) / (ll(z)*y + L) + 1;
    /*
    X + (Y+T)V > min(10000, TZ)
    X + (Y+T)V > TZ
    XZ + (YZ+TZ)V > TZZ
    consider T == 10000/Z and T == 0
    V > (10000-X)Z / (ZY+10000)
    X + YV > 0
    */
}
signed main() {
    int t;
    scanf("%d", &t);
    while(t--) printf("%d\n", solve());
    return 0;
}
