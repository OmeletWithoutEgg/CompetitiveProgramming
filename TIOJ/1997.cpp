#include <iostream>
using namespace std;
typedef long long ll;
const ll N = 1000001, INF = 1e18;

ll n,k,v[N],dp[N];
int fr[7][N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; i++) cin >> v[i], v[i] += v[i-1];
    int d = 1;
    for(int i = 1; i <= n; i++) dp[i] = -INF;
    for(int t = 1; t <= k; t++) {
        ll mx = (t==1 ? 0 : -INF), pos = 0;
        for(int i = 1; i <= n; i++) {
            ll DP = mx + d*v[i];
            fr[t][i] = pos;
            if(mx < dp[i] - d*v[i]) {
                mx = dp[i] - d*v[i];
                pos = i;
            }
            dp[i] = DP;
        }
        d = -d;
    }
    for(int t = k-1, i = fr[k][n]; t >= 1; i=fr[t--][i])
        cout << i << '\n';
}

