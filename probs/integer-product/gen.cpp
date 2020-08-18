#include <bits/stdc++.h>

using namespace std;

signed main(int argc, char *argv[]) {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
    //assert(argc > 1);
    int n = atoi(argv[1]);
    int a = uniform_int_distribution<int>(1,n)(rnd);
    int b = uniform_int_distribution<int>(1,n)(rnd);
    vector<int> A(a),B(b);
    for(auto &x:A) x = uniform_int_distribution<int>(0,9)(rnd);
    A.back() = uniform_int_distribution<int>(1,9)(rnd);
    for(auto &x:B) x = uniform_int_distribution<int>(0,9)(rnd);
    B.back() = uniform_int_distribution<int>(1,9)(rnd);
    for(int i = a-1; i >= 0; i--) cout << A[i]; cout << '\n';
    for(int i = b-1; i >= 0; i--) cout << B[i]; cout << '\n';
}
