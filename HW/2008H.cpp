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
#define debug(...) qqbx(#__VA_ARGS__,  __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...); // C++ 17!
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
constexpr ld PI = acos(-1), eps = 1e-9;
constexpr ll N = 500025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

typedef complex<int64_t> point;
struct Segment {
    point S, L; // S + tL, 0 <= t < 1
    Segment(point A, point B) : S(A), L(B-A) {}
    static bool valid(int64_t p, int64_t q) {
        if(q == 0) return p == 0;
        if(q < 0) q = -q, p = -p;
        return 0 <= p && p < q;
    }
};
bool intersect(Segment A, point P) {
    // A.S + t A.L = P
    if(A.L == point{0}) return P == A.S;
    return (imag((P - A.S) * conj(A.L)) == 0) && Segment::valid(real((P - A.S) * conj(A.L)), real(A.L * conj(A.L)));
}
bool intersect(Segment A, Segment B) {
    // a + tLa = b + sLb
    // b - a = tLa - sLb
    // (b-a)conj(La) = t(La*conj(La)) - s(Lb*conj(La))
    // s = IM((a-b)conj(La)) / IM(Lb*conj(La))
    if(imag(A.L * conj(B.L)) == 0)
        return intersect(A, B.S) || intersect(A, B.S+B.L) || intersect(B, A.S) || intersect(B, A.S+A.L);
    return Segment::valid(imag((A.S - B.S) * conj(A.L)), imag(B.L * conj(A.L)))
        && Segment::valid(imag((B.S - A.S) * conj(B.L)), imag(A.L * conj(B.L)));
}
istream& operator>>(istream &I, point &p) {
    int64_t x, y;
    I >> x >> y;
    p = point(x, y);
    return I;
}
bool anyIntersect(const vector<Segment> &v) {
    vector<tuple<int,int,bool>> evt;
    for(int i = 0; i < n; i++) {
        int l = v[i].S.real();
        int r = v[i].S.real() + v[i].L.real();
        evt.pb(l, i, true);
        evt.pb(r, i, false);
    }
    sort(evt.begin(), evt.end());
    for(auto [x, id, tp]: evt) {
        if(tp) {
            int y = v[id].S.imag();
            if(tr.count(y)) return true;
            auto it = tr.lower_bound(y);
            if((it!=tr.end() && intersect(v[id], v[it->second])) ||
               (it!=tr.begin() && intersect(v[prev(it)->second], v[id]))) return true;
            tr[y] = id;
        } else {
            int y = v[id].S.imag();
            auto it = tr.find(y);
            if(it!=tr.begin() && next(it)!=tr.end() && intersect(v[prev(it)->second], v[next(it)->second])) return true;
            tr.erase(it);
        }
    }
    return false;
}
int n;
void solve() {
    vector<Segment> seg;
    for(int i = 0; i < n; i++) {
        point A, B, C;
        cin >> A >> B >> C;
        seg.pb(A, B);
        seg.pb(B, C);
        seg.pb(C, A);
    }
    if(anyIntersect(seg)) {
        cout << "ERROR\n";
        return;
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n && n != -1) solve();
}
