#include <bits/stdc++.h>

using namespace std;

int n;
pair<int,int> t[10000];
bool cmp(pair<int,int> a,pair<int,int> b){
    return a.second != b.second?a.second > b.second:a.first < b.first;
}
int main(){
    while(cin >> n, n){
        for(int i = 0;i < n;i++)cin >> t[i].first >> t[i].second;
        sort(t,t+n,cmp);
        int res = 0, mres = 0;
        for(int i = 0;i < n;i++)res += t[i].first,mres = max(mres,res + t[i].second);
        cout << mres << '\n';
    }
    return 0;
}
