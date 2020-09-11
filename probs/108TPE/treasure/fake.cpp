#include <bits/stdc++.h>
using namespace std;
#define debug(x) std::cerr<<#x<<" = "<<x<<'\n'

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

const int N = 105, inf = 1e9;
int v[N][N];
int dp[N][N], fr[N][N];
signed main() {
    TIME;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }
    int ans = 0;
    for(int t = 0; t < 2; t++) {
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) dp[i][j] = -inf, fr[i][j] = 0;
        dp[0][0] = v[0][0];
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                if(v[i][j] == -1) continue;
                if(i) {
                    if(dp[i][j] < dp[i-1][j] + v[i][j]) {
                        dp[i][j] = dp[i-1][j] + v[i][j];
                        fr[i][j] = -1;
                    }
                }
                if(j) {
                    if(dp[i][j] < dp[i][j-1] + v[i][j]) {
                        dp[i][j] = dp[i][j-1] + v[i][j];
                        fr[i][j] = 1;
                    }
                }
            }
        }
        if(fr[n-1][m-1] == 0) return cout << 0 << '\n', 0;
        ans += dp[n-1][m-1];
        int i = n-1, j = m-1;
        while(i || j) {
            v[i][j] = 0;
            int f = fr[i][j];
            if(f == 1) --j;
            else if(f == -1) --i;
            else return 3;
        }
        v[i][j] = 0;
    }
    cout << ans << '\n';
}
