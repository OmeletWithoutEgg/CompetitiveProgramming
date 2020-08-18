#include <bits/stdc++.h>
using namespace std;
// dynamic RMQ structure
map<int,long long> mp;
void init() {
    mp.clear();
}
long long get_max(int h) {
    auto it = mp.lower_bound(h);
    if(it == mp.begin()) return 0;
    else return prev(it)->second;
}
void ins(int h,long long dp) {
    auto it = mp.upper_bound(h);
    if(it != mp.begin() && prev(it)->second >= dp) return;
    while(it != mp.end() && it->second <= dp) mp.erase(it++);
    mp[h] = dp;
}

const int N = 200000;
int id[N],n,q,x;
long long w[N],h[N],f[N];
long long dp[2][N];
signed main(int argc,char *argv[]) {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> q;
    for(int i = 0; i < n; i++) cin >> w[i] >> h[i] >> f[i];

    for(int i = 0; i < n; i++) id[i] = i;
    sort(id,id+n,[](int a,int b){
        if(w[a] != w[b]) return w[a] < w[b];
        return h[a] > h[b];
    });

    init();
    for(int k = 0; k < n; k++) {
        int i = id[k], H = h[i];
        dp[0][i] = f[i] + get_max(H);
        ins(H,dp[0][i]);
    }

    init();
    for(int k = n-1; k >= 0; k--) {
        int i = id[k], H = 100001-h[i];
        dp[1][i] = f[i] + get_max(H);
        ins(H,dp[1][i]);
    }

    while(q--) {
        cin >> x;
        x--;
        cout << dp[0][x] + dp[1][x] - f[x] << '\n';
    }
}
