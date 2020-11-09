#include <bits/stdc++.h>

using namespace std;

signed main() {
    for(int i = 0, s = 0; i < 8; i++, s += 6) {
#define ou(a, b) cout << s+a << ' ' << s+b << '\n';
        ou(0, 2);
        ou(1, 4);
        ou(3, 5);
    }
}
