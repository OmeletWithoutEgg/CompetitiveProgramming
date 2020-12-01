#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 100001;

int dp[N];
void solve() {
    int n,h,x,y,z,sum=0;
    cin >> n >> h;
    for(int i = 0; i < N; i++) dp[i] = 0;
    for(int i = 0; i < n; i++) {
        cin >> x >> y >> z;
        //sum = min(h, sum+max({x,y,z}));
        for(int w = h; w >= min({x,y,z}); w--) {
            if(w >= x) dp[w] = max(dp[w],dp[w-x]+1);
            if(w >= y) dp[w] = max(dp[w],dp[w-y]+1);
            if(w >= z) dp[w] = max(dp[w],dp[w-z]+1);
        }
    }
    for(int i = h; i >= 0; i--) if(dp[i] == n) return cout << i << '\n', void();
    cout << "no solution\n";
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) solve();
}

