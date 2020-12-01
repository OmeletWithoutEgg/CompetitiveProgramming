//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\
//   \###################\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.

#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#include <bits/stdc++.h>
#define debug(x) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define siz(v) (ll(v.size()))
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define ff first
#define ss second

using namespace std;
typedef int64_t ll;
typedef pair<int,int> pii;
constexpr ll N = 50025, INF = 1e18;

ld dist(pii a,pii b){return hypot(ll(a.ff)-b.ff, ll(a.ss)-b.ss);}
ld best;
pll v[N];
void solve(int l, int r){
    if(r-l == 1) return INF;
    int lm =
    solve(l, m), solve(m, r);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    //freopen("../p01.txt", "r", stdin);
    int n;
    cout << fixed << setprecision(6);
    while(cin >> n) {
        for(int i = 0; i < n; i++) cin >> v[i].ff >> v[i].ss;
        sort(v,v+n,[](pll a,pll b){return a.ss<b.ss;});
        ans = INF;
        solve(0, n);
        cout << best << '\n';
    }
}
