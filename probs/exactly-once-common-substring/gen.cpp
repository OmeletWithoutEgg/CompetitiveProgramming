#include <bits/stdc++.h>

using namespace std;

const int seed = 7122;
mt19937 rng(seed);
int gi(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rng);
}
bool dice(int x) { return gi(0, x-1) == 0; }
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
void gen(string filename, int maxn, int maxsum) {
    ofstream fout(filename);
    const int n = maxn==1 ? 1 : min( dice(4) ? gi(2, maxn) : (dice(3) ? gi(2, 2 * ceil(sqrt(maxsum))) : gi(2, 5)), maxn );
    const int mask = (1 << (dice(2) ? gi(2, 5) : dice(3) ? 26 : gi(10, 12))) - 1;
    const string ans = randStr(gi(1, maxsum/n), mask);
    const bool hasAns = !dice(4);
    const int sum = gi(ans.size() * n, maxsum);
    const vector<int> len = fixedSumNumbers(n*2, sum - ans.size() * n);
    int mx = 0, mn = 1e9;
    fout << n << '\n';
    for(int i = 0; i < n*2; i+=2) {
        int preLen = len[i], sufLen = len[i+1];
        string s;
        if(hasAns) {
            s = randStr(preLen, mask) + ans + randStr(sufLen, mask);
        } else {
            s = randStr(preLen + sufLen + ans.size(), mask);
        }
        fout << s << '\n';
        if(mx < s.size()) mx = s.size();
        if(mn > s.size()) mn = s.size();
    }
    fout.close();
    cerr << n << ' ' << sum << ' ' << mn << ' ' << mx << ' ' << mask << ' ' << hasAns << '\n';
}
void specialGen(string filename, vector<int> len) {
    ofstream fout(filename);
    int n = len.size();
    fout << n << '\n';
    for(int x: len) {
        string s = randStr(x, 3);
        fout << s << '\n';
    }
    fout.close();
}
signed main() {
    for(int i = 0; i < 3; i++)
        gen(format("%02d.in", i), 1, 1e5);
    for(int i = 3; i < 8; i++)
        gen(format("%02d.in", i), 20, 20);
    for(int i = 8; i < 15; i++)
        gen(format("%02d.in", i), 300, 300);
    for(int i = 15; i < 20; i++)
        gen(format("%02d.in", i), 3500, 3500);
    for(int i = 20; i < 30; i++)
        gen(format("%02d.in", i), 2e5, 2e5);
    specialGen("15.in", {1750, 1750});
    specialGen("16.in", {1000, 1000, 1000});
    specialGen("17.in", {1300, 1500});
    for(int i = 0; i < 30; i++) {
        string command = format("./sol < %02d.in > %02d.out", i, i);
        cerr << command << '\n';
        system(command.c_str());
    }
}
