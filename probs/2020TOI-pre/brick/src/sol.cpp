#include <bits/stdc++.h>

using namespace std;

#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

const int maxn = 2001, sigma = 3;
const int64_t INF = 1e18;
int id(char c) { return c=='r' ? 0 : c=='g' ? 1 : 2; }
struct AhoCorasick {
    int ch[maxn][sigma], fail[maxn], tot;
    int64_t score[maxn];
    void add(string S, int v) {
        int now = 0;
        for (char c: S) {
            c = id(c);
            if (!ch[now][c])
                ch[now][c] = ++tot;
            now = ch[now][c];
        }
        score[now] += v;
    }
    void build() {
        queue<int> q;
        for (int i = 0; i < sigma; i++)
            if (ch[0][i])
                q.push(ch[0][i]);
        while (!q.empty()) {
            int i = q.front(); q.pop();
            int f = fail[i];
            score[i] += score[f];
            for (int c = 0; c < sigma; c++) {
                if (int j = ch[i][c]) {
                    fail[j] = ch[f][c];
                    q.push(j);
                } else {
                    ch[i][c] = ch[f][c];
                }
            }
        }
    }
    int64_t solve(string T) {
        vector<int64_t> dp(tot+1, -INF);
        dp[0] = 0;
        for (char c: T) {
            vector<int64_t> ndp(tot+1, -INF);
            if (c == 'x') {
                for (int i = 0; i <= tot; i++) {
                    for (int d = 0; d < sigma; d++) {
                        int j = ch[i][d];
                        ndp[j] = max(ndp[j], dp[i] + score[j]);
                    }
                }
            } else {
                for (int i = 0; i <= tot; i++) {
                    int j = ch[i][id(c)];
                    ndp[j] = max(ndp[j], dp[i] + score[j]);
                }
            }
            dp = ndp;
        }
        return *max_element(dp.begin(), dp.end());
    }
} AC;

signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < k; i++) {
        string S;
        int w;
        cin >> S >> w;
        AC.add(S, w);
    }
    string T;
    cin >> T;
    AC.build();
    cout << AC.solve(T) << '\n';
}
