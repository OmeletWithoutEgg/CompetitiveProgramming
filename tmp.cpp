#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define TAK(args...) std::ostream &operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { int f=0; O << BEG; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(vector, "[", "]", e)
template <typename T, size_t N> TAK(std::array<T,N> v) { return O << std::vector<T>(v.begin(), v.end()); }
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
using ld = double;
const int N = 100002;
const ll INF = 1e18;
const ld PI = acos(-1);

struct Restrict {
    int l, r, v;
    Restrict() {}
    Restrict(int l, int r, int v) : l(l), r(r), v(v) {}
    friend ostream & operator<<(ostream &O, Restrict &r) {
        return O << "x[" << r.r << "] <= x[" << r.l << "] + " << r.v;
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> u;
    u.pb(0);
    u.pb(n);
    vector<Restrict> R(m);
    for(int i = 0; i < m; i++) {
        int t;
        auto &[l, r, v] = R[i];
        cin >> t >> l >> r >> v;
        --l;
        u.pb(l);
        u.pb(r);
        if(t)
            swap(l, r), v = -v;
    }
    sort(all(u)), u.erase(unique(all(u)), end(u));
    for(int i = 0; i < m; i++) {
        auto &[l, r, v] = R[i];
        l = lower_bound(all(u), l) - begin(u);
        r = lower_bound(all(u), r) - begin(u);
    }
    for(int i = 1; i < u.size(); i++) {
        R.emplace_back(i-1, i, 9 * (u[i] - u[i-1]));
        R.emplace_back(i, i-1, i==1 ? -1 : 0);
    }
    debug(R);
    vector<int> dis(u.size(), 1e9);
    dis[0] = 0;
    for(int t = 0; t <= u.size(); t++) {
        bool relax = false;
        for(auto [l, r, v]: R)
            if(dis[r] > dis[l] + v) {
                dis[r] = dis[l] + v;
                relax = true;
                if(dis[r] < 0) return cout << -1 << '\n', 0;
            }
        if(!relax) break;
        if(t == u.size()) return cout << -1 << '\n', 0;
    }
    debug(dis);
    for(int i = 1; i < u.size(); i++) {
        int sum = dis[i] - dis[i-1], len = u[i] - u[i-1];
        for(int c = 0; c < len; c++)
            cout << min(9, sum), sum -= min(9, sum);
    }
    cout << '\n';
}
