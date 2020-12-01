#include <bits/stdc++.h>
using namespace std;
signed main(int argc, char **argv) {
    if(argc < 2) return 0;
    int N = atoi(argv[1]);
    int C = atoi(argv[2]);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int n = uniform_int_distribution<int>(1, N)(rng);
    vector<int> pa(n), pa_d(n), perm(n);
    for(int i = 1; i < n; i++) {
        pa[i] = uniform_int_distribution<int>(0,i-1)(rng);
        pa_d[i] = uniform_int_distribution<int>(1,C)(rng);
    }
    iota(perm.begin(), perm.end(), 1);
    shuffle(perm.begin(), perm.end(), rng);
    cout << n << '\n';
    for(int i = 1; i < n; i++) {
        int a = perm[i], b = perm[pa[i]], c = pa_d[i];
        cout << a << ' ' << b << ' ' << c << '\n';
    }
}
