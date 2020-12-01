#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
typedef long long ll;

signed main(){
    int t,n,m,stk[1001] = {},p = 0,r = 0;
    cin >> n >> m;
    for(int i = 0;i < n;i++){
        cin >> t;
        while(p && stk[p-1]>t)--p,++r;
        //cout << '{';for(int k = 0;k < p;k++)cout<<stk[p]<<',';cout<<"}\n";
        stk[p++] = t;
        if(p > m)return cout << "no\n",0;
    }
    cout << (r+p==n?"yes":"no") << '\n';
}


