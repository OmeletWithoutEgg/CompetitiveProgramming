#include <bits/stdc++.h>

using namespace std;
const int N = 1000001;

int n;
int encode(array<int,3> a) { sort(a.begin(), a.end()); return a[0] + a[1] * (n+2); }
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n && n) {
        array<int,3> a, b;
        vector<bool> vis((n+2)*(n+2));
        for(int i = 0; i < 3; i++) cin >> a[i];
        for(int i = 0; i < 3; i++) cin >> b[i];
        if(a[0]+a[1]+a[2] != b[0]+b[1]+b[2]) {
            cout << "No\n";
            continue;
        }
        int cnt = 0;
        queue<array<int,3>> q;
        vis[encode(a)] = true;
        q.push(a);
        while(!q.empty()) {
            array<int,3> nxt = q.front(); q.pop();
            for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) if(i!=j) {
                int x = nxt[i], y = nxt[j];
                nxt[i] = 2*y-x+1, nxt[j] = 2*x-y-1;
                if(nxt[i] >= 0 && nxt[i] <= n && nxt[j] >= 0 && nxt[j] <= n && !vis[encode(nxt)]) {
                    vis[encode(nxt)] = true;
                    ++cnt;
                    q.push(nxt);
                }
                nxt[i] = x, nxt[j] = y;
            }
            if(cnt >= N || vis[encode(b)]) break;
        }
        //debug(vis.size());
        if(vis[encode(b)])
            cout << "Yes\n";
        else
            cout << "No\n";
    }
}

