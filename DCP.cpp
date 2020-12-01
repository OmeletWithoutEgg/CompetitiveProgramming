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

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
template <typename T> using rkt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-9;
constexpr ll N = 1000025, INF = 1e18, MOD = 998244353, K = 899153;
constexpr inline ll cdiv(ll x, ll m) { return (x+m-1)/m; } // ceiling divide, x/m for flooring divide
template <typename T> void M(T &x, ll m = MOD){x%=m; if(x<0) x+=m;}

// splay tree
struct splay_tree {
    int pa[N],sz[N],ch[2][N];
    bool isroot(int x){return ch[0][pa[x]]!=x && ch[1][pa[x]]!=x;}
    bool ori(int x){
        assert(!isroot(x));
        if(ch[0][pa[x]] == x) return 0;
        if(ch[1][pa[x]] == x) return 1;
    }
    void init(int n) { for(int i = 1; i <= n; i++) pa[i] = i, sz[i] = 1; }
    void rot(int &x,bool d) {
        int y = x;
        x = ch[!d][y], ch[!d][y] = ch[d][x], ch[d][x] = y;
    }
    void splay(int x) {
        while(!isroot(x)) {
            int y = pa[x];
            if(!isroot(y))
        }
    }
};
struct ETT{

};
struct dynamic_connectivity {
    void addEdge(int x,int y);
    void cutEdge(int x,int y);
    bool isconnect(int x,int y);
};

signed main() {
    //LCT
}
