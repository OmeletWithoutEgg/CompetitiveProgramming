#include <bits/stdc++.h>

using namespace std;

int t,n;
pair<int,int> d[20010];
int lis[20010];
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 0; i < n; i++) cin >> d[i].first >> d[i].second;
        sort(d,d+n,[](pair<int,int> &a,pair<int,int> &b){
            return a.first!=b.first ? a.first<b.first : a.second>b.second;
        });
        fill(lis,lis+n,1e9);
        for(int i = 0; i < n; i++) *lower_bound(lis,lis+n,d[i].second) = d[i].second;
        cout << lower_bound(lis,lis+n,1e9)-lis << '\n';
    }
}
