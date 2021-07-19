#ifndef local
#include "lib1896.h"
#endif // !local

const int maxn = 1501;
int cnt[maxn];
void initialize(int n) {
    for (int i = 0; i < n; i++)
        cnt[i] = 0;
}

int hasEdge(int a, int b) {
    if (a < b) {
        int t = a; a = b; b = t;
    }
    return ++cnt[a] == a;
}
#ifdef local
#include <bits/stdc++.h>
using namespace std;
signed main() {
    int n;
    cin >> n;
    initialize(n);
    for (int i = 0, x, y; i < n*(n-1)/2; i++)
        cin >> x >> y, cout << hasEdge(x, y) << '\n';
}
#endif // local
