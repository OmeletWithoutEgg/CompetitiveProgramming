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
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
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
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct Point {
    int x, y;
    friend istream& operator>>(istream &I, Point &p) {
        return I >> p.x >> p.y;
    }
    bool operator<(const Point &rhs) const {
        return x != rhs.x ? x < rhs.x : y < rhs.y;
    }
    friend Point operator-(const Point &a, const Point &b) {
        return {a.x-b.x, a.y-b.y};
    }
    friend int ori(Point a, Point b, Point c) {
        c = c-a, b = b-a;
        int64_t cross = 1LL * b.x * c.y - 1LL * b.y * c.x;
        return cross ? cross > 0 ? 1 : -1 : 0;
    }
    friend int64_t area(Point a, Point b, Point c) {
        c = c-a, b = b-a;
        int64_t cross = 1LL * b.x * c.y - 1LL * b.y * c.x;
        return cross;
    }
};
vector<Point> buildConvexHull(vector<Point> &sorted) {
    vector<Point> lcv, ucv;
    for(auto p: sorted) {
        while(lcv.size() >= 2 && ori(lcv[lcv.size()-2], lcv[lcv.size()-1], p) >= 0) lcv.pop_back();
        lcv.push_back(p);
        while(ucv.size() >= 2 && ori(ucv[ucv.size()-2], ucv[ucv.size()-1], p) <= 0) ucv.pop_back();
        ucv.push_back(p);
    }
    reverse(all(ucv));
    for(auto p: ucv) lcv.push_back(p);
    return lcv;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Point> pts(n);
    for(auto &p: pts) cin >> p;
    sort(all(pts));
    pts = buildConvexHull(pts);
    ll mx = 0;
    for(int i = 0; i < pts.size(); i++) {
        int k = i+2;
        for(int j = i+1; j < pts.size(); j++) {
            while(k < pts.size()*2 && area(pts[i], pts[j], pts[k%pts.size()]) <= area(pts[i], pts[j], pts[(k+1)%pts.size()])) ++k;
            debug(k);
            mx = max(mx, area(pts[i], pts[j], pts[k%pts.size()]));
        }
    }
    debug(mx);
    cout << mx/2 << '.' << (mx&1 ? 5 : 0);
}
