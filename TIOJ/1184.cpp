#include <cstdio>
#include <algorithm>

struct item{
    int price, cnt;
    bool operator<(const item &rhs) const {return price<rhs.price;}
} v[201];
inline void solve() {
    int n, m, ans = 0;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; i++) scanf("%d%d", &v[i].price, &v[i].cnt);
    std::sort(v,v+n);
    for(int i = 0; i < n; i++) {
        int t = std::min(m, v[i].cnt);
        ans += v[i].price * t;
        m -= t;
    }
    if(m) puts("so sad");
    else printf("%d\n", ans);
}
signed main() {
    int t;
    scanf("%d", &t);
    while(t--) solve();
}
