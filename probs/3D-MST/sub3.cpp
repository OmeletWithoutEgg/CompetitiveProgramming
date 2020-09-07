#include <bits/stdc++.h>

using namespace std;

signed main() {
    int n;cin >> n;int x,y,z;
    vector<int> v;
    while(n--)cin>>x>>y>>z,v.push_back(x);
    sort(v.begin(),v.end());
    long long ans=0;
    for(int i = 1; i < v.size(); i++) ans+=1LL*(v[i]-v[i-1])*(v[i]-v[i-1]);
    cout<<ans<<'\n';
}
