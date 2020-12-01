#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<'\n'

typedef long long ll;
const int MOD = 998244353, G = 3;
const int N = 100025;

using namespace std;
constexpr int modpow(int e, int p) {
    int r = 1;
    for(e%=MOD; p; p>>=1, e=1LL*e*e%MOD) if(p&1) r=1LL*r*e%MOD;
    return r;
}
ll fr[N] = {1};
void FFT(vector<int> &F, bool inv) {
    int n = F.size();
    for(int i = 0, j = 0; i < n; i++) {
        if(i < j) swap(F[i], F[j]);
        for(int k = n>>1; (j^=k) < k; k>>=1);
    }
    for(int s = 1; s < n; s<<=1) {
        ll omega = modpow(G, (MOD-1)/(s*2));
        if(inv) omega = modpow(omega, MOD-2);
        for(int i = 0; i < n; i+=s*2) {
            ll now = 1;
            for(int j = 0; j < s; j++) {
                int a = F[i+j], b = F[i+j+s] * now % MOD;
                F[i+j] = (a+b<MOD ? a+b : a+b-MOD);
                F[i+j+s] = (a-b<0 ? a-b+MOD : a-b);
                now = now * omega % MOD;
            }
        }
    }
    if(inv) {
        ll in = modpow(n, MOD-2);
        for(int i = 0; i < n; i++) F[i] = F[i] * in % MOD;
    }
}

// S(n) * (1+x^n) = S(n*2)
// (S(n) + 1) * x = S(n+1)
ll pwsum(ll x, ll n) { // returns x + x^2 + ... + x^n
    ll s = 0, p = 1; // S(0) = 0, x^0 = 1
    for(int i = __lg(n); i >= 0; i--) {
        s = s * (1+p) % MOD;
        p = p * p % MOD;
        if(n >> i & 1) {
            s = (s+1) * x % MOD;
            p = p * x % MOD;
        }
    }
    return s;
}
ll solve(int n, int k) {
    if(n < 1 || k < 0) return 0;
    // \sum_c \sum_{i=1}^{min(n,c+k)} F^c [i]
    // if c+k > n -> just calculate the first n term
    // if c+k <= n -> calculate the first c+k term -> shift by n-(c+k)
    /* conclusion:
     * let F = \sum_{i=1}^n (1/i) x^i
     * \sum_{i=1}^n {
     *      \sum_{c=1}^{n-k} shift{n-k-c} F^c +
     *      \sum_{c=n-k+1}^n F^c
     * } [i]
     */
    if(n-1 <= k) {
        ll res = 0;
        for(int i = 1; i <= n; i++) res = (res + fr[i]) % MOD;
        debug(res);
        return res;
    }
    int h = n-k, len = 1<<__lg(n)+1;
    ll res = 0;
    {
        vector<int> F(len);
        for(int i = 0; i <= n; i++) F[i] = modpow(i+1, MOD-2);
        FFT(F, 0);
        for(int i = 0; i < len; i++) F[i] = pwsum(F[i], h);
        FFT(F, 1);
        for(int i = len-1; i >= 0; i--) F[i] = i < h ? 0 : F[i-h];
        for(int i = 1; i <= n; i++) res = (res + F[i] * fr[i]) % MOD;
    }
    {
        vector<int> F(len);
        for(int i = 1; i <= n; i++) F[i] = modpow(i, MOD-2);
        FFT(F, 0);
        for(int i = 0; i < len; i++) F[i] = (pwsum(F[i], n) - pwsum(F[i], h) + MOD) % MOD;
        FFT(F, 1);
        for(int i = 1; i <= n; i++) res = (res + F[i] * fr[i]) % MOD;
    }
    return res;
}
ll naive(int n, int L, int R) {
    int v[10] = {}, u[10] = {}, res = 0;
    for(int i = 0; i < n; i++) v[i] = i;
    do {
        int ans = 0;
        for(int i = 0; i < n; i++) cout << i+1 << " \n"[i+1==n];
        for(int i = 0; i < n; i++) cout << v[i]+1 << " \n"[i+1==n];
        for(int i = 0; i < n; i++) u[i] = v[i];
        for(int i = 0; i < n; i++) while(u[i] != i) {
            ++ans;
            int x = u[i];
            swap(u[x], u[i]);
        }
        cout << ans << '\n';
        if(L <= ans && ans <= R) ++res;
    } while(next_permutation(v,v+n));
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    for(int i = 1; i < N; i++) fr[i] = fr[i-1] * i % MOD;
    int A, B, L, R;
    cin >> A >> B >> L >> R;
    cout << (naive(B, L, R) - naive(A-1, L, R) + MOD) % MOD << '\n';
    cout << (solve(B, R) - solve(B, L-1) - solve(A-1, R) + solve(A-1, L-1) + MOD*2) % MOD << '\n';
}
