#include <bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    long long N, K, W, C, T;
    long long water = 0;
    long long totTime = 0;
    long long mnc = 1e18, mxc = -1e18;
    long long mnt = 1e18, mxt = -1e18;
    assert(cin >> N >> K >> W >> C >> T);
    int ans = 0;
    for(int i = 1; i <= N; i++) {
        long long c, t;
        assert(cin >> c >> t);
        mnc = min(mnc, c), mxc = max(mxc, c);
        mnt = min(mnt, t), mxt = max(mxt, t);
        water -= c;
        totTime += t;
        if(water < 0) {
            long long cnt = (-water + K-1) / K; // cdiv
            water += cnt * K;
            totTime += cnt * W;
        }
        if(totTime <= T) ans = i;
    }
    cout << ans << '\n';
    cerr << N << ' ' << K << ' ' << W << ' ' << C << ' ' << T << '\n';
    cerr << mnc << ' ' << mxc << '\n';
    cerr << mnt << ' ' << mxt << '\n';
    cerr << ans << '\n';
}
