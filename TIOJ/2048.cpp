//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \\#################\\
//   \\#################\\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.

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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 300;

ll dp[2][N],a,n,best=-1e18,mx=-1e18,MX;
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a;
        if(i>=1) MX = max(0LL, dp[0][i-1]);
        if(i>=2) mx = max({mx, dp[1][i-2],dp[1][i-1],dp[0][i-2]});
        debug(mx);
        dp[0][i] = MX+a;
        dp[1][i] = mx+a;
        debug(dp[0][i]), debug(dp[1][i]);
        best = max(best, dp[1][i]);
    }
    cout << best << '\n';
}

