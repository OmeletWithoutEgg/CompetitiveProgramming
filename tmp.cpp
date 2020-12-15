#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
const int N = 1000025;

bool banned[N];
vector<int> g[N];
int dis[N];
int BFS(int s, int t) {
    memset(dis, -1, sizeof dis);
    queue<int> q;
    dis[s] = 0;
    q.push(s);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        for(int j: g[i]) if(dis[j] == -1) dis[j] = dis[i] + 1, q.push(j);
    }
    return dis[t];
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int w, h, n, m;
    int xp, yp, xs, ys;
    cin >> w >> h >> n >> m;
    cin >> xp >> yp >> xs >> ys;
    vector<tuple<int,int,int,int>> rects(n);
    for(int i = 0; i < n; i++) {
        auto &[x1, y1, x2, y2] = rects[i];
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
    }
    vector<tuple<int,int,int,int>> evt;
    for(int i = 0; i < n; i++) {
        auto &[x1, y1, x2, y2] = rects[i];
        evt.pb(x1, 1, y2, i);
        evt.pb(x2, 0, y2, i);
    }
    evt.pb(xp, 2, yp, 1);
    evt.pb(xs, 2, ys, -1);
    for(int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        evt.pb(x, 2, y, 0);
    }
    int S, T;
    sort(all(evt));
    map<int, int> mp;
    for(auto [x, t, y, id]: evt) {
        if(t == 0) {
            mp.erase(y);
        } else if(t == 1) {
            mp[y] = id;
        } else if(t == 2) {
            int r = mp.lower_bound(y)->second;
            if(id == 1) {
                S = r;
            } else if(id == -1) {
                T = r;
            } else {
                banned[r] = true;
            }
        }
    }
    cerr << S << ' ' << T << '\n';
    vector<tuple<int,int,int>> L, R, D, U;
    for(int i = 0; i < n; i++) {
        auto [x1, y1, x2, y2] = rects[i];
        L.pb(x1, y2, i);
        R.pb(x2, y2, i);
        D.pb(y1, x2, i);
        U.pb(y2, x2, i);
    }
    sort(all(L));
    sort(all(R));
    sort(all(D));
    sort(all(U));
    auto go = [&](vector<tuple<int,int,int>> &v, int d, int c, int i) {
        auto it = lower_bound(all(v), make_tuple(d, c, 0));
        if(it != v.end() && get<0>(*it) == d) {
            int j = get<2>(*it);
            if(!banned[i] && !banned[j])
                g[i].pb(j), g[j].pb(i);
        }
    };
    for(int i = 0; i < n; i++) {
        auto [x1, y1, x2, y2] = rects[i];
        go(R, x1, y1+1, i);
        go(R, x1, y2, i);
        go(L, x2, y1+1, i);
        go(L, x2, y2, i);
        go(U, y1, x1+1, i);
        go(U, y1, x2, i);
        go(D, y2, x1+1, i);
        go(D, y2, x2, i);
    }
    cout << BFS(S, T) + 1 << '\n';
}
