#include "lib1740.h"
#include <bits/stdc++.h>

using namespace std;
const int N = 100001;

int n, m, k, u[N], v[N], c[N];
int vis[N], top[N], use[N], pid[N];
vector<int> g[2][N];
void dfs(int i, int t, int p) {
    vis[i] = 1;
    top[i] = t;
    for(int id: g[1][i]) {
        int j = u[id]^v[id]^i;
        if(!vis[j]) {
            use[id] = 1;
            pid[j] = id;
            dfs(j, j, i);
        }
    }
    for(int id: g[0][i]) {
        int j = u[id]^v[id]^i;
        if(!vis[j]) {
            use[id] = 1;
            pid[j] = id;
            dfs(j, top[i], i);
        }
    }
}
bool add(int id) {
    int a = u[id], b = v[id];
}
int main() {
    Init(n, m, k, u, v, c);
    for(int i = 0; i < m; i++) {
        g[c[i]][u[i]].push_back(i);
        g[c[i]][v[i]].push_back(i);
    }
    for(int i = 1; i <= n; i++) if(!vis[i]) dfs(i, i, 0);
    int cnt = 0;
    for(int i = 0; i < m; i++) if(used[i]) ++cnt;
    for(int i = 0; i < m && cnt < k; i++) if(c[i] == 0 && add(i)) ++cnt;
    if(cnt != k) NoSolution();
    else for(int i = 0; i < m; i++)
}
