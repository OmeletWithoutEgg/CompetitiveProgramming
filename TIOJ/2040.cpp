#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <iostream>
 
using namespace std;
const int N = 10025;

template <typename T> struct DQ {
    T q[256];
    unsigned char head, tail;
    T & front() { return q[head]; }
    T & back() { return q[tail-1]; }
    bool empty() { return head == tail; }
    void pop_front() {
        ++head;
    }
    void pop_back() {
        --tail;
    }
    void pb(T x) {
        q[tail++] = x;
    }
};
int dp[2][N];
DQ<int> r[N], c[N];
int getMn(DQ<int> &dq, int i) {
    while(!dq.empty() && (dq.front() & 65535) < i) dq.pop_front();
    return dq.empty() ? 10000 : dq.front() >> 16;
}
void add(DQ<int> &dq, int v, int i) {
    while(!dq.empty() && (dq.back() >> 16) >= v) dq.pop_back();
    dq.pb(v << 16 | i);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string a, b;
    int L, k;
    cin >> a >> b >> L >> k;
    int n = a.size(), m = b.size();
    if(abs(n - m) > L * k) return cout << "Impossible\n", 0;
    for(int i = 0; i <= n; i++) {
        for(int j = max(0, i - k * L - 1); j <= m && j <= i + k * L + 1; j++) {
            dp[i & 1][j] = (i || j ? k+1 : 0);
            if(i && j && a[i-1] == b[j-1])
                dp[i & 1][j] = min(dp[i & 1][j], dp[~i & 1][j-1]);
            dp[i & 1][j] = min(dp[i & 1][j], getMn(c[j], i-L) + 1);
            dp[i & 1][j] = min(dp[i & 1][j], getMn(r[i], j-L) + 1);
            add(c[j], dp[i & 1][j], i);
            add(r[i], dp[i & 1][j], j);
            /* if(i >= L) dp[i][j] = min(dp[i][j], dp[i-L][j] + 1); */
            /* if(j >= L) dp[i][j] = min(dp[i][j], dp[i][j-L] + 1); */
        }
    }
    if(dp[n & 1][m] <= k)
        cout << dp[n & 1][m] << '\n';
    else
        cout << "Impossible\n";
}
