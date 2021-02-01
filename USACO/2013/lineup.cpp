#include <bits/stdc++.h>

using namespace std;

map<int,int> cnt;
int cntcnt[100001], mx, kind;
void add(int x, int d) {
    if(cnt[x] == 0 && d == 1) kind += 1;
    if(cnt[x] == 1 && d == -1) kind -= 1;
    --cntcnt[cnt[x]];
    cnt[x] += d;
    ++cntcnt[cnt[x]];
    if(cnt[x] > mx) mx = cnt[x];
    while(!cntcnt[mx]) --mx;
}
signed main() {
#ifndef local
    assert( freopen("lineup.in", "r", stdin) && freopen("lineup.out", "w", stdout) );
#endif
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++)
        cin >> a[i];
    cntcnt[0] = 1e9;
    int ans = 0;
    for(int i = 0, j = 0; i < n; i++) {
        add(a[i], 1);
        while(kind > k+1) {
            // can't obtain identical Breed ID by deleting at most k
            add(a[j++], -1);
        }
        ans = max(ans, mx);
    }
    cout << ans << '\n';
}
