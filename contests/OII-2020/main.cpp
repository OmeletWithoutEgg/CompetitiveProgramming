#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (", ..., (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) (void(0))
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int N = 500025, inf = 1e9, K = 120;

void aggiungi();
void copia();
void incolla();

bool chkmn(int &x, int v) {
    if(x > v) return x = v, true;
    return false;
}
int dp[N], fr[N];
map<ll,int> mdp, mfr;
int DFS(ll n, int dep = 0) {
    /* debug(n, dep); */
    if(n < 0 || dep > K) return inf;
    if(n < N) return dp[n];
    if(mdp.count(n)) return mdp[n];
    int &ans = mdp[n];
    ans = inf;
    for(int k = 2; k <= K; k++) if(n % k == 0) if(chkmn(ans, DFS(n / k, dep + k + 1) + k + 1)) mfr[n] = k;
    if(chkmn(ans, DFS(n-1, dep+1) + 1)) mfr[n] = -1;
    return ans;
}
void auguri(ll n) {
    static bool dped = false;
    if(!dped) {
        for(int i = 1; i < N; i++) dp[i] = inf;
        for(int i = 0; i < N; i++) {
            if(i+1 < N && chkmn(dp[i+1], dp[i] + 1)) fr[i+1] = -1;
            if(i) for(int j = 2; i * j < N; j++) if(chkmn(dp[i*j], dp[i] + j+1)) fr[i*j] = j;
        }
        dped = true;
    }
    DFS(n);
    vector<int> ans;
    while(n) {
        int f = n < N ? fr[n] : mfr[n];
        if(f == -1) ans.pb(1), --n;
        else {
            for(int j = 1; j < f; j++) ans.pb(3);
            ans.pb(2);
            n /= f;
        }
    }
    reverse(all(ans));
    for(int x: ans) {
        if(x == 1) aggiungi();
        else if(x == 2) copia();
        else if(x == 3) incolla();
    }
}
#ifdef local
signed main() {
    /* ios_base::sync_with_stdio(0), cin.tie(0); */
    ll n;
    cin >> n;
    cerr << n << ' ' << __lg(n) << ' ';
    auguri(n);
    cerr << '\n';
    debug(mdp.size());
}
void aggiungi() {
    cerr << "+";
}
void copia() {
    cerr << "y";
}
void incolla() {
    cerr << "p";
}
#endif // local
