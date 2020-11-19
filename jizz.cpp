#include <bits/stdc++.h>
#ifdef local
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
void qqbx(const char *s) {}
template <typename H, typename ...T> void qqbx(const char *s, const H &h, T ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if (sizeof...(T)) qqbx(++s, args...);
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define ff first
#define ss second
#define all(v) begin(v),end(v)
#define get_pos(v, x) int(lower_bound(begin(v),end(v),x) - begin(v))

using namespace std;
typedef int64_t ll;
typedef long double ld;
const int N = 200025, MOD = 1000000007;
const ld PI = acos(-1);

/*
bool check(pair<int,int> a, pair<int,int> b) {
    static const auto in = [](pair<int,int> I, int x) {
        if(I.ff < I.ss) return I.ff < x && x < I.ss;
        return I.ff < x || x < I.ss;
    };
    return in(a, b.ff) || in(a, b.ss) || in(b, a.ff) || in(b, a.ss);
}
*/
struct FenwickTree : vector<int> {
    FenwickTree(int n) : vector<int>(n) {}
    void add(int p, int d) {
        for(++p; p <= size(); p += p&-p) at(p-1) += d;
    }
    int query(int p) {
        int res = 0;
        for(++p; p > 0; p -= p&-p) res += at(p-1);
        return res;
    }
};
signed main() {
#ifndef local
    assert( freopen("sight.in", "r", stdin) && freopen("sight.out", "w", stdout) );
#endif // local
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, R;
    cin >> n >> R;
    vector<pair<ld,ld>> I(n);
    vector<ld> u;
    for(int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        ld theta = atan2(y, x);
        ld D = sqrt(x*x+y*y);
        ld phi = acos(R / D);
        ld l = theta - phi, r = theta + phi;
        if(l < 0) l += PI * 2;
        if(r < 0) r += PI * 2;
        if(l >= PI*2) l -= PI*2;
        if(r >= PI*2) r -= PI*2;
        I[i] = {l, r};
        u.pb(l), u.pb(r);
    }
    sort(all(u));
    assert(unique(u.begin(), u.end()) == u.end());
    vector<pair<int,int>> v;
    vector<tuple<int,int,int>> evt;
    for(int i = 0; i < n; i++) {
        int l = get_pos(u, I[i].ff);
        int r = get_pos(u, I[i].ss);
        // debug(l, r);
        if(l < r)
            v.pb(l, r), evt.pb(l, r, 1);
        else
            evt.pb(r, l, 0);
    }

    ll ans = 0;
    sort(all(v));
    FenwickTree fwt(u.size());
    for(auto p: v) {
        int l, r;
        tie(l, r) = p;
        ans += fwt.query(l);
        fwt.add(r, 1);
    }
    fwt = FenwickTree(u.size());
    // b1 < a1 < a2 < b2
    sort(all(evt));
    for(auto t: evt) {
        int a, b, c;
        tie(a, b, c) = t;
        if(c) {
            ans += fwt.query(u.size()-1) - fwt.query(b);
        } else {
            fwt.add(b, 1);
        }
    }
    ans = 1LL * n * (n-1) / 2 - ans;
    cout << ans << '\n';
}
