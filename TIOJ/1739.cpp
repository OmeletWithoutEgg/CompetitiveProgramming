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
#define debug(x) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define siz(v) (ll(v.size()))
#define get_pos(v,x) (lower_bound(all(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define ff first
#define ss second
#define mem(v,x) memset(v,x,sizeof v)

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = __gnu_pbds::priority_queue<T,less<T> >;
template <typename T> using min_heap = __gnu_pbds::priority_queue<T,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-5;
constexpr ll N = 300025, INF = 1e18, MOD = 998244353, K = 64, inf = 1e9;
constexpr ll modpow(ll e,ll p,ll m=MOD) {ll r=1; for(;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r;}
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x<0 ^ m>0) && (x%m); } // ceiling divide
#include "lib1739.h"

struct segtree {
    struct node {
        int l,r,val;
    } S[N*K];
    int tot;
    int newnode(int v) {
        return S[++tot] = {0,0,v}, tot;
    }
    int newnode(int l,int r) {
        return S[++tot] = {l,r,0}, tot;
    }
    int build(int l, int r) {
        if(l+1 == r) return newnode(l);
        int m = l+(r-l>>1);
        return newnode(build(l,m),build(m,r));
    }
    int modify(int root, int p, int k, int l, int r) {
        if(l+1 == r) return newnode(k);
        int m = l+(r-l>>1);
        if(p < m)
            return newnode(modify(S[root].l,p,k,l,m), S[root].r);
        else
            return newnode(S[root].l, modify(S[root].r,p,k,m,r));
    }
    int query(int root, int p, int l, int r) {
        while(l+1 < r) {
            int m = l+(r-l>>1);
            if(p < m) r = m, root = S[root].l;
            else l = m, root = S[root].r;
        }
        return S[root].val;
    }
} sgt;
int n,m;
int root[N],chg[N],v[N],pos[N];
void init() {
    root[0] = sgt.build(1,n+1);
    for(int i = 1; i <= n; i++) v[i] = pos[i] = i;
    for(int i = 1; i <= m; i++) {
        int a = chg[i], b = chg[i]+1;
        int r = sgt.modify(root[i-1],v[a],pos[v[b]],1,n+1);
        root[i] = sgt.modify(r,v[b],pos[v[a]],1,n+1);
        swap(pos[v[a]], pos[v[b]]);
        swap(v[a], v[b]);
    }
}
signed main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) scanf("%d", chg+i);
    init();
    int q = getNumQuestions();
    while(q--) {
        int A,B;
        getQuestion(A, B);
        answer(sgt.query(root[B],A,1,n+1));
    }
}
