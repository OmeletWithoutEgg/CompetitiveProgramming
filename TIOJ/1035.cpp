#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/stdc++.h>
using namespace std;
const int64_t m = 998244353, g = 3, N = 1<<17;
int rev[N],n,in;
int64_t mdp(int64_t e,int64_t p) {
    int64_t r = 1;
    while(p) (p&1)&&(r=r*e%m), e=e*e%m, p>>=1;
    return r;
}
void trans(int64_t F[],int n,bool inv) {
    int L = __lg(n);
    for(int i = 0; i < n; i++) {
        rev[i] = (rev[i>>1]>>1) | ((i&1)<<L-1);
        if(i < rev[i]) swap(F[i],F[rev[i]]);
    }
    for(int step = 1; step < n; step *= 2) {
        int64_t root = mdp(g,(m-1)/(step*2));
        if(inv) root = mdp(root,m-2);
        for(int i = 0; i < n; i += step*2) {
            int64_t now = 1;
            for(int j = 0; j < step; j++) {
                int64_t a = F[i+j];
                int64_t b = F[i+j+step]*now%m;
                F[i+j] = (a+b < m ? a+b : a+b-m);
                F[i+j+step] = (a-b < 0 ? a-b+m : a-b);
                now = now*root%m;
            }
        }
    }
    if(inv) {
        for(int i = 0; i < n; i++) F[i] = F[i]*in%m;
    }
}
void mul(int64_t A[],int64_t B[],int64_t C[],int n) {
    trans(A,n,0);
    trans(B,n,0);
    for(int i = 0; i < n; i++) C[i] = A[i]*B[i]%m;
    trans(C,n,1);
}
int64_t A[N],B[N],C[N],ans[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s,t;
    cin >> s >> t;
    n = 1<<__lg(s.size()+t.size())+1;
    in = mdp(n,m-2);
    for(int c = 0; c < 26; c++) {
        for(int i = 0; i < n; i++) {
            A[i] = (i < s.size() && s[i]-'a'==c);
            B[i] = (i < t.size() && t[t.size()-1-i]-'a'==c);
        }
        mul(A,B,C,n);
        for(int i = 0; i < n; i++) ans[i] += C[i];
    }
    cout << *max_element(ans,ans+n) << '\n';
}

