#include <bits/stdc++.h>

using namespace std;
typedef int64_t ll;
constexpr ll base = 1000000, width = 6;

ll modpow(ll e,ll p,ll m) {
    ll r = 1;
    while(p) (p&1)&&(r=r*e%m), e=e*e%m, p>>=1;
    return r;
}
inline ll M(ll x,ll MOD) {return x<MOD ? x : x-MOD;}
void NTT(const ll MOD,const ll G,vector<ll> &F, bool inv) {
    int n = F.size(), L = __lg(n);
    vector<int> rev(n);
    for(int i = 0; i < n; i++) {
        rev[i] = (rev[i>>1]>>1) | ((i&1) << L-1);
        if(i < rev[i]) swap(F[i],F[rev[i]]);
    }
    for(int step = 1; step < n; step <<= 1) {
        ll root = modpow(G,(MOD-1)/(step<<1),MOD);
        if(inv) root = modpow(root,MOD-2,MOD);
        for(int i = 0; i < n; i += step*2) {
            ll now = 1;
            for(int j = 0; j < step; j++) {
                ll a = F[i+j];
                ll b = F[i+j+step]*now%MOD;
                F[i+j] = M(a+b,MOD);
                F[i+j+step] = M(a-b+MOD,MOD);
                now = now*root%MOD;
            }
        }
    }
    if(inv) {
        ll invn = modpow(n,MOD-2,MOD);
        for(int i = 0; i < n; i++) F[i] = F[i]*invn%MOD;
    }
}
inline void read(vector<ll> &v) {
    string s;
    cin >> s;
    reverse(s.begin(), s.end());
    ll now = 0, p = 1;
    for(int i = 0; i < s.size(); i++) {
        now = now+(s[i]-'0')*p;
        p *= 10;
        if(i+1 == s.size() || (i+1)%width == 0)
            v.push_back(now), now = 0, p = 1;
    }
}
inline void mul(const ll MOD,const ll G,vector<ll> A,vector<ll> B,vector<ll> &R) {
    if(A.empty() || B.empty()) return;
    int a = A.size(), b = B.size();
    int n = 1<<__lg(a+b)+1;
    R.resize(n);
    A.resize(n);
    B.resize(n);
    NTT(MOD,G,A,0);
    NTT(MOD,G,B,0);
    for(int i = 0; i < n; i++) R[i] = A[i]*B[i]%MOD;
    NTT(MOD,G,R,1);
}
void print(vector<ll> &A) {
    if(A.empty()) return cout << 0 << '\n', void();
    ll carry = 0;
    for(int i = 0; i < A.size(); i++) {
        A[i] += carry;
        carry = A[i]/base;
        A[i] %= base;
    }
    while(carry) A.push_back(carry%base), carry/=base;
    bool first = true;
    for(int i = A.size()-1; i >= 0; i--) {
        if(first) {
            if(A[i]) cout << A[i], first = false;
        }else {
            ll p = 1;
            for(int k = 0; k < width-1; k++) {
                p *= 10;
                if(A[i] < p) cout << 0;
            }
            cout << A[i];
        }
    }
    cout << '\n';
}
inline long long modmul(long long a,long long b,long long m){ // ???????
	//a%=m,b%=m;
	long long y=(long long)((double)a*b/m+0.5);/* fast for m < 2^58 */
	long long r=(a*b-y*m)%m;
	return r<0?r+m:r;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    ll m1 = 998244353, g1 = 3;
    ll m2 = 1004535809, g2 = 3;
    ll c1 = m2*modpow(m2,m1-2,m1); // m2*inv(m2,m1)
    ll c2 = m1*modpow(m1,m2-2,m2); // m1*inv(m1,m2)
    ll M  = m1*m2; // m1*m2
    vector<ll> A,B,R1,R2;
    read(A);
    read(B);
    mul(m1,g1,A,B,R1);
    mul(m2,g2,A,B,R2);
    for(int i = 0; i < R1.size(); i++) {
        R1[i] = (modmul(R1[i],c1,M) + modmul(R2[i],c2,M))%M;
    }
    print(R1);
    //print(R1);
    //print(R2);
}
