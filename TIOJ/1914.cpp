#include <bits/extc++.h>

using namespace std;
const int N = 201;

int t,n,k,v[N],dp[N][N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n >> k;
        for(int i = 0; i < n; i++) cin >> v[i];
        for(int i = n-1; i >= 0; i--) for(int j = i; j < n; j++) {
            dp[i][j] = j-i+1;
            for(int k = i; k < j; k++)
                dp[i][j] = min(dp[i][j],dp[i][k]+dp[k+1][j]-(v[i]==v[j]));
        }
        cout << dp[0][n-1] << '\n';
    }
}
