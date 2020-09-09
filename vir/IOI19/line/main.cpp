
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
struct cmp {
    bool operator()(array<int,2> a, array<int,2> b) const {
        return a[1]!=b[1] ? a[1]<b[1] : a[0]<b[0];
    }
};
mt19937 rng(7122);
bool monotone(int a, int b, int c) {
    return (a <= b && b <= c) || (a >= b && b >= c);
}
void solve(string inFile, string outFile) {
    ifstream fin(inFile);
    ofstream fout(outFile);
    int n;
    fin >> n;
    vector<array<int,2>> pts(n), ans;
    for(int i = 0; i < n; i++) fin >> pts[i][0] >> pts[i][1];
    sort(all(pts));
    vector<vector<array<int,2>>> QQ;
    auto magic = [&](array<int,2> p) -> int {
        int f = p[0]+p[1];
        const int C = 10050, r = 50;
        return C-r <= f && f <= C+r;
    };
    for(int i = 0; i < n; i++) debug(pts[i][0]+pts[i][1]-10050);
    for(int i = 0; i < n; i++) {
        /* shuffle(QQ.begin(), QQ.end(), rng); */
        bool ok = false;
        for(int j = 0; QQ.size() && j < 100 && !ok; j++) {
            int c = QQ.size()<2 || j ? uniform_int_distribution<int>(0, QQ.size()-1)(rng) : magic(pts[i]);
            if(QQ[c].size() < 2 || monotone(QQ[c][QQ[c].size()-2][1],QQ[c].back()[1],pts[i][1]))
                QQ[c].pb(pts[i]), ok = true;
        }
        if(!ok) QQ.pb(1, pts[i]);
    }
    array<int,2> now{0, 0};
    bool d = 0;
    for(auto v: QQ) {
        now[d] = v[0][d];
        ans.pb(now);
        d = !d;
        /* cerr<<"-----\n"; */
        for(auto p: v) {
            now[d] = p[d];
            ans.pb(now);
            d = !d;
            /* cerr<<p[0]<<' '<<p[1]<<'\n'; */
        }
        now[d] = v.back()[d];
        ans.pb(now);
        d = !d;
    }
    ans.pb(QQ.back().back());
    debug(QQ.size());
    cerr << ans.size() / ld(n) << '\n';
    fout << ans.size() << '\n';
    for(auto v: ans) fout << v[0] << ' ' << v[1] << '\n';
    fin.close();
    fout.close();
    cerr << inFile << ' ' << outFile << '\n';
}
signed main() {
    solve(format("examples/%02d.in", 0), "tmp.out");
    for(int i = 2; i <= 2; i++) {
        solve(format("tests/%02d.in", i), format("submission/%02d.out", i));
    }
}
