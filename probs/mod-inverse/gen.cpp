#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char *argv[]) {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
    int M = atoi(argv[1]);
    int Q = atoi(argv[2]);
    int m = uniform_int_distribution<int>(2,M)(rnd);
    int q = uniform_int_distribution<int>(1,min(Q,m-1))(rnd);
    vector<int> x(q);
    for(int &t:x) t = uniform_int_distribution<int>(0,m-1)(rnd);
    cout << m << ' ' << q << '\n';
    for(int t:x) cout << t << '\n';
}
