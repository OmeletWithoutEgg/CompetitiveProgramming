#include <bits/stdc++.h>
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}

using namespace std;
template <typename T> using max_heap = priority_queue<T, vector<T>, less<T>>;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> t(n), s(n), d(n);
    for (int i = 1; i < n; i++) cin >> t[i];
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> d[i];
    auto go = [&](int p, int t) {
        vector<int> cur = s;
        max_heap<pair<int,int>> pq;
        for (int i = 0; i < p; i++) pq.emplace(cur[i], i);
        long long ans = 0;
        for (int i = 0; i < t; i++) {
            auto [_, id] = pq.top(); pq.pop();
            ans += cur[id];
            cur[id] = max(0, cur[id] - d[id]);
            pq.emplace(cur[id], id);
        }
        return ans;
    };
    long long best = 0;
    for (int i = 0; i < n; i++) {
        if (i) m -= t[i];
        if (m <= 0) break;
        best = max(best, go(i+1, m));
    }
    cout << best << '\n';
    debug(best);
}
