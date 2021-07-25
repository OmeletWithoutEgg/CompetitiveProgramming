#include "jngen.h"
#include <bits/stdc++.h>

using namespace std;

complex<double> ans;
vector<pair<int,int>> polygon;
void gen(complex<double> v) {
    const int K = 1000;
    complex<double> dif(0, 0);
    for (int i = 1; i <= K; i++) {
        dif += complex<double>(i, 1);
        ans += dif * v / abs(v);
        polygon.emplace_back(ans.real(), ans.imag());
    }
    for (int i = K; i >= 1; i--) {
        dif += complex<double>(i, -1);
        ans += dif * v / abs(v);
        polygon.emplace_back(ans.real(), ans.imag());
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    int x[100], y[100];
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
    for (int i = n-1; i >= 0; i--)
        gen({ x[(i+1)%n] - x[i], y[(i+1)%n] - y[i] });
    cout << polygon.size() << '\n';
    for (auto [a, b]: polygon)
        cout << a << ' ' << b << '\n', assert(max(abs(a), abs(b)) <= 2000000000);
    // Drawer d;
    // d.polygon(polygon);
    // d.dumpSvg("jizz.svg");
}
