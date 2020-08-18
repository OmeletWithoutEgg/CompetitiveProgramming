#include <bits/stdc++.h>

using namespace std;
const int N = 1000025;
const int64_t INF = 1e18;
typedef long double ld;

int n;
int64_t v[N], a, b, c, dp[N];
int64_t tran(int j, int i) {
    return dp[j] + a*(v[i]-v[j])*(v[i]-v[j]) + b*(v[i]-v[j]) + c;
    // (dp[j] + a*v[j]*v[j] - b*v[j]) - 2*a*v[i]*v[j]
}
bool over(int x,int y,int i) {
    int64_t bx = (dp[x] + a*v[x]*v[x] - b*v[x]);
    int64_t by = (dp[y] + a*v[y]*v[y] - b*v[y]);
    int64_t bi = (dp[i] + a*v[i]*v[i] - b*v[i]);
    int64_t mx = v[x], my = v[y], mi = v[i];
    // arg(f(x)==f(y)) >= arg(f(x)==f(i))
    return (bx-by)/(my-mx) >= (by-bi)/(mi-my);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> a >> b >> c;
    for(int i = 1; i <= n; i++) cin >> v[i], v[i] += v[i-1];
    deque<int> dq{0};
    for(int i = 1; i <= n; i++) {
        #if 0
        dp[i] = -INF;
        for(int j = 0; j < i; j++) dp[i] = max(dp[i], tran(j,i));
        #else
        while(dq.size() >= 2 && tran(dq.front(),i) <= tran(dq[1],i)) dq.pop_front();
        dp[i] = tran(dq.front(), i);
        while(dq.size() >= 2 && over(dq[dq.size()-2], dq.back(), i)) dq.pop_back();
        dq.push_back(i);
        #endif // 0
    }
    cout << dp[n] << '\n';
}

/*
8
-1 -3 -9
9 4 8 7 7 1 2 2
*/
