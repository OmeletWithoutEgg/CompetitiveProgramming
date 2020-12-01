#include <bits/stdc++.h>

using namespace std;
const int64_t N = 200001, MOD = 998244353;
int64_t modpow(int64_t e, int64_t p) {
    int64_t r = 1;
    assert(e);
    while(p) (p&1) && (r=r*e%MOD), e=e*e%MOD, p>>=1;
    return r;
}

typedef array<array<int64_t,2>,2> matrix;
matrix operator*(const matrix &a, const matrix &b) {
    matrix c{};
    for(int i = 0; i < 2; i++) for(int k = 0; k < 2; k++) {
        int64_t r = a[i][k];
        for(int j = 0; j < 2; j++) c[i][j] += r*b[k][j];
    }
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) c[i][j] %= MOD;
    return c;
}
void print(const matrix &v) {
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) cout << v[i][j] << " \n"[j];
}
matrix inv(const matrix &v) {
    matrix res{v[1][1],MOD-v[0][1],MOD-v[1][0],v[0][0]};
    int64_t d = (v[0][0]*v[1][1]%MOD - v[1][0]*v[0][1]%MOD+MOD)%MOD;
    d = modpow(d, MOD-2);
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) res[i][j] = res[i][j]*d%MOD;
    matrix check = res*v;
    for(int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) assert(check[i][j] == (i==j));
    return res;
}
int n,q;
matrix v[N];
int main() {
    v[0] = {1,0,0,1};
    cin >> n >> q;
    for(int i = 1,a; i <= n; i++) {
        cin >> a;
        if(a > 0) v[i] = matrix{1,a,0,1};
        if(a < 0) v[i] = matrix{1,0,-a,1};
    }
    for(int i = 1; i <= n; i++) v[i] = v[i] * v[i-1];
    while(q--) {
        int L,R;
        int64_t x,y;
        cin >> L >> R >> x >> y;
        matrix A = v[R] * inv(v[L-1]);
        int64_t nx = (x*A[0][0]+y*A[0][1])%MOD;
        int64_t ny = (x*A[1][0]+y*A[1][1])%MOD;
        cout << nx << ' ' << ny << '\n';
    }
}
