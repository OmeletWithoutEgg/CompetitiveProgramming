#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <utility>

typedef long long ll;
using state = std::pair<ll,int>;
state min(const state &a, const state &b) {
    return a < b ? a : b;
}
state operator+(const state &a, const state &b) {
    return {a.first + b.first, a.second + b.second};
}
state dp[2], best;
int n, k;
ll d[100025];
state calc(ll p) {
    dp[0] = {0, 0};
    best = dp[1] = min(dp[0], dp[0] + state{d[1]-p, 1});
    for(int i = 2; i <= n; i++) {
        dp[i&1] = min(dp[~i&1], dp[i&1] + state{d[i]-p, 1});
        best = min(best, dp[i&1]);
    }
    return best;
}

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

signed main() {
    n = nextint() - 1, k = nextint();
    int last = nextint();
    for(int i = 1; i <= n; i++) {
        int v = nextint();
        d[i] = v-last;
        last = v;
    }
    ll x = 0;
    for(ll s = 1<<30; s; s>>=1) if(calc(x+s).second < k) x += s;
    ll DP = calc(x).first;
    printf("%lld\n", DP + x*k);
}

