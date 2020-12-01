#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
const int N = 15000000;

bitset<N> np;
vector<int> prs, emirp;
int rev(int x) {
    int r = 0;
    while(x) r = r*10+x%10, x/=10;
    return r;
}
int isp(int x) {
    if(x < N) return !np[x];
    for(int p: prs) {
        if(x%p == 0) return 0;
        if(p*p >= x) return 1;
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    np[1] = 1;
    for(int i = 2; i < N; i++) {
        if(!np[i]) prs.pb(i);
        for(int p: prs) {
            if(i*p >= N) break;
            np[i*p] = 1;
            if(i%p == 0) break;
        }
    }
    for(int i = 2; i < N; i++) if(!np[i]) {
        int j = rev(i);
        if(i != j && isp(j)) emirp.pb(i);
    }
    int t, n;
    cin >> t;
    while(t--) {
        cin >> n;
        cout << emirp[n-1] << '\n';
    }
}
