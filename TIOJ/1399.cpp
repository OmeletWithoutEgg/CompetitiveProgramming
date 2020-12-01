#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <utility>
#define ff first
#define ss second
#define pb emplace_back

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && ~c) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

const int N = 100025;
typedef long long ll;
typedef std::pair<ll,ll> pll;
inline ll max(ll a, ll b){return a>b?a:b;}
int n, lim;
ll F[N], D[N], T[N];
ll dp[2][N];
pll dq[N];
int head, tail;
bool better(pll a, pll b, pll c) {
    return (b.ss-a.ss) * (c.ff-b.ff) < (c.ss-b.ss) * (b.ff-a.ff);
}
void ins(ll a, ll b) {
    while(tail-head >= 2 && better(dq[tail-2], dq[tail-1], {a, b}))
        --tail;
    dq[tail++] = {a, b};
}
ll qry(ll x) {
    while(tail-head >= 2 && dq[head].ff*x+dq[head].ss <= dq[head+1].ff*x+dq[head+1].ss)
        ++head;
    return dq[head].ff*x+dq[head].ss;
}
signed main() {
    freopen("../in.txt", "r", stdin);
    //ios_base::sync_with_stdio(0), cin.tie(0);
    while(lim = nextint()) {
        n = nextint();
        for(int i = 1; i <= n; i++) F[i] = nextint();
        for(int i = 1; i <= n; i++) D[i] = nextint();
        for(int i = 1; i <= n; i++) T[i] = nextint();
        for(int i = 1; i <= n; i++) T[i] += T[i-1];

        ll best = 0;
        for(int i = 0; i <= lim; i++)
            dp[0][i] = i ? -1e18 : 0;
        for(int i = 1; i <= n; i++) {
            /*
            for(int a = 0; a <= lim; a++) {
                dp[i][a] = dp[i-1][a];
                for(int b = 0; b <= a; b++) {
                    ll d = a-b;
                    dp[i][a] = max(dp[i][a], dp[i-1][b] + F[i]*d - D[i]*d*(d-1)/2);
                }
                if(a>=T[i]) best = max(best, dp[i][a-T[i]]);
            }
            }*/
            bool d = i&1;
            if(!D[i]) {
                dp[d][0] = dp[!d][0];
                for(int a = 1; a <= lim; a++)
                    dp[d][a] = max(dp[!d][a], dp[d][a-1]+F[i]);
                for(int a = 0; a+T[i] <= lim; a++)
                    best = max(best, dp[d][a]);
                continue;
            }
            head = tail = 0;
            for(int a = 0; a <= lim; a++) {
                ins(a*D[i], dp[!d][a] - F[i]*a - D[i]*a*(a+1LL)/2);
                dp[d][a] = max(dp[!d][a], (F[i]*a - D[i]*a*(a-1LL)/2) + qry(a));
                if(a+T[i] <= lim)
                    best = max(best, dp[d][a]);
            }
        }
        printf("%lld\n", best);
    }
    /* dp[i][a] = max(dp[i-1][a],
                      dp[i-1][b] + F[i] * (a-b) - D[i] * (a-b)*(a-b-1)/2);
                      (F[i]*a - D[i]*a*(a-1)/2) + dp[i-1][b]-F[i]*b-D[i]*b*(b+1)/2 + a*b*D[i]
                      dp[i-1][b] -F[i]*b + F[i]*a - D[i]*(a^2+b^2-2ab-a+b)/2
                      F[i]*a - D[i]*a*(a-1)/2
                      cx+mx*a > cy+my*a
                      cx-cy > (my-mx)*a
                      a < (cx-cy) / (my-mx)
    */
}

