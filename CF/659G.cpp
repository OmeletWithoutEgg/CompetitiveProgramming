#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#define debug(x) cerr<<__PRETTY_FUNCTION__<<" Line "<<__LINE__<<": "<<#x<<" = "<<x<<'\n'
#define ff first
#define ss second
#define pb emplace_back
#define all(v) begin(v),end(v)
#define mem(v,x) memset(v, x, sizeof v)

using namespace std;
typedef int64_t ll;
const int N = 1000025, MOD = 1000000007;

int n, h[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 1; i <= n; i++) cin >> h[i];
    //for(int i = 1; i <= n; i++) ans = (ans+max(0, h[i] - max({1,h[i-1],h[i+1]})))%MOD;
    for(int i = 1; i <= n; i++) {
        //dp[i][0] =
    }
}

