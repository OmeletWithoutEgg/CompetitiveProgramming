//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\Q
//   \###################\Q
//    \        ____       \B
//     \_______\___\_______\X
// An AC a day keeps the doctor away.
 
#include <queue>
#include <iostream>
#include <algorithm>

using std::queue, std::cin, std::cout, std::min;

const int N = 3025, inf = 1e9;

int dis[N], prv[N], dist, prvt;
int n;
int a[N], b[N];
int rest[N*N/2];
int encode(int a, int b) { // b < a
    return a*(a-1)/2 + b;
}
bool BFS() {
    for(int i = 0; i < n; i++) dis[i] = -1, prv[i] = -1;
    queue<int> q;
    for(int i = 0; i < n; i++)
        if(b[i] > 0)
            dis[i] = 1, q.push(i);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        for(int j = 0; j < i; j++)
            if(a[i] % a[j] == 0) {
                if(dis[j] == -1)
                    dis[j] = dis[i] + 1, prv[j] = i, q.push(j);
            }
        for(int j = i+1; j < n; j++)
            if(rest[encode(j, i)] > 0 && a[j] % a[i] == 0)
                if(dis[j] == -1)
                    dis[j] = dis[i] + 1, prv[j] = i, q.push(j);
    }
    dist = -1;
    for(int i = 0; i < n; i++) if(dis[i] != -1 && b[i] < 0) {
        if(dist == -1 || dist > dis[i] + 1)
            dist = dis[i], prvt = i;
    }
    return dist != -1;
}
int maxFlow() {
    int ans = 0;
    while(BFS()) {
        int f = abs(b[prvt]), x, last;
        for(x = prv[prvt], last = prvt; x != -1; last = x, x = prv[x]) {
            if(last < x) {
                // f = min(f, rest[encode(x, last)]);
            } else {
                f = min(f, rest[encode(last, x)]);
            }
        }
        f = min(f, b[last]);
        b[prvt] += f;
        for(x = prv[prvt], last = prvt; x != -1; last = x, x = prv[x]) {
            if(last < x) {
                rest[encode(x, last)] += f;
            } else {
                rest[encode(last, x)] -= f;
            }
        }
        b[last] -= f;
        ans += f;
    }
    return ans;
}
signed main() {
    for(int i = 0; i < N*N/2; i++) rest[i] = 0;
    /* for(int i = 0, cnt = 0; i < 5; i++) { */
    /*     for(int j = 0; j < i; j++) */
    /*         std::cerr << cnt++ << ',' << encode(i, j) << ' '; */
    /*     std::cerr << '\n'; */
    /* } */
    // std::cerr<<(encode(2999, 2998))<<' '<<N*N/2<<'\n';
    std::ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    // for(int i = 0; i < n; i++) a[i] = rand()%99+1;
    // for(int i = 0; i < n; i++) b[i] = rand()%60000-30000;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    int pos = 0;
    for(int i = 0; i < n; i++) if(b[i] > 0) pos += b[i];
    cout << pos - maxFlow() << '\n';
}
