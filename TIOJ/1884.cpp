#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <deque>
#define ff first
#define ss second
#define pb emplace_back

typedef long long ll;
inline char readchar() {
    static constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline ll min(ll a, ll b) {return a<b?a:b;}
std::deque<std::pair<int,ll>> dq[2];
ll solve() {
    int n = nextint();
    int k = nextint();
    int L = nextint();
    int v = nextint();
    ll dp = 0;
    dq[0].clear();
    dq[1].clear();
    dq[0].pb(0, 0);
    dq[1].pb(0, 2*(L-v));
    for(int i = 1; i <= n; i++) {
        /*dp[i] = INF;
        for(int j = max(0, i-k); j < i; j++) {
            dp[i] = min(dp[i], dp[j] + min({L, 2*v[i], 2*(L-v[j+1])}));
        }*/
        //puts("SAFE");
        while(dq[0].front().ff < i-k) dq[0].pop_front();
        while(dq[1].front().ff < i-k) dq[1].pop_front();
        dp = min(dq[0].front().ss+min(L,2*v), dq[1].front().ss);
        if(i!=n) v = nextint();
        while(dq[0].size() && dq[0].back().ss >= dp) dq[0].pop_back();
        while(dq[1].size() && dq[1].back().ss >= dp+2*(L-v)) dq[1].pop_back();
        dq[0].pb(i, dp);
        dq[1].pb(i, dp+2*(L-v));
    }
    return dp;
    /*
        dp[i] = min(dp[j] + min(L, 2*v[i], 2*(L-v[j]));
        dp[i] = min(dp[j] + min(a[i], b[j])) = min(min(dp[j])+a[i], min(dp[j]+b[j]));
    */
}
signed main() {
    int t = nextint();
    while(t--) printf("%lld\n", solve());
}
