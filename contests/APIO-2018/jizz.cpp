#include <bits/stdc++.h>
#ifdef local
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> void qqbx(const char *s, const H &h, T ...args) {
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
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))

using namespace std;
typedef long long ll;
const int N = 100025;

int n, q, k;
int query(int x) {
    int r = 0;
    for(int s = 1<<30; s; s>>=1) if(qry(x-r-s, x+r+s+1) == k) r += s;
    return r;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    vector<tuple<int,int,int,int>> evt;
    vector<tuple<int,int,int,int>> Q(q);
    for(int i = 0; i < n; i++) {
        int x, t, a, b;
        cin >> x >> t >> a >> b;
        ++b;
        evt.pb(a, 0, t, x);
        evt.pb(b, 1, t, x);
    }
    for(int i = 0; i < q; i++) {
        auto &[t, y, id, ans] = Q[i];
        cin >> t >> y;
        id = i;
    }
    sort(evt.begin(), evt.end());
    sort(Q.begin(), Q.end());
    int it = 0;
    for(int i = 0, j = 0; i < evt.size(); i = j) {
        while(it < Q.size() && get<0>(Q[it]) < get<0>(evt[i])) {
            auto &[_, pos, id, ans] = Q[it++];
            ans = query(pos);
        }
        for(j = i; j < evt.size(); j++) {
            if(get<0>(evt[i]) != get<0>(evt[j])) break;
            auto [_, t, k, pos] = evt[j];
            if(t == 0) {
                add(s[k], pos);
            } else {
                del(s[k], pos);
            }
        }
    }
    sort(Q.begin(), Q.end(), [](auto &a, auto &b){return get<2>(a) < get<2>(b);});
    for(int i = 0; i < q; i++) cout << get<3>(Q[i]) << (i+1==q ? '\n' : ' ');
}
