#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    int res = (1<<26) - 1;
    for(int i = 0; i < n; i++) {
        int mask = 0;
        string s;
        cin >> s;
        for(char c: s) mask |= 1 << c-'a';
        res &= mask;
    }
    if(res)
        cout << char('a' + __builtin_ctz(res & -res)) << '\n';
    else
        cout << 7122 << '\n';
}
