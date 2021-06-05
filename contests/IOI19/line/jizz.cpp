#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename H, typename ...T> void qqbx(const char *s, const H&h, T &&...args) {
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
#define all(v) begin(v),end(v)

using namespace std;
typedef long double ld;

template <typename ...T> string format(const char *s, T&& ...args) {
    static char buf[1<<10];
    sprintf(buf, s, args...);
    return string(buf);
}

pair<int,vector<array<int,2>>> take(vector<array<int,2>> &v) {
    int n = v.size();
    vector<int> lisPre(n);
    vector<int> lis, lisId;
    for (int i = 0; i < n; i++) {
        auto it = lower_bound(all(lis), v[i][1]);
        int j = it - lis.begin();
        lisPre[i] = j ? lisId[j-1] : -1;
        if (it == lis.end())
            lis.push_back(v[i][1]), lisId.push_back(i);
        else
            *it = v[i][1], lisId[j] = i;
    }
    vector<int> ldsPre(n);
    vector<int> lds, ldsId;
    for (int i = n-1; i >= 0; i--) {
        auto it = lower_bound(all(lds), v[i][1]);
        int j = it - lds.begin();
        ldsPre[i] = j ? ldsId[j-1] : -1;
        if (it == lds.end())
            lds.push_back(v[i][1]), ldsId.push_back(i);
        else
            *it = v[i][1], ldsId[j] = i;
    }

    int type = 0;
    if (lds.size() >= lis.size()) swap(lis, lds), swap(lisId, ldsId), swap(lisPre, ldsPre), type = 1;

    vector<bool> used(n);
    int cur = lisId.back();
    while (cur != -1) {
        used[cur] = true;
        cur = lisPre[cur];
    }
    vector<array<int,2>> result[2];
    for (int i = 0; i < n; i++)
        result[used[i]].push_back(v[i]);
    v = result[0];
    return { type, result[1] };
}

ostream & operator<<(ostream &O, array<int,2> x) {
    return O << '(' << x[0] << ',' << x[1] << ')';
}
bool onSeg(array<int,2> a, array<int,2> b, array<int,2> c) {
    if (a > b) swap(a, b);
    if (a[0] == b[0] && b[0] == c[0])
        return a[1] <= c[1] && c[1] <= b[1];
    if (a[1] == b[1] && b[1] == c[1])
        return a[0] <= c[0] && c[0] <= b[0];
    exit(3);
    return false;
}
void solve(string inFile, string outFile) {
// #define fin cin
// #define fout cout
    cerr << inFile << '\n';
    ifstream fin(inFile);
    ofstream fout(outFile);
    int n;
    fin >> n;
    vector<array<int,2>> pts(n), ans;
    for(int i = 0; i < n; i++) fin >> pts[i][0] >> pts[i][1];
    sort(all(pts));

    int inf = 0;
    for (int i = 0; i < n; i++)
        inf = max({ inf, pts[i][0], pts[i][1] });
    inf += 1;
    array<int,2> cur = {}, last = cur;
    int cnt = 0;
    int d = 0;
    while (pts.size()) {
        auto [type, LIS] = take(pts);
        // LIS[0][0], (type ? inf : 0) -> LIS[0][0], LIS[1][1] -> LIS[2][0], LIS[1][1] -> LIS[2][0], LIS[3][1]
        // (type ? inf : 0), LIS[0][1] -> LIS[1][0], LIS[0][1] -> LIS[1][0], LIS[2][1] -> LIS[3][0], LIS[2][1]
        if (type == 0) {
            // LIS
            if (cur[0] == 0 || cur[1] == 0) {
                int d = (cur[0] == 0);
                for (auto p: LIS) {
                    cur[d] = p[d];
                    ans.pb(cur);
                    d = !d;
                }
                cur[d] = inf;
                ans.pb(cur);
            } else {
                reverse(all(LIS));
                int d = (cur[0] == inf);
                for (auto p: LIS) {
                    cur[d] = p[d];
                    ans.pb(cur);
                    d = !d;
                }
                cur[d] = 0;
                ans.pb(cur);
            }
        } else {
            if (cur[0] == 0 || cur[1] == inf) {
                int d = (cur[0] == 0);
                for (auto p: LIS) {
                    cur[d] = p[d];
                    ans.pb(cur);
                    d = !d;
                }
                cur[d] = d ? 0 : inf;
                ans.pb(cur);
            } else {
                reverse(all(LIS));
                int d = (cur[0] == inf);
                for (auto p: LIS) {
                    cur[d] = p[d];
                    ans.pb(cur);
                    d = !d;
                }
                cur[d] = d ? inf : 0;
                ans.pb(cur);
            }
        }
        ++cnt;
    }
    debug(ans.size(), n, cnt);
    fout << ans.size() << '\n';
    for (auto p: ans)
        fout << p[0] << ' ' << p[1] << '\n';
}
signed main() {
    solve(format("examples/%02d.in", 0), "tmp.out");
    for(int i = 1; i <= 10; i++) {
        solve(format("tests/%02d.in", i), format("submission/%02d.out.txt", i));
    }
}
