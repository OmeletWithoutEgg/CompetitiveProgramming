#include <bits/stdc++.h>

using namespace std;

const int seed = 7122;
mt19937 rng(seed);
int gi(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}
string randStr(int n, int mask) {
    string res, valid;
    for(int i = 0; i < 26; i++) if(mask >> i & 1) valid += char('a'+i);
    for(int i = 0; i < n; i++) res += valid[gi(0, valid.size()-1)];
    return res;
}
template <typename ...T> string format(const char *F, T ...args) {
    const int B = 1<<10;
    char buf[B] = {};
    sprintf(buf, F, args...);
    return string(buf);
}
vector<int> fixedSumNumbers(int n, int s) {
    vector<int> p{0, s}, res;
    for(int i = 0; i < n-1; i++) p.emplace_back(gi(0, s));
    sort(p.begin(), p.end());
    for(int i = 1; i <= n; i++) res.emplace_back(p[i] - p[i-1]);
    return res;
}
int tot;
void gen(int subtask, int maxn, int maxsum, bool hasAns) {
    if(subtask != 0) {
        string filename = format("%02d.in", tot++);
        cerr << filename << '\n';
        freopen(filename.c_str(), "w", stdout);
    }
    const int mask = (1<<16) - 1;
    int n = subtask ? gi(1, maxn) : maxn;
    string ans = randStr(gi(1, maxsum/n), mask);
    int s = gi(ans.size() * n, maxsum);
    vector<int> len = fixedSumNumbers(n*2, s - ans.size() * n);
    cout << n << '\n';
    int mx = 0, mn = 1e9;
    for(int i = 0; i < n*2; i+=2) {
        int preLen = len[i], sufLen = len[i+1];
        string s;
        if(hasAns) {
            s = randStr(preLen, mask) + ans + randStr(sufLen, mask);
        } else {
            s = randStr(preLen + sufLen + ans.size(), mask);
        }
        cout << s << '\n';
        if(mx < s.size()) mx = s.size();
        if(mn > s.size()) mn = s.size();
    }
    cerr << n << ' ' << s << ' ' << mn << ' ' << mx << ' ' << hasAns << '\n';
}
signed main() {
    gen(1, 1, 100, 0);
    gen(1, 1, 5e4, 0);
    gen(1, 1, 1e5, 1);

    gen(2, 20, 20, 0);
    gen(2, 20, 20, 1);
    gen(2, 20, 20, 0);

    gen(3, 400, 400, 0);
    gen(3, 400, 5000, 0);
    gen(3, 5000, 5000, 0);

    gen(4, 2000, 5000, 1);
    gen(4, 1e5, 1e5, 1);
    gen(4, 2e3, 2e5, 0);
    gen(4, 20, 2e5, 0);
    gen(4, 10, 2e5, 1);
    gen(4, 5, 2e5, 0);
    gen(4, 20, 2e5, 0);
    gen(4, 10, 2e5, 0);
    gen(4, 5, 2e5, 1);
    gen(4, 20, 2e5, 0);
    gen(4, 10, 2e5, 0);
    gen(4, 5, 2e5, 1);

    freopen("sample-1.in", "w", stdout);
    gen(0, 1, 13, 0);
    freopen("sample-2.in", "w", stdout);
    gen(0, 6, 20, 0);
    freopen("sample-3.in", "w", stdout);
    gen(0, 3, 10, 1);
    for(int i = 0; i < tot; i++) {
        string command = format("./sol < %02d.in > %02d.out", i, i);
        cerr << command << '\n';
        system(command.c_str());
    }
    for(int i = 1; i <= 3; i++) {
        string command = format("./sol < sample-%d.in > sample-%d.out", i, i);
        cerr << command << '\n';
        system(command.c_str());
    }
}
