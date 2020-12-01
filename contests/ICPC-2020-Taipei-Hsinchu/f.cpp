#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef pair<int,int> pii;
const int maxn=2e5+10,inf=1e9;
int n,m;
vector<int> e[maxn];
pii dfs(int i,int p=-1){
    pii ret{0, 1};
    for(auto &to:e[i]){
        if((p==-1&&to<n) || to==p) continue;
        pii t = dfs(to,i);
        ret.first += t.second;
        ret.second += min(t.first, t.second);
    }
    return ret;
}
signed main(){
    cin>>n>>m;
    for(int i=0,a,b;i<n+m;i++){
        cin>>a>>b;
        e[a].push_back(b); e[b].push_back(a);
    }
    vector<pii> v;
    for(int i=0;i<n;i++){
        v.push_back(dfs(i));
    }
    int ans = inf;
    vector<pii> dp(n);
    dp[0] = {inf, v[0].second};
    for(int i = 1; i < n; i++)
        dp[i] = {dp[i-1].second + v[i].first, min(dp[i-1].first, dp[i-1].second) + v[i].second};
    ans = min({ ans, dp[n-1].first, dp[n-1].second });
    dp[0] = {v[0].first, inf};
    for(int i = 1; i < n; i++)
        dp[i] = {dp[i-1].second + v[i].first, min(dp[i-1].first, dp[i-1].second) + v[i].second};
    ans = min(ans, dp[n-1].second);
    cout << ans << '\n';
}
