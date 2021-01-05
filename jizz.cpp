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
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))

using namespace std;
using ll = long long;
const int N = 1000025, inf = 1e9;

vector<pair<ll,int>> v;
vector<ll> ans;
void dfs(ll lim, ll prod, int i) {
    ans.pb(prod);
    if(i == v.size()) return;
    auto [p, maxC] = v[i];
    for(int c = 0; c <= maxC; c++) {
        dfs(lim, prod, i+1);
        if(prod > lim / p) break;
        prod *= p;
    }
}
vector<int> prs;
bool sv[N];
void solve() {
    ll lim;
    ll a, b;
    cin >> lim >> a >> b;
    map<ll,int> mp;
    for(int p: prs) {
        while(a % p == 0) a /= p, ++mp[p];
        if(p*p >= a) break;
    }
    for(int p: prs) {
        while(b % p == 0) b /= p, ++mp[p];
        if(p*p >= b) break;
    }
    if(a > 1) mp[a] += 1;
    if(b > 1) mp[b] += 1;
    v.clear();
    for(auto [p, c]: mp) v.pb(p, c);
    ans.clear();
    dfs(lim, 1, 0);
    sort_uni(ans);
    for(int i = 0; i < ans.size(); i++)
        cout << ans[i] << (i+1==ans.size() ? '\n' : ' ');
}
signed main() {
    for(int i = 2; i < N; i++) {
        if(!sv[i]) prs.pb(i);
        for(int p: prs) {
            if(i*p >= N) break;
            sv[i*p] = true;
            if(i%p == 0) break;
        }
    }
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--)
        solve();
}
