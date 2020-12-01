#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
using namespace std;
long long calc(long long n, long long x, long long m) {
    long long ans = 1;
    while(n) {
        ans = ans * (x+1) % m;
        if(n & 1) ans = (ans + x) % m;
        x = x*x%m;
        n >>= 1;
    }
    cout << "ans = " << ans << '\n';
    return ans;
}

signed main() {
  int q, x, l, r, m;
  cin >> q;
  while(q--) {
    cin >> x >> l >> r >> m;
    cout << (calc(x, r, m) - calc(x, l-1, m) + m) % m << '\n';
  }
}
/*
2 + 4 + 8 + 16
*/
