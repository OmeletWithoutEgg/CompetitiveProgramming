#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    map<int,int> cnt;
    map<int,set<int> > mp;
    int v;
    while(cin >> v[i] && v[i]) {
        if(cnt[v]) mp[cnt[v]].erase(v);
        cnt[v]++;
        mp[cnt[v]].insert(v);
        auto it = prev(mp.end());
        cout << it->ff << ' ' << *it->ss.begin() << '\n';
    }
}
