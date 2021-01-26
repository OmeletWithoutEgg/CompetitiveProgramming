#include <bits/stdc++.h>

using namespace std;
using ld = long double;

signed main() {
    struct Item {
        int v, w;
    };
    int W, n;
    cin >> W >> n;
    vector<Item> e(n);
    for(int i = 0; i < n; i++) {
        int v, w;
        cin >> v >> w;
        e[i] = {v, w};
    }
    int ans = -1;
    int anscost = 0;
    auto take = [&]() {
        int val = 0, cost = 0;
        for(int i = 0; i < n; i++) {
            if(cost + e[i].w > W)
                continue;
            val += e[i].v;
            cost += e[i].w;
        }
        if(ans < val || (ans == val && anscost > cost))
            ans = val, anscost = cost;
    };
    mt19937 rng(812);
    do {
        shuffle(e.begin(), e.end(), rng);
        take();
    } while(clock() / CLOCKS_PER_SEC < 0.7);

    cout << ans << ' ' << anscost << '\n';
}
