#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
using ll = long long;
const int N = 200025;
const ll INF = 1e18;

vector<pair<ll,int>> g[N];
int pa[20][N];
ll len[20][N];
int cnt[20][N];
signed main() {
#ifndef local
    freopen("runaway.in", "r", stdin);
    freopen("runaway.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    ll lim;
    cin >> n >> lim;
    for(int i = 2; i <= n; i++) cin >> pa[0][i] >> len[0][i];
    len[0][1] = INF;
    for(int L = 1; L < 20; L++) {
        for(int i = 1; i <= n; i++) {
            pa[L][i] = pa[L-1][pa[L-1][i]];
            len[L][i] = min(INF, len[L-1][i] + len[L-1][pa[L-1][i]]);
        }
    }
    for(int i = 1; i <= n; i++) {
        if(len[0][i] > lim) {
            ++cnt[0][i];
            continue;
        }
        int x = i;
        ll sum = 0;
        debug(i);
        for(int L = 19; L >= 0; L--) if(sum + len[L][x] <= lim) debug(x, L), sum += len[L][x], ++cnt[L][x], x = pa[L][x];
        debug(x, sum);
        ++cnt[0][x];
    }
    for(int L = 19; L >= 1; L--) {
        for(int i = 1; i <= n; i++) {
            cnt[L-1][i] += cnt[L][i];
            cnt[L-1][pa[L-1][i]] += cnt[L][i];
        }
    }
    for(int i = 1; i <= n; i++) cout << cnt[0][i] << '\n';
}
