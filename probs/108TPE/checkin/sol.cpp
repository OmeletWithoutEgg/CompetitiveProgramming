#include <bits/stdc++.h>
using namespace std;
#define debug(args...) qqbx(#args, args);
template <typename H, typename ...T> void qqbx(const char *s, const H& h, T&&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#define pb emplace_back

#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

const int N = 1025;
vector<int> g[N];
bool vis[N];
int cnt;
void dfs(int i) {
    if(g[i].size() % 2 == 1) ++cnt;
    vis[i] = true;
    for(int j: g[i]) if(!vis[j]) dfs(j);
}
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int A, B, S, M, K;
    cin >> A >> B >> S >> M >> K;
    for(int i = 0; i < K; i++) {
        int a, b, m;
        cin >> a >> b >> m;
        b += A;
        g[a].pb(b), g[b].pb(a);
        /* cout << a << ' ' << b << '\n'; */
    }
    int n = B+A;
    int ans = 0;
    /* bool odd=true, even=true; */
    bool lone=false;
    int odd=0, even=0;
    int CC = 0;
    for(int i = 1; i <= n; i++) {
        if(g[i].size()==0) lone=true;
        /* else if(g[i].size() % 2 == 0) odd=false; */
        /* else even=false; */
        if(vis[i] || g[i].size() == 0) continue;
        ++CC;
        cnt = 0;
        dfs(i);
        if(cnt) ++odd;
        else ++even;
        assert(cnt % 2 == 0);
        ans += max(1, cnt/2);
    }
    debug(odd, even, lone, CC);
    cout << ans << '\n';
}
