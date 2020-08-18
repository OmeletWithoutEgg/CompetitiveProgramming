#include <bits/stdc++.h>

using namespace std;

int C, cnt[5];
const int c[5] = {1, 5, 10, 20, 50};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while(T--) {
        cin >> C;
        int tot = 0;
        for(int i = 0; i < 5; i++) cin >> cnt[i];
        for(int i = 0; i < 5; i++) {
            int x;
            cin >> x;
            cnt[i] += x;
            C += c[i] * x;
        }
        // C = c[i] * take[i];
        // ans = take[i]
        // dp[i][C] = min(dp[i-1][C-take*c[i]] + take)
        // dp[i][r+c[i]*a] = min(dp[i-1][r+c[i]*b] + (a-b))
        /*cerr << "C = " << C << endl;
        for(int i = 0; i < 5; i++) cerr << cnt[i] << ' ';
        cerr << endl;*/
        for(int i = 0; i < 5; i++) tot += cnt[i];
        vector<int> dp[2];
        dp[0].resize(C+1), dp[1].resize(C+1);
        for(int w = 0; w <= C; w++) dp[1][w] = -1e9;
        dp[1][0] = 0;
        for(int i = 0; i < 5; i++) {
            deque<pair<int,int>> dq;
            for(int r = 0; r < c[i]; r++) {
                for(int w = 0; r+c[i]*w <= C; w++) {
                    while(dq.size() && dq.front().first < w - cnt[i]) dq.pop_front();
                    while(dq.size() && dq.back().second <= dp[~i&1][r+c[i]*w] - w) dq.pop_back();
                    dq.emplace_back(w, dp[~i&1][r+c[i]*w] - w);
                    dp[i&1][r+c[i]*w] = dq.front().second + w;
                }
            }
            /*cout << "---\n";
            for(int w = 0; w <= C; w++) cout << dp[i&1][w] << ' ';
            cout << '\n';*/
            /*for(int w = 0; w <= C; w++) {
                dp[i&1][w] = -1e9;
                for(int take = 0; take <= cnt[i] && take*c[i] <= w; take++) {
                    dp[i&1][w] = max(dp[i&1][w], dp[~i&1][w-take*c[i]] + take);
                }
            }*/
        }
        cout << tot - dp[0][C] << '\n';
    }
}
