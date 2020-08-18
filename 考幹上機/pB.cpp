#include <bits/stdc++.h>
#define MOD 1000000009
#define N 1000000

using namespace std;
typedef long long ll;

void muti(ll m[2][2],ll n[2][2],ll t[2][2]){
    t[0][0]=t[0][1]=t[1][0]=t[1][1]=0;
    for(int k = 0;k < 2;k++)
        for(int i = 0;i < 2;i++)
            for(int j = 0;j < 2;j++){
                t[i][j]+=m[i][k]*n[k][j]%MOD;
                if(t[i][j]>=MOD)t[i][j]-=MOD;
            }
}
void cpy(ll m[2][2],ll r[2][2]){for(int i = 0;i < 2;i++)for(int j = 0;j < 2;j++)r[i][j]=m[i][j];}
ll fib(ll n){
    ll r[2][2] = {{1,0},{0,1}};
    ll m[2][2] = {{0,1},{1,1}};
    ll t[2][2] = {};
    //cout << "n:" << n << '\n';
    while(n){
        if(n&1)muti(r,m,t),cpy(t,r);
        n>>=1;
        muti(m,m,t),cpy(t,m);
    }
    return r[1][0];
}

signed main(){
    ll q,n;
    cin >> q;
    while(q--)cin >> n, n%=333333336, cout << fib(n+2)-1 << '\n';
}
