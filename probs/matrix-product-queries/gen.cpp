#include <bits/stdc++.h>

using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int random(int l,int r) { // [l,r]
    return uniform_int_distribution<int>(l,r)(rng);
}
signed main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int Q = atoi(argv[2]);
    int W = atoi(argv[3]);
    int n = random(1,N);
    int q = random(1,Q);
    cout << n << ' ' << q << '\n';
    for(int i = 0; i < n; i++) {
        int x = random(1,W);
        cout << (random(0,1) ? x : -x);
        cout << " \n"[i+1==n];
    }
    for(int i = 0; i < q; i++) {
        int l = random(1,n), r = random(1,n);
        int x = random(0,W), y = random(0,W);
        if(l > r) swap(l,r);
        cout << l << ' ' << r << ' ' << x << ' ' << y << '\n';
    }
}
