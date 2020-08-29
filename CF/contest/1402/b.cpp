#include <bits/stdc++.h>
#ifdef local
#define debug(...) QQBX(#__VA_ARGS__, __VA_ARGS__);
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
void QQBX(const char *s) {}
template <typename H, typename ...T> void QQBX(const char *s, const H& h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) QQBX(++s, args...);
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back

using namespace std;
typedef long long ll;
const int N = 100025, MOD = 1000000007;

struct point {
    ll x, y;
    friend istream& operator>>(istream &I, point &p) {
        return I >> p.x >> p.y;
    }
    friend ostream& operator<<(ostream &O, const point &p) {
        return O << p.x << ' ' << p.y;
    }
    friend point operator-(const point &a, const point &b) {
        return {a.x-b.x, a.y-b.y};
    }
    bool operator<(const point &rhs) const {
        return x!=rhs.x ? x<rhs.x : y<rhs.y;
    }
    friend point operator*(const point &a, const point &b) {
        return {a.x*b.y - a.y*b.x, a.x*b.x + a.y*b.y};
    }
};
array<point, 2> v[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> v[i][0] >> v[i][1];
    for(int i = 0; i < n; i++) if(v[i][1] < v[i][0]) swap(v[i][0], v[i][1]);
    point dif = v[0][1] - v[0][0];
    auto cmp = [dif](auto a, auto b) {
        a[0] = a[0] * dif, a[1] = a[1] * dif;
        b[0] = b[0] * dif, b[1] = b[1] * dif;
        return a < b;
    };
    sort(v, v+n, cmp);
    vector<pair<point,point>> ans;
    for(int i = 0, j; i < n; i = j) {
        for(j = i; j < n; j++) {
            if((v[i][0]*dif).x != (v[j][0]*dif).x) break;
            if(i != j) ans.pb(v[j-1][1], v[j][0]);
        }
        if(j != n) ans.pb(v[i][0], v[j][0]);
    }
    for(int i = 0; i < n-1; i++)
        cout << ans[i].first << ' ' << ans[i].second << '\n';
}
