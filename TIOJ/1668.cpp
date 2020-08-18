#include <bits/stdc++.h>
using namespace std;
const int N = 800025;
int n,s,t,dp[N];
pair<int,int> lis[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    fill(lis,lis+n,pair<int,int>(0,1e9));
    for(int i = 0; i < n; i++) {
        cin >> s >> t;
        auto it = lower_bound(lis,lis+n,pair<int,int>(s,t),[](pair<int,int> a,pair<int,int> b) {
            return a.second < b.first;
        });
        dp[i] = it-lis+1;
        *it = pair<int,int>(s,t);
        cout << dp[i] << " \n"[i+1==n];
    }
    cout << *max_element(dp,dp+n) << '\n';
}
