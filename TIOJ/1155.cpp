#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    priority_queue<double, vector<double>, greater<double>> pq;
    int n;
    double v;
    char c;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> c >> v, pq.push(v);
    double ans = 0;
    while(pq.size() >= 2) {
        double a = pq.top(); pq.pop();
        double b = pq.top(); pq.pop();
        double c = a+b;
        pq.push(c);
        ans += c;
    }
    ans = floor(ans*100+0.5) / 100;
    cout << fixed << setprecision(2) << ans << '\n';
}
