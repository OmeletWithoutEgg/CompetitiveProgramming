#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#define debug(x) (cerr<<#x<<" = "<<x<<'\n')
#define pb emplace_back

using namespace std;
const int N = 3000025;

vector<int> prs,fac[N];
int ans[N],sp[N],mp[N];
int64_t cnt;
inline int lcm(int a,int b) {
    return a/__gcd(a,b)*b;
}
bool ok(int id,int m) {
    int64_t E[2][2] = {{1,1},{1,0}}, R[2][2] = {{1,0},{0,1}}, T[2][2];
    while(id) {
        if(id&1) {
            for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) {
                T[i][j] = 0;
                for(int k = 0; k < 2; k++) T[i][j] += E[i][k]*R[k][j];
            }
            for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) R[i][j]=T[i][j]%m;
        }
        for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) {
            T[i][j] = 0;
            for(int k = 0; k < 2; k++) T[i][j] += E[i][k]*E[k][j];
        }
        for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) E[i][j]=T[i][j]%m;
        id>>=1;
    }
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) if(R[i][j] != (i==j)) return false;
    return true;
}
void brute(int m) {
    if(m == 2) return ans[m] = 3, void();
    if(m == 5) return ans[m] = 20, void();
    if(m%10==1 || m%10==9) {
        sort(fac[m-1].begin(),fac[m-1].end());
        for(int f:fac[m-1]) if(f!=1 && ok(f,m)) {ans[m]=f; break;}
    }else {
        int u = m*2+2;
        auto &v = fac[u>>__builtin_ctz(u)];
        sort(v.rbegin(),v.rend());
        for(int t:v) if(t!=u && ok(u/t,m)) {ans[m]=u/t; break;}
    }
}
void init(int n) {
    sp[1] = 1, fac[1].pb(1);
    for(int i = 2; i <= n; i++) {
        if(!mp[i]) {
            if(i*i <= n) prs.pb(i);
            sp[i] = 1, mp[i] = i, fac[i].pb(1), fac[i].pb(i);
        }
        for(int p:prs) {
            int64_t j = int64_t(i)*p;
            if(j > n) break;
            mp[j] = p;
            fac[j] = fac[i];
            if(i%p) {
                sp[j] = i;
                for(int f:fac[i]) fac[j].pb(f*p);
            }else {
                sp[j] = sp[i];
                for(int f:fac[sp[i]]) fac[j].pb(j/f);
                break;
            }
        }
    }
    //prs.clear();
}
void calc(int n) {
    ans[1] = 1;
    for(int i = 2; i <= n; i++) {
        ans[i] = 1;
        //cout << i << ',' << sp[i] << '\n';
        if(mp[i]==i) brute(i);
        else if(sp[i]==1) ans[i] = ans[i/mp[i]]*mp[i];
        else ans[i] = lcm(ans[sp[i]],ans[i/sp[i]]);
    }
}
signed main() {
    int n = 3000000;
    scanf("%d",&n);
    init(n);
    calc(n);
    for(int i = 1; i <= n; i++) printf("%d\n", ans[i]);
}
