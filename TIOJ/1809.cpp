#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
typedef long long ll;

int n,m,q;
ll a,b;
vector<ll> E;
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n >> m >> q;
    for(int i = 0; i < m; i++) {
        cin >> a >> b;
        if(a>b) b<<=32;
        else a<<=32;
        E.pb(a|b);
    }
    sort(begin(E),end(E));
    for(int i = 0; i < q; i++) {
        cin >> a >> b;
        if(a>b) b<<=32;
        else a<<=32;
        cout << (binary_search(begin(E),end(E),a|b) ? "yes\n" : "no\n");
    }
}
