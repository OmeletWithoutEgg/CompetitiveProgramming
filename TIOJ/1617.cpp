#include <bits/stdc++.h>
#include "lib1617.h"

using namespace std;

signed main(){
    int n = Get_Box();
    if(n == 1)return Report(1),0;
    int mx = 1, mi = 2;
    for(int i = 3;i <= n;i++){
        int tmp = Med3(mx,mi,i);
        if(tmp == mx) mx = i;
        if(tmp == mi) mi = i;
    }
    vector<int> v;
    for(int i = 1;i <= n;i++) if(i!=mx && i!=mi) v.push_back(i);
    nth_element(v.begin(),v.begin()+n/2-1,v.end(),[mx](int a,int b){
        int tmp = Med3(a,b,mx);
        return tmp != b;
    });
    Report(v[n/2-1]);
}
