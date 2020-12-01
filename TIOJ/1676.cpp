#include <bits/stdc++.h>
#define debug(x) (cerr<<#x<<" = "<<x<<'\n')
using namespace std;
const int64_t N = 500025, INF = 1e18;
int n,k;
int64_t v[N],dp[N];
int64_t tran(int64_t i,int64_t j) {
    return dp[j]-(i-j)*(i-j)+v[i];
}
bool over(int64_t a,int64_t b,int64_t i) {
    // don't know if dividing operation should be floor or ceiling
    int64_t x = min(a+k, ((dp[a]-a*a) - (dp[b]-b*b)) / (b*2 - a*2)); // expire of a
    int64_t y = min(b+k, ((dp[b]-b*b) - (dp[i]-i*i)) / (i*2 - b*2)); // expire of b
    return x>=y;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> k;
    for(int i = n; i >= 1; i--) cin >> v[i];
    for(int i = 1; i <= n; i++) v[i] += v[i-1];
    deque<int> dq;
    dq.push_back(0);
    for(int i = 1; i <= n; i++) {
        //dp[i] = -INF;
        //for(int j = max(0,i-k); j < i; j++) dp[i] = max(dp[i], dp[j] - (i-j)*(i-j) + v[i]);
        //v[i]-i*i + (dp[j]-j*j) + (2*i)*j;
        while(dq.size() && dq.front()+k < i) dq.pop_front();
        while(dq.size() >= 2 && tran(i,dq[0]) <= tran(i,dq[1])) dq.pop_front();
        dp[i] = tran(i,dq[0]);
        while(dq.size() >= 2 && over(dq[dq.size()-2],dq.back(),i)) dq.pop_back();
        dq.push_back(i);
    }
    cout << dp[n]-v[n] << '\n';
}
