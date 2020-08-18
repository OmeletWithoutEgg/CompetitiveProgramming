#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
typedef long long ll;

int n,k,v[1<<20];
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n >> k) {
        for(int i = 0; i < n; i++) cin >> v[i];
        nth_element(v,v+n-k,v+n);
        cout << v[n-k] << '\n';
    }
}

