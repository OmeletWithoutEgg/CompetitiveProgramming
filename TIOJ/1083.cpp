#include <bits/stdc++.h>
#define pb push_back

using namespace std;

vector<int> a[2];
int len[43]={};
int main(){
    a[0].pb(1);
    len[0] = 1;
    for(int i = 1;i < 43;i++){
        int cnt=1;
        auto &v = a[!(i&1)];
        auto &u = a[i&1];
        for(int j = 0;j < v.size()-1;j++){
            if(v.at(j) == v.at(j+1))cnt++;
            else u.pb(cnt),u.pb(v.at(j)),cnt=1;
        }
        u.pb(cnt),u.pb(*v.rbegin());
        len[i] = u.size();v.clear();
    }
    int n;
    while(cin >> n,n--){
        cout << len[n] << ' ';
        cout << fixed << setprecision(6) << ((double)len[n-1] / len[n]) << '\n';
    }
    return 0;
}
