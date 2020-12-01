#include <bits/stdc++.h>

using namespace std;
const int N = 10025;
typedef long double ld;

int a[N],b[N],c[N],n;
inline ld f(int i, ld x) { return a[i]*x*x + b[i]*x + c[i]; }
int ori(ld x) {
    int mn = 0;
    for(int i = 1; i < n; i++) if(f(mn, x) > f(i, x)) mn = i;
    ld dif = -b[mn] / (2.0*a[mn]) - x;
    return abs(dif) < 1e-8 ? 0 : dif/abs(dif);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) cin >> a[i] >> b[i] >> c[i];
    ld ans = 0, step = 1e18;
    while(step >= 1e-8) {
        int r = ori(ans);
        if(r == 0) break;
        ans = max<ld>(0, ans + r * step);
        step /= 2;
    }
    cout << fixed << setprecision(6) << ans << '\n';
}
