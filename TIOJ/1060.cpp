#include <bits/stdc++.h>
#define N 300

using namespace std;
typedef long long ll;

inline ll h(ll x){
    ll tb[6] = {-1,-1,2,5,5,2};
    return x<2?-1LL:tb[x%6];
}
inline ll g(ll x){
    return x<=2?x*x-1:2LL;
}
signed main(){
    int x;
    auto f = [](ll x){
        ll res = 0,hx;
        while(x != (hx=h(x))){
            if(x > hx)res -= hx,--x;
            else res -= x=g(x);
        }
        return res+1;
    };
    cin >> x;
    cout << f(x) << '\n';
}
