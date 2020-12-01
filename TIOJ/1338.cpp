#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include "lib1338.h"

typedef long long ll;
constexpr ll N = 1000025;

inline ll __gcd(register ll a,register ll b){
    if(!a) return b;
    if(!b) return a;
    register int s=__builtin_ctz(a|b);
    for(int i = 0; i < 80; i++) {
        a>>=__builtin_ctz(a), b>>=__builtin_ctz(b);
        if(a == b) return a << s;
        if(a < b)
            b -= a;
        else
            a -= b;
    }
}
inline ll min(ll a,ll b){return a<b?a:b;}

ll gcd[20][N] = {};
ll mn[20][N] = {};
void init(int n,ll C[]){
    for(int i = 0; i < n; i++) gcd[0][i] = mn[0][i] = C[i];
    for(int b = 1, d = 1; b < 20; b++, d <<= 1) {
        for(int i = 0; i+d < n; i++) {
            gcd[b][i] = __gcd(gcd[b-1][i], gcd[b-1][i+d]);
            mn[b][i] = min(mn[b-1][i], mn[b-1][i+d]);
        }
    }
}
int query(int l,int r){
    int b = 31 - __builtin_ctz(r-l);
    r -= 1<<b;
    return __gcd(gcd[b][l],gcd[b][r]) == min(mn[b][l],mn[b][r]);
}
