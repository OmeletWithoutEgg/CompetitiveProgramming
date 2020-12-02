/*
--------------              |   /
      |                     |  /
      |                     | /
      |             *       |/          |    |         ------            *
      |                     |           |    |        /      \
      |             |       |\          |    |       |       |\          |
   \  |             |       | \         |    |       |       | \         |
    \ |             |       |  \        |    |        \     /   \        |
     V              |       |   \        \__/|         -----     \       |
*/
#include <bits/stdc++.h>
using namespace std;

#define EmiliaMyWife ios::sync_with_stdio(0); cin.tie(NULL);
using ll = int64_t;
using ull = uint64_t;
using ld = long double;
using uint = uint32_t;
const double EPS  = 1e-8;
const int INF     = 0x3F3F3F3F;
const ll LINF     = 4611686018427387903;
const int MOD     = 1e9+7;
/*--------------------------------------------------------------------------------------*/

signed main() { EmiliaMyWife
        int n, q;
        cin >> n >> q;
        cerr<<q<<'\n';
        vector<int> nxt(n + 1), sz(n + 1, 1), pa(n + 1);
        for(int i = 1; i <= n; i++)
                nxt[i] = i + 1, pa[i] = i;
        const function<int(int)> fnd = [&] (int x) { return pa[x] == x ? pa[x] : pa[x] = fnd(pa[x]); };
        const auto uni = [&] (int a, int b) {
                if((a = fnd(a)) == (b = fnd(b)))
                        return;
                if(sz[a] > sz[b])
                        swap(a, b);
                sz[b] += sz[a];
                pa[a] = b;
        };
        int cnt = 0;
        const function<void(int, int)> que = [&] (int x, int y) {
                if(nxt[x] > y)
                        return;
                que(nxt[x], y);
                uni(x, nxt[x]);
                nxt[x] = nxt[nxt[x]];
                ++cnt;
        };
        int a, b, c;
        while(q--) {
                assert(cin >> a >> b >> c);
                if(a == 1)
                        uni(b, c);
                if(a == 2)
                        que(b, c);
                if(a == 3)
                        cout << (fnd(b) == fnd(c) ? "YES" : "NO") << '\n';
        }
        cerr << "cnt = " << cnt << '\n';
        /* for(int i = 1; i <= n; i++) cerr << nxt[i] << ' '; */
        cerr << '\n';
}
