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
int dp[N*2][N][N];
signed main() {
    TIME;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }
    for(int L = 0; L <= n+m-2; L++) {
        for(int i = 0; i < n; i++) {
            for(int a = 0; a < n; a++) {
                dp[L][i][a] = -inf;
            }
        }
    }
    dp[0][0][0] = v[0][0];
    for(int L = 1; L <= n+m-2; L++) {
        for(int i = 0; i < n; i++) {
            int j = L-i;
            if(j < 0 || j >= m || v[i][j] == -1) continue;
            for(int a = 0; a < n; a++) {
                int b = L-a;
                if(b < 0 || b >= m || v[a][b] == -1) continue;
                int value = i==a ? v[i][j] : v[i][j] + v[a][b];
                if(i && a) dp[L][i][a] = max(dp[L][i][a], dp[L-1][i-1][a-1] + value);
                if(i && b) dp[L][i][a] = max(dp[L][i][a], dp[L-1][i-1][a] + value);
                if(j && a) dp[L][i][a] = max(dp[L][i][a], dp[L-1][i][a-1] + value);
                if(j && b) dp[L][i][a] = max(dp[L][i][a], dp[L-1][i][a] + value);
            }
        }
    }
    /*
    for(int L = 1; L <= n+m-2; L++) {
        for(int i = 0; i < n; i++) {
            for(int a = 0; a < n; a++) {
                cout << dp[L][i][a] << (a+1==n ? '\n' : ' ');
            }
        }
        cout << "--------\n";
    }
    */
    int ans = dp[n+m-2][n-1][n-1];
    cout << max(0, ans) << '\n';
    cerr << max(0, ans) << '\n';
}
