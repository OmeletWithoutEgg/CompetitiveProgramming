#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe."
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int N = 200025, MOD = 1000000007;

int naive(int n, int m) {
    set<pair<int,int>> s;
    for(int i = 0; i <= m; i++) {
        for(int j = 0; i+j <= m; j++) {
            if((i^j) <= n) {
                s.insert({i^j, i+j});
                assert((i^j) % 2 == (i+j) % 2);
            }
        }
    }
    return s.size();
}
map<pair<ll,ll>,int> mp;
int solve(ll n, ll m) {
    if(m < 0) return 0;
    if(m == 0) return 1;
    if(mp.count({n, m})) return mp[{n, m}];
    return mp[{n, m}] = (1LL * solve(n/2, m/2) * (m&1 ? 2 : 1) + 1LL * solve(n/2, m/2-1) * (m&1 ? 1 : 2)) % MOD;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll n;
    cin >> n;
    cout << solve(n, n) << '\n';
}
