#include <bits/stdc++.h>
using namespace std;

int main() {
    freopen("in/02.txt", "r", stdin);
    cin >> n >> m;
    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for(int i = 0; i < L; i++) {
        cin >> x[i] >> y[i];
    }
    for(int i = 0; i < L; i++) {
        for(int j = 0; j < i; j++)
    }
}
