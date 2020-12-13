#include <bits/stdc++.h>
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
const int N = 50025;

int R[N];
array<int,11> S[N];
signed main() {
#ifndef local
    freopen("cbs.in", "r", stdin);
    freopen("cbs.out", "w", stdout);
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    int k, n;
    cin >> k >> n;
    for(int j = 0; j <= n; j++) R[j] = n, S[j][k] = j;
    for(int i = 0; i < k; i++) {
        string s;
        cin >> s;
        int sum = 0;
        for(int j = 1; j <= n; j++) {
            sum += (s[j-1] == '(' ? 1 : -1);
            S[j][i] = sum;
        }
        vector<pair<int,int>> dq;
        for(int j = n; j >= 0; j--) {
            while(dq.size() && dq.back().first >= S[j][i]) dq.pop_back();
            if(dq.size()) R[j] = min(R[j], dq.back().second);
            dq.pb(S[j][i], j);
        }
    }
    vector<array<int,11>> u(S, S+n+1);
    sort(all(u));
    long long ans = 0;
    /* auto pr = [&](string t, array<int,11> x) { */
    /*     cerr << t; */
    /*     for(int j = 0; j <= k; j++) */
    /*         cerr << x[j] << ' '; */
    /*     cerr << '\n'; */
    /* }; */
    for(int i = 0; i <= n; i++) {
        array<int,11> l = S[i],  r = S[i];
        l[k] = i;
        r[k] = R[i];
        /* pr("l = ", l); */
        /* pr("r = ", r); */
        /* for(auto p: u) { */
        /*     if(l < p && p <= r) { */
        /*         pr("p = ", p); */
        /*         ++ans; */
        /*     } */
        /* } */
        ans += upper_bound(all(u), r) - upper_bound(all(u), l);
    }
    cout << ans << '\n';
}
