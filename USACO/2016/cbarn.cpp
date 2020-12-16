#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int N = 1025;
const ll INF = 1e18;

ll sum[N], isum[N];
struct Line {
    ll a, b;
    ll operator()(ll x) { return a * x + b; }
};
bool check(Line a, Line b, Line c) {
    // return (a & c) <= (a & b)
    return (a.b - c.b) * (b.a - a.a) <= (a.b - b.b) * (c.a - a.a);
}
ll cost(int a, int b) {
    return isum[b] - isum[a] - (a+1) * (sum[b] - sum[a]);
    // isum[b] - sum[b] * (a+1) - (isum[a] + (a+1)*sum[a]);
}
ll dp[8][N];
ll solve(vector<int> r, int k) {
    int n = r.size();
    for(int i = 1; i <= n; i++) sum[i] = sum[i-1] + r[i-1];
    for(int i = 1; i <= n; i++) isum[i] = isum[i-1] + 1LL * i * r[i-1];
    /* cerr << "r = \n"; for(int i = 0; i < n; i++) cerr << r[i] << ' '; cerr << '\n'; */
    /* cerr << "sum = \n"; for(int i = 0; i <= n; i++) cerr << sum[i] << ' '; cerr << '\n'; */
    for(int i = 1; i <= n; i++) dp[0][i] = INF;
    ll res = INF;
    for(int t = 1; t <= k; t++) {
        /* dnq(1, n); */
        deque<Line> dq;
        dq.push_back({1, 0});
        for(int i = 1; i <= n; i++) {
            while(dq.size() >= 2 && dq[0](sum[i]) <= dq[1](sum[i])) dq.pop_front();
            dp[t][i] = isum[i] - dq[0](sum[i]);
            Line L = {i+1, isum[i] - (i+1)*sum[i] - dp[t-1][i]};
            while(dq.size() >= 2 && check(dq[dq.size()-2], dq.back(), L)) dq.pop_back();
            dq.push_back(L);
            /* for(int j = i-1; j >= 0; j--) { */
            /*     dp[t][i] = min(dp[t][i], dp[t-1][j] + cost(j, i)); */
            /* } */
        }
        res = min(res, dp[t][n]);
        /* for(int i = 1; i <= n; i++) cerr << dp[t][i] << ' '; */
        /* cerr << '\n'; */
    }
    debug(res);
    return res;
}

signed main() {
#ifndef local
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);
#endif // local
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> r(n);
    for(int &x: r) cin >> x;
    ll ans = INF;
    for(int s = 0; s < n; s++) {
        rotate(r.begin(), r.begin() + 1, r.end());
        ans = min(ans, solve(r, k));
        /* break; */
    }
    cout << ans << '\n';
}

/*
3 1
1 2 3

6 2
2 5 4 2 6 2
*/
