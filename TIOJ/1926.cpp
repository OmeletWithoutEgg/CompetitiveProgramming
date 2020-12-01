#include <bits/stdc++.h>

using namespace std;
using ll = long long;
#include "lib1926.h"
#define cmp Oshietekudasai // return <

int N;
ll M;
// Report
void solve(ll l, ll r) {
    ll m = l+(r-l)/2;
    int mn = 0;
    for(int i = 1; i < N; i++) {
        if(cmp(i, m, mn, m)) {
            mn = i;
        }
    }
    if(m != 0 && cmp(mn, m-1, mn, m)) solve(l, m);
    else solve();
    if((m == 0 || cmp(mn, m, mn, m-1)) && (m == M-1 || cmp(mn, m, mn, m+1))) {
        Report();
    }
}
signed main() {
    Init(&n, &m);
}
