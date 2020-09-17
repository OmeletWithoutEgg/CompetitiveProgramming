#include <bits/stdc++.h>
using namespace std;
const int N  = 1e5 + 5;
int deg[N] = {};
int main() {
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int a, b, s, m, k;
    int u, v, w;
    cin >> a >> b >> s >> m >> k;
    for (int i = 1; i <= k; i++) {
        cin >> u >> v >> w;
        deg[u]++, deg[a + v]++;
    }
    int cnt = 0;
    for (int i = 1; i <= a + b; i++)
        cnt += (deg[i] & 1);
    if (cnt == 0) cout << 1 << '\n';
    else cout << cnt / 2 << '\n';
    return 0;
}
