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
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(vector, "[", "]", e)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}

using std::queue, std::cin, std::cout, std::min;

const int N = 3025, inf = 1e9;

int dis[N], dist;
int n;
int a[N], b[N];
int rest[N*N/2];
int encode(int a, int b) { // b < a
    return a*(a-1)/2 + b;
}
bool BFS() {
    for(int i = 0; i < n; i++) dis[i] = -1;
    queue<int> q;
    for(int i = 0; i < n; i++)
        if(b[i] > 0)
            dis[i] = 1, q.push(i);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        for(int j = 0; j < i; j++)
            if(a[i] % a[j] == 0) {
                if(dis[j] == -1)
                    dis[j] = dis[i] + 1, q.push(j);
            }
        for(int j = i+1; j < n; j++)
            if(rest[encode(j, i)] > 0 && a[j] % a[i] == 0)
                if(dis[j] == -1)
                    dis[j] = dis[i] + 1, q.push(j);
    }
    dist = -1;
    for(int i = 0; i < n; i++) if(dis[i] != -1 && b[i] < 0) {
        if(dist == -1 || dist > dis[i] + 1)
            dist = dis[i] + 1;
    }
    return dist != -1;
}
int cur[N];
int DFS(int i = -1, int lim = inf) {
    int ans = 0;
    if(i == -1) {
        for(int j = 0; j < n; j++) cur[j] = 0;
        for(int j = 0; j < n && lim > 0; j++)
            if(b[j] > 0 && dis[j] == 1) {
                int f = DFS(j, b[j]);
                ans += f;
                lim -= f;
                b[j] -= f;
            }
        return ans;
    }
    // if(vis[i]) return 0;
    // vis[i] = true;
    if(b[i] < 0 && dis[i] + 1 == dist) {
        int f = min(lim, -b[i]);
        ans += f;
        lim -= f;
        b[i] += f;
    }
    for(int &j = cur[i]; j < n && lim > 0; j++)
        if(j != i && (j < i ? a[i] % a[j] == 0 : a[j] % a[i] == 0) && dis[j] == dis[i] + 1) {
            int cap = j < i ? inf : rest[encode(j, i)];
            int f = DFS(j, min(lim, cap));
            ans += f;
            lim -= f;
            if(j > i)
                rest[encode(j, i)] -= f;
            else
                rest[encode(i, j)] += f;
        }
    return ans;
}
int maxFlow() {
    int ans = 0;
    while(BFS()) {
        while(int f = DFS()) ans += f;
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
