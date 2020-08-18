#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) 0//(cerr<<#x<<" = "<<(x)<<'\n')
#define all(v) begin(v),end(v)
#define pb emplace_back
#define ff first
#define ss second
#define mid (l+(r-l>>1))

using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;
constexpr long double PI = acos(-1),eps = 1e-8;
constexpr ll N = 225, INF = 1e18, MOD = 1000000007, K = 300;

ll m,n,a,b,c,d,res;
ll dp[N][N][N];
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> m >> n >> a >> b >> c >> d;
    for(int i = 1; i <= n; i++) {
        for(int x = 1; x <= m; x++) for(int y = 1; y <= m; y++)
            dp[i][x][y] = dp[i-1][x-1][y-1]+(a*(i-1)+b*(x-1)+c*(y-1))%d,
            dp[i][x][y] = max({dp[i][x][y],dp[i][x-1][y],dp[i][x][y-1]});
    }
    cout << dp[n][m][m] << '\n';
}

