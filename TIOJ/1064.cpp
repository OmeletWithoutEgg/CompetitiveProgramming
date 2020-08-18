#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>

using namespace std;
typedef int64_t ll;
typedef __int128 magic;
constexpr ll base = 1000000, width = 6, N = 3000000;
constexpr ll modpow(ll e,ll p,ll m) {
    ll r = 1;
    for(; p; p>>=1, e=e*e%m) if(p&1) r=r*e%m;
    return r;
}
ll root[2][25] = {};
inline void root_init(ll m,ll g) {
    for(int i = 0; i < 25; i++)
        root[1][i] = modpow(root[0][i]=modpow(g,m-1>>i,m),m-2,m);
}
inline void rev(ll F[],ll R[],int n) {
    for(int i = 0, j = 0; i < n; i++) {
        R[i] = F[i];
        if(j < i) swap(R[i],R[j]);
        for(int k = n>>1; (j^=k) < k; k>>=1);
    }
}
inline void NTT(ll F[],int n,bool inv,ll m) {
    // F must be reved
    for(int step = 1, L = 1; step < n; step <<= 1, L++) {
        ll w = root[inv][L];
        //ll w = modpow(3,(m-1)/(step*2),m);
        //if(inv) w = modpow(w,m-2,m);
        for(int i = 0; i < n; i+=step<<1) {
            ll now = 1;
            for(int j = 0; j < step; j++) {
                ll a = F[i+j], b = F[i+j+step]*now%m;
                F[i+j] = (a+b<m ? a+b : a+b-m);
                F[i+j+step] = (a-b<0 ? a-b+m : a-b);
                now = now*w%m;
            }
        }
    }
    if(inv) {
        ll invn = modpow(n,m-2,m);
        for(int i = 0; i < n; i++) F[i]=F[i]*invn%m;
    }
}
inline int read(ll F[]) {
    string s;
    cin >> s;
    if(s == "0") cout << 0 << '\n', exit(0);
    reverse(s.begin(),s.end());
    ll now = 0, p = 1, j = 0;
    for(int i = 0; i < s.size(); i++) {
        now += (s[i]-'0')*p, p = p*10;
        if(i+1==s.size() || (i+1)%width == 0) F[j++] = now, now = 0, p = 1;
    }
    return j;
}
inline void print(ll F[],int n) {
    ll carry = 0;
    for(int i = 0; i < n; i++) {
        F[i] += carry;
        carry = F[i]/base;
        F[i] %= base;
    }
    while(carry) F[n++] = carry%base, carry/=base;
    //while(F[n-1] == 0) --n;
    bool first = 1;
    for(int i = n-1; i >= 0; i--) {
        if(first) {
            if(F[i]) cout << F[i], first = 0;
        }else {
            for(ll p = 10; p < base; p *= 10) if(F[i] < p) cout << 0;
            cout << F[i];
        }
    }
    cout << '\n';
}
ll A[N],B[N],AA[N],BB[N];
ll R1[N],R2[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    constexpr ll m1 = 998244353, g1 = 3;
    constexpr ll m2 = 1004535809, g2 = 3;
    constexpr magic c1 = m2*modpow(m2,m1-2,m1); // m2*inv(m2,m1)
    constexpr magic c2 = m1*modpow(m1,m2-2,m2); // m1*inv(m1,m2)
    constexpr ll M  = m1*m2; // m1*m2
    int a = read(A);
    int b = read(B);
    int n = 1<<__lg(a+b)+1;

    root_init(m1,g1);
    rev(A,AA,n);
    rev(B,BB,n);
    NTT(AA,n,0,m1);
    NTT(BB,n,0,m1);
    for(int i = 0; i < n; i++) R1[i] = AA[i]*BB[i]%m1;
    rev(R1,R1,n);
    NTT(R1,n,1,m1);

    root_init(m2,g2);
    rev(A,AA,n);
    rev(B,BB,n);
    NTT(AA,n,0,m2);
    NTT(BB,n,0,m2);
    for(int i = 0; i < n; i++) R2[i] = AA[i]*BB[i]%m2;
    rev(R2,R2,n);
    NTT(R2,n,1,m2);

    for(int i = 0; i < n; i++) R1[i] = (R1[i]*c1 + R2[i]*c2)%M;
    print(R1,n);
    //print(R1);
    //print(R2);
}
/*
12345
123

135372
88762

9487
7122
*/

