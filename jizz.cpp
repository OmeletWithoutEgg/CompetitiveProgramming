#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 200025, inf = 1e9;

vector<pair<int,int>> g[maxn];
vector<int> prv[maxn];
int dis[maxn];
void solve() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) g[i].clear();
    vector<pair<int,int>> edges(m);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        edges[i] = {a, b};
        g[a].emplace_back(b, i);
        g[b].emplace_back(a, i);
    }

    for (int i = 0; i < n; i++) dis[i] = -1;
    queue<int> q;
    dis[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int i = q.front(); q.pop();
        for (auto [j, mid]: g[i]) {
            if (dis[j] == -1) {
                dis[j] = dis[i] + 1;
                q.push(j);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        auto [a, b] = edges[i];
        if (dis[a] == dis[b]) {
            ;
        }
    }

    int ans = 0;
    cout << ans << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
}

/*
7

8 10
1 2
1 3
1 4
1 5
2 6
3 7
4 8
5 8
6 7
8 8

10 11
1 2
1 5
1 6
2 3
3 4
4 5
4 10
6 7
7 8
8 9
9 9

13 15
1 2
1 5
1 6
2 3
3 4
4 5
6 7
7 8
7 11
8 9
9 10
10 11
11 12
11 13
12 13

16 18
1 2
1 7
1 8
2 3
3 4
4 5
5 6
6 7
8 9
9 10
9 15
9 16
10 11
11 12
12 13
13 14
14 15
14 16

21 22
1 2
1 9
1 12
2 3
3 4
4 5
5 6
6 7
7 8
7 11
8 9
8 10
12 13
13 14
13 21
14 15
15 16
16 17
17 18
18 19
19 20
20 21

20 26
1 2
1 5
1 6
2 3
3 4
4 5
4 7
6 8
8 9
8 11
8 12
8 13
8 14
8 15
8 16
8 17
9 10
10 18
11 18
12 19
13 20
14 20
15 20
16 20
17 20
19 20

24 31
1 2
1 7
1 8
2 3
3 4
4 5
5 6
6 7
6 9
8 10
10 11
10 16
10 17
10 18
10 19
10 20
11 12
12 13
13 14
14 15
15 16
15 17
15 18
15 19
15 20
15 21
15 22
15 23
15 24
21 22
23 24
*/
