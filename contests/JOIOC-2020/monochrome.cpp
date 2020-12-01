#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename H, typename ...T> void qqbx(const char *s, const H&h, T&&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
using namespace std;
typedef long long ll;
const int N = 200025;

#define int ll
int result[N];
array<vector<int>,2> ID;
int n;
int calc(int offset) {
    offset = (offset%n+n)%n;
    if(result[offset] != -1) return result[offset];
    auto id = ID;
    rotate(id[0].begin(), id[0].begin()+offset, id[0].end());
    vector<pair<int,int>> e;
    for(int i = 0; i < n; i++) {
        int a = id[0][i];
        int b = id[1][i];
        if(a > b) swap(a,b);
        e.pb(a, b);
    }
    sort(e.begin(), e.end());
    int ans = 0;
    vector<int> sum(n*2+1);
    auto qry = [&sum](int p) {
        int res = 0;
        for(++p; p > 0; p-=p&-p) res += sum[p];
        return res;
    };
    auto add = [&sum](int p) {
        for(++p; p < sum.size(); p+=p&-p) ++sum[p];
    };
    for(int i = 0; i < n; i++) {
        int l = e[i].first, r = e[i].second;
        ans += qry(r-1) - qry(l-1);
        add(r);
    }
    return result[offset] = ans;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> n >> s;
    for(int i = 0; i < n*2; i++) ID[s[i]=='B'].pb(i);
    for(int i = 0; i < n; i++) result[i] = -1;
    int l = 0, r = n;
    while(r-l > 3) {
        int m = l+(r-l)/2;
        if(calc(m-1) < calc(m) && calc(m) > calc(m+1)) return cout << calc(m) << '\n', 0;
        if(calc(l) < calc(l+1)) {
            if(calc(m) > calc(m-1)) {
                l = m;
            } else {
                r = m;
            }
        } else {
            if(calc(m) < calc(m-1)) {
                r = m;
            } else {
                l = m;
            }
        }
    }
    int mx = 0;
    for(int i = l; i <= r; i++) mx = max(mx, calc(i));
    cout << mx << '\n';
}
