#include <cstdio>

long long calc(int x) {
    // "0" in 0 + #["0" in z for z \in [1, x]]
    if(x == -1) return 0;
    long long ans = 1;
    for(long long p = 1; p*10 <= x; p *= 10) {
        int a = x%p, b = x/p;
        if(b%10 == 0)
            ans += (b/10-1)*p+a+1;
        else
            ans += b/10*p;
    }
    return ans;
}
int main() {
    int l, r;
    while(~scanf("%d%d", &l, &r)) {
        if(l > r) {
            int t = l;
            l = r;
            r = t;
        }
        printf("%lld\n", calc(r) - calc(l-1));
    }
    return 0;
}
