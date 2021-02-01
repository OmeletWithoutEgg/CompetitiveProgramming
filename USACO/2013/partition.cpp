#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define TAK(args...) std::ostream & operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { int f=0; O << BEG; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }

NIE(vector, "[", "]", e);
#else
#define debug(...) ((void)0)
#endif // local

#define pb emplace_back

using namespace std;
const int inf = 1e9;

int v[16][16];
signed main() {
#ifdef local
    auto &fin = cin;
    auto &fout = cout;
#else
    ifstream fin("partition.in");
    ofstream fout("partition.out");
#endif
    int n, k;
    fin >> n >> k;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            fin >> v[i][j];
    auto calc = [&](int mask, int rest) {
        if(rest < 0) return inf;
        vector<vector<int>> sum;
        sum.pb(n);
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                sum.back()[j] += v[i][j];
            if(mask >> i & 1)
                sum.pb(n);
        }
        debug(sum);
        auto ok = [&](int x, bool dbg=false) {
            int cnt = 0;
            vector<int> now(sum.size());
            for(int j = 0; j < n; j++) {
                bool tooBig = false;
                for(int i = 0; i < sum.size(); i++) {
                    if(sum[i][j] > x) return false;
                    if(dbg)
                        debug(now[i] + sum[i][j], x);
                    if(now[i] + sum[i][j] > x)
                        tooBig = true;
                }
                debug(tooBig);
                if(tooBig) {
                    ++cnt;
                    for(int i = 0; i < sum.size(); i++)
                        now[i] = 0;
                    debug(now);
                }
                for(int i = 0; i < sum.size(); i++)
                    now[i] += sum[i][j];
                if(dbg)
                    debug(now);
            }
            return cnt <= rest;
        };
        int ans = -1;
        for(int s = 1<<15; s; s>>=1) if(!ok(ans + s)) ans += s;
        ++ans;
        debug(ans, ok(ans, true));
        return ans;
    };
    int ans = inf;
    for(int s = 0; s < (1<<n-1); s++)
        ans = min(ans, calc(s, k - __builtin_popcount(s)));
    fout << ans << '\n';
}
