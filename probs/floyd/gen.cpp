#include <bits/stdc++.h>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
signed main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int M = atoi(argv[2]);
    int W = atoi(argv[3]);
    int n = uniform_int_distribution<int>(1,N)(rng);
    int m = uniform_int_distribution<int>(1,M)(rng);
    cout << n << ' ' << m << '\n';
    for(int i = 0; i < m; i++) {
        int a = uniform_int_distribution<int>(1,n)(rng);
        int b = uniform_int_distribution<int>(1,n)(rng);
        int w = uniform_int_distribution<int>(0,W)(rng);
        cout << a << ' ' << b << ' ' << w << '\n';
    }
    int q = uniform_int_distribution<int>(1,n*n)(rng);
    cout << q << '\n';
    for(int i = 0; i < q; i++) {
        int s = uniform_int_distribution<int>(1,n)(rng);
        int t = uniform_int_distribution<int>(1,n)(rng);
        cout << s << ' ' << t << '\n';
    }
}
