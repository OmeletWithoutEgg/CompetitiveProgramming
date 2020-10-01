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
 
#ifdef local
#include <bits/extc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    std::cerr << "\033[1;32m" << '(' << s << ')' << " = " << '(';
    constexpr int size = sizeof...(T);
    int cnt = size, dummy[size] = { (std::cerr << args << (--cnt ? ", " : ")\033[0m\n"), 0)... };
}
#else
#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#include <bits/stdc++.h>
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define get_pos(v,x) int(lower_bound(begin(v),end(v),x)-begin(v))
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
template <typename T> using max_heap = std::priority_queue<T,vector<T>,less<T> >;
template <typename T> using min_heap = std::priority_queue<T,vector<T>,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 300025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

template <int k>
struct Segtree {
    struct node : vector<pair<int,int>> {
        node() {}
        node(int x) : vector<pair<int,int>>{{x, 1}} {}
        friend node operator+(const node &a, const node &b) {
            const int n = a.size(), m = b.size();
            node res;
            for(int i = 0, j = 0; i < n || j < m; ) {
                pair<int,int> now = (j == m || (i < n && a[i] < b[j])) ? a[i++] : b[j++];
                if(res.empty() || res.back().first != now.first)
                    res.push_back(now);
                else
                    res.back().second += now.second;
            }
            if(res.size() >= k) {
                sort(res.begin(), res.end(), [](pair<int,int> x, pair<int,int> y){ return x.second > y.second; });
                int t = res[k-1].second;
                res.resize(k-1);
                for(int i = 0; i < k-1; i++) res[i].second -= t;
                sort(res.begin(), res.end());
            }
            return res;
        }
    };
    int n;
    vector<node> st;
    Segtree(const vector<int> &v) : n(v.size()), st(v.size() * 2) {
        for(int i = 0; i < n; i++) st[i+n] = node(v[i]);
        for(int i = n-1; i > 0; i--) st[i] = st[i<<1] + st[i<<1|1];
    }
    vector<int> query(int l, int r) {
        node resl, resr;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) resl = resl + st[l++];
            if(r&1) resr = st[--r] + resr;
        }
        vector<int> res;
        for(auto [a, b]: (resl + resr)) res.pb(a);
        return res;
    }
};
vector<int> vs[N];
struct Query {
    int l, r, pos;
    Query(int l, int r, int pos) : l(l), r(r), pos(pos) {}
};
int getCnt(vector<int> &v, int l, int r) {
    /* int cnt = 0; */
    /* for(int x: v) if(l <= x && x < r) ++cnt; */
    /* return cnt; */
    return get_pos(v, r) - get_pos(v, l);
}
int ans[N];
template <int k>
void solve(const vector<int> &a, const vector<Query> &Q) {
    Segtree<k> sgt(a);
    for(auto &[l, r, id]: Q) {
        vector<int> candidate = sgt.query(l-1, r);
        bool found = false;
        for(int x: candidate) {
            int cnt = getCnt(vs[x], l-1, r);
            debug(x, cnt);
            if(cnt > (r-l+1) / k) {
                found = true;
                ans[id] = x;
                break;
            }
        }
        if(!found) ans[id] = -1;
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(int &x: a) cin >> x;
    vector<Query> Q[6];
    for(int i = 0; i < q; i++) {
        int l, r, k;
        cin >> l >> r >> k;
        Q[k].pb(l, r, i);
    }
    for(int i = 0; i < n; i++) vs[a[i]].pb(i);
    solve<2>(a, Q[2]);
    solve<3>(a, Q[3]);
    solve<4>(a, Q[4]);
    solve<5>(a, Q[5]);
    for(int i = 0; i < q; i++) cout << ans[i] << '\n';
}
