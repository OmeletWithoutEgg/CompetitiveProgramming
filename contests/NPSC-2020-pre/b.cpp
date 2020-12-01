#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> d(n);
    for(int i = 0; i < n; i++) cin >> d[i];
    sort(d.begin(), d.end());
    long long sum = 0, ans = 0;
    for(int i = 0; i < n; i++) {
        ans += 1LL * d[i] * i - sum;
        sum += d[i];
    }
    cout << ans << '\n';
}
