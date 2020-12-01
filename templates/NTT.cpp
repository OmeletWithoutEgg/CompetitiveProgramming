#include <bits/stdc++.h>

using namespace std;

int64_t modpow(int64_t e,int64_t p,int64_t m) {
    int64_t r = 1;
    while(p) (p&1)&&(r=r*e%m), e=e*e%m, p>>=1;
    return r;
}
void NTT(int64_t F[],int n,bool inv,int64_t m=998244353,int64_t g=3) {
    for(int i = 0, j = 0; i < n; i++) {
        if(i < j) swap(F[i],F[j]);
        for(int k = n>>1; (j^=k) < k; k>>=1);
    }
    for(int step = 1; step < n; step *= 2) {
        int64_t root = modpow(g,(m-1)/(step*2),m);
        if(inv) root = modpow(root,m-2,m);
        for(int i = 0; i < n; i += step*2) {
            int64_t now = 1;
            for(int j = 0; j < step; j++) {
                int64_t a = F[i+j];
                int64_t b = F[i+j+step]*now%m;
                F[i+j] = (a+b<m ? a+b : a+b-m);
                F[i+j+step] = (a-b<0 ? m+a-b : a-b);
                now = now*root%m;
            }
        }
    }
    if(inv) {
        int64_t in = modpow(n,m-2,m);
        for(int i = 0; i < n; i++) F[i]=F[i]*in%m;
    }
}

int64_t A[1<<20] = {1,2}, B[1<<20] = {1,2,3}; // (1+2x) * (1+2x+3x^2)
signed main() {
    // A*B
    int n = 1<<__lg(2+3)+1; // n = 2^k >= deg(A)+deg(B)
    NTT(A,n,0);
    NTT(B,n,0);
    for(int i = 0; i < n; i++) A[i] = A[i]*B[i]%998244353;
    NTT(A,n,1);
}
