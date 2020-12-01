//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \\#################\\
//   \\#################\\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.

#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#define all(v) begin(v),end(v)
#define siz(v) (ll(v.size()))
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
#define pb emplace_back
#define ff first
#define ss second
#define mid (l+(r-l>>1))
#define mem(v,x) memset(v,x,sizeof v)

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
template <typename T> using rkt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-9;
constexpr ll N = 50025, INF = 1e18, MOD = 1000000007, K = 63;
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
template <typename T> void M(T &x, ll m = MOD){x%=m; if(x<0) x+=m;}

ll read() {
    string s;
    cin >> s;
    assert(s[2]==':' && s[5]==':');
    int H = (s[0]-'0')*10+(s[1]-'0');
    int M = (s[3]-'0')*10+(s[4]-'0');
    int S = (s[6]-'0')*10+(s[7]-'0');
    return H*3600+M*60+S;
}
void print(ll x) {
    if(x < 0) x += 24*3600;
    int H = x/3600;
    int M = (x/60)%60;
    int S = x%60;
    //debug(H),debug(M),debug(S);
    if(H < 10) cout << '0';
    cout << H << ':';
    if(M < 10) cout << '0';
    cout << M << ':';
    if(S < 10) cout << '0';
    cout << S << '\n';
}
signed main() {
    ll st = read();
    ll ed = read();
    print(ed-st);
}
