#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define pb emplace_back

using namespace std;
typedef pair<int,int> pii;

int n;
vector<pii> tmp;
signed main(){
    cin >> n;
    for(int i = 2; i <= n; i++) for(int j = 1; j <= i; j++) if(__gcd(i,j) == 1) tmp.pb(j,i);
    sort(begin(tmp),end(tmp),[](pii &a,pii &b){return a.first*b.second<b.first*a.second;});
    cout << tmp.size() << '\n';
    pii ans = n<tmp.size() ? tmp[n-1] : tmp.back();
    cout << ans.first << '/' << ans.second << '\n';
}
