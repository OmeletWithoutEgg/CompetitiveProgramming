#include <bits/stdc++.h>
//#include "lib1965.h"

using namespace std;
typedef uint64_t ll;
const ll N = 1000000, K = __lg(N)+1;
ll V[N];
ll sp[N/K][__lg(N/K)+1];
ll pre[N], suf[N];
ll best;

void init(int n,ll C[]){
    for(int i=0;i<n;i++)V[i] = C[i];
    for(int i = 0;i < n;i++){
        if(i%K == 0) best = 0;
        pre[i] = best = max(best,C[i]);
    }
    for(int i = n-1;i >= 0;i--){
        if(i%K == (n-1)%K) best = 0;
        suf[i] = best = max(best,C[i]);
    }
    // sparse table
    for(int i = 0;i < n/K;i++) sp[i][0] = 0;
    for(int i = 0;i < n;i++)
        if(sp[i/K][0]<C[i])
            sp[i/K][0] = C[i];
    for(int lg = 1;(1<<lg) < n/K;lg++)
        for(int i = 0;i < n/K;i++)
            sp[i][lg] = i+(1<<lg-1) < n/K ? max(sp[i][lg-1],sp[i+(1<<lg-1)][lg-1])
                                          : sp[i][lg-1];
}
ll RMQ(int l,int r){
    int lid = (l-1)/K+1;
    int rid = r/K;
    ll res = 0;
    if(rid > lid){
        int lg = __lg(rid-lid), d = 1<<lg;
        res = max(sp[lid][lg],sp[lid+d][lg]);
        res = max({res,pre[r-1],suf[l]});
        return res;
    }
    return *max_element(V+l,V+r);
}
/*
signed main(){
    int n,q,x,y;
    ll C[500];
    cin >> n >> q;
    for(int i=0;i<n;i++) cin >> C[i];
    init(n,C);
    for(int i=0;i<q;i++) cin >> x >> y, cout << RMQ(x,y) << '\n';
}
*/
