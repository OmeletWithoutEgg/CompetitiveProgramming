#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(a...) qqbx(#a, a)
#define pary(a...) danb(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\033[1;32m(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\033[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\033[1;32m[ " << s << " ] = [ ";
    for (auto it = L; it != R; ++it)
        std::cerr << *it << ' ';
    std::cerr << "]\033[0m\n";
}
#else
#define safe ((void)0)
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define pb emplace_back
#define sort_uni(v) sort(all(v)),v.erase(unique(all(v)), v.end())
#define get_pos(u,v) int(lower_bound(all(u), v) - u.begin())

using namespace std;
using ll = int64_t;
using ld = long double;
template <typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
const int maxn = 100, maxm = 10000;

int ans[maxn], cnt, p[maxn];
int ask(vector<int> a) {
#ifdef local
    sort(all(a), [](int x, int y){return ans[x] < ans[y];});
    cout<<++cnt<<' ';
    cout << "? " << a[0] << ' ' << a[1] << ' ' << a[2];
    cout << " -> " << a[1] << '\n';
    return a[1];
#endif // local
    cout << a[0] << ' ' << a[1] << ' ' << a[2] << '\n';
    int res;
    cin >> res;
    if (res == -1)
        exit(0);
    return res;
}
signed main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);
    int T, N, Q;
    cin >> T >> N >> Q;
#ifdef local
    for (int i = 1; i <= N; i++) ans[i] = i;
    shuffle(ans+1, ans+N+1, mt19937(7122));
    for (int i = 1; i <= N; i++) p[ans[i]] = i;
#endif // local
    for (int tc = 1; tc <= T; tc++) {
        cnt=0;
        // cout << "Case #" << tc << ": ";
        vector<int> v{ 1, 2 };
        for (int i = 3; i <= N; i++) {
            v.pb(i);
            int x = ask(v);
            v.erase(find(all(v), x));
        }
        pary(all(v));
        vector<int> rest;
        for (int i = 1; i <= N; i++)
            if (i != v[0] && i != v[1])
                rest.pb(i);
        stable_sort(all(rest), [&v](int a, int b){
            return ask({ v[0], a, b }) == a;
        });
        cout << v[0] << ' ';
        for (int i = 0; i < N - 2; i++)
            cout << rest[i] << ' ';
        cout << v[1] << '\n';

#ifdef local
        for (int i = 1; i <= N; i++)
            cout << p[i] << (i==N ? '\n' : ' ');
#else
        int verd;
        cin >> verd;
#endif // local
    }
}
