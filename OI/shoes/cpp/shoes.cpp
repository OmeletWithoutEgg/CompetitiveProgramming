//#include "shoes.h"
#include <bits/stdc++.h>

using namespace std;

long long count_swaps(std::vector<int> s) {
    {
        int cnt = 0;
        vector<int> id(s.size());
        map<int,vector<int>> mp;
        for(int i = int(s.size())-1; i >= 0; i--) mp[s[i]].push_back(i);
        for(int i = 0; i < int(s.size()); i++) {
            if(id[i]) continue;
            int S = abs(s[i]);
            int a = mp[S].back(), b = mp[-S].back();
            id[b] = ++cnt, id[a] = ++cnt;
            mp[S].pop_back(), mp[-S].pop_back();
        }
        s = id;
    }
    //for(int x: s) cout << x << ' '; cout << '\n';
    std::reverse(s.begin(), s.end());
    std::vector<int> BIT(s.size()+1);
    auto query = [&BIT](int p){
        int res = 0;
        for(; p>0; p-=p&-p) res += BIT[p];
        return res;
    };
    auto add = [&BIT](int p){
        for(; p<int(BIT.size()); p+=p&-p) ++BIT[p];
    };
    long long ans = 0;
    for(int x: s) ans += query(x-1), add(x);
    return ans;
}
