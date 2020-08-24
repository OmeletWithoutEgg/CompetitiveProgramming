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
 
#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#else
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
    /* friend bool operator<(const Point a&, const Point &b){ return a.x!=b.x ? a.x<b.x : a.y<b.y; } */
    friend Point operator-(const Point &a, const Point &b) {
        return {a.x - b.x, a.y - b.y};
    }
};
int intersect(Point a, Point b, int x, bool canTouch) {
    // x - a.x, b.x - x
    // y = (a.y * (b.x-x) + b.y * (x-a.x)) / (b.x - a.x)
    ll A = 1LL * a.y * (b.x-x) + 1LL * b.y * (x-a.x), B = b.x - a.x;
    if(canTouch && A%B == 0) return A / B;
    assert(B > 0);
    int res = A/B;
    if((res+1)*B < A) ++res;
    if(res*B >= A) --res;
    return res;
}
#define int int64_t
#define ll ld
ld calc(const vector<Point> &pts) {
    vector<Point> u, v; // u is lower, v is upper
    {
        int l = min_element(pts.begin(), pts.end(), [](const Point &a, const Point &b){ return a.x!=b.x ? a.x<b.x : a.y<b.y; }) - pts.begin();
        int r = min_element(pts.begin(), pts.end(), [](const Point &a, const Point &b){ return a.x!=b.x ? a.x>b.x : a.y<b.y; }) - pts.begin();
        if(l <= r) {
            for(int i = l; i <= r; i++) u.push_back(pts[i]);
        } else {
            for(int i = l; i < int(pts.size()); i++) u.push_back(pts[i]);
            for(int i = 0; i <= r; i++) u.push_back(pts[i]);
        }
    }
    {
        int r = min_element(pts.begin(), pts.end(), [](const Point &a, const Point &b){ return a.x!=b.x ? a.x<b.x : a.y>b.y; }) - pts.begin();
        int l = min_element(pts.begin(), pts.end(), [](const Point &a, const Point &b){ return a.x!=b.x ? a.x>b.x : a.y>b.y; }) - pts.begin();
        if(l <= r) {
            for(int i = l; i <= r; i++) v.push_back(pts[i]);
        } else {
            for(int i = l; i < int(pts.size()); i++) v.push_back(pts[i]);
            for(int i = 0; i <= r; i++) v.push_back(pts[i]);
        }
    }
    sort(u.begin(), u.end(), [](const Point &a, const Point &b){return a.x<b.x;});
    sort(v.begin(), v.end(), [](const Point &a, const Point &b){return a.x<b.x;});
    /* debug("HERE"); */
    /* for(auto p: u) cout << p.x << ',' << p.y << '\n'; */
    /* safe; */
    /* for(auto p: v) cout << p.x << ',' << p.y << '\n'; */
    /* safe; */
    ll cnt = 0;
    ll sum = 0, sqsum = 0, xsum = 0;
    /* vector<int> xs; */
    for(int x = u.front().x, i = 0, j = 0; x <= u.back().x; x++) {
        while(i < u.size() && u[i].x <= x) ++i;
        while(j < v.size() && v[j].x <= x) ++j;
        assert(i && j);
        int l = i==u.size() ? u.back().y-1 : intersect(u[i-1], u[i], x, 0); // can't touch
        int r = j==v.size() ? v.back().y : intersect(v[j-1], v[j], x, 1); // can touch
        /* debug(i, j, l, r); */
        sum += (r-l) * (x*x*cnt - 2*x*xsum + sqsum);
        xsum += 1LL*x*(r-l);
        sqsum += 1LL*x*x*(r-l);
        cnt += r-l;
    }
    /* cnt = xs.size() * (xs.size()-1) / 2; */
    /* for(int i = 0; i < xs.size(); i++) for(int j = 0; j < i; j++) sum += (xs[i]-xs[j])*(xs[i]-xs[j]); */
    return sum / ld(cnt*(cnt-1)/2);
}
bool clockwise(vector<Point> &p) {
    for(int i = 0; i < p.size(); i++) {
        Point a = p[i] - p[(i+1)%p.size()];
        Point b = p[(i+1)%p.size()] - p[(i+2)%p.size()];
        ll C = 1LL*a.x*b.y - 1LL*a.y*b.x;
        if(C != 0) return C < 0;
    }
    debug("QAQ");
    exit(-1);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<Point> v(n);
    for(auto &[x, y]: v) cin >> x >> y;
    if(clockwise(v)) reverse(v.begin(), v.end());
    ld ans = 0;
    ans += calc(v);
    for(auto &[x, y]: v) swap(x, y);
    if(clockwise(v)) reverse(v.begin(), v.end());
    ans += calc(v);
    ans /= 2;
    cout << fixed << setprecision(20);
    cout << ans << '\n';
}
