#include <bits/stdc++.h>

using namespace std;
using ll = int64_t;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const ll INF = 1e18;
const int maxn = 100025;
const int C = 8000;

bool dp[2][C * 2 + 5], ndp[C * 2 + 5];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    int x, y;
    cin >> s >> x >> y;
    vector<int> len[2];
    int cnt = 0, dir = 0, first = true;
    s += 'T';
    dp[0][C] = dp[1][C] = true;
    for (char c: s) {
        if (c == 'T') {
            if (first) {
                x -= cnt;
                cerr << x << '\n';
            } else {
                for (int c = -C; c <= C; c++) {
                    ndp[c + C] = false;
                    if (c - cnt >= -C && dp[dir][c - cnt + C]) ndp[c + C] = true;
                    if (c + cnt <= C && dp[dir][c + cnt + C]) ndp[c + C] = true;
                }
                for (int c = -C; c <= C; c++)
                    dp[dir][c + C] = ndp[c + C];
            }
            first = false;
            dir = !dir;
            cnt = 0;
        } else {
            ++cnt;
        }
    }
    cout << (dp[0][x + C] && dp[1][y + C] ? "Yes\n" : "No\n");
}
