#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <vector>
#include <utility>

const int N = 1000001, K = 21, MOD = 1000000007;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
using std::vector, std::pair;
struct Query { int l, r, id; };
vector<Query> Q[N];
struct FenwickTree {
    long long b[N], n;
    void init(int _n) {
        n = _n;
        for(int i = 1; i <= n; i++) b[i] = 1;
    }
    void modify(int p, int d) {
        for(; p <= n; p += p&-p) b[p] = b[p] * d % MOD;
    }
    long long query(int p) {
        long long r = 1;
        for(; p; p -= p&-p) r = r * b[p] % MOD;
        return r;
    }
} prod;
long long modinv(long long p){
    long long r = 1, e = MOD-2;
    while(e) {
        if(e&1) r = r*p%MOD;
        p = p*p%MOD, e>>=1;
    }
    return r;
}
int ppow[N][21], ippow[N][21];
vector<pair<int,int>> dq[N];
void ins(int p, int e, int l) {
    // debug("IN");
    auto &v = dq[p];
    while(v.size() && v.back().first <= e) {
        if(v.size() >= 2)
            prod.modify(v[v.size()-2].second, ppow[p][v.back().first]);
        prod.modify(v.back().second, ippow[p][v.back().first]);
        v.pop_back();
    }
    if(v.size()) prod.modify(v.back().second, ippow[p][e]);
    prod.modify(l, ppow[p][e]);
    v.push_back({e, l});
    // debug("OU");
}
struct Sieve {
    int np[N];
    vector<pair<int,int>> operator()(int x) {
        vector<pair<int,int>> res;
        while(x > 1) {
            int p = np[x], e = 0;
            while(np[x] == p) x /= p, e++;
            res.push_back({p, e});
        }
        return res;
    }
    void init() {
        vector<int> prs;
        for(int i = 2; i < N; i++) {
            if(!np[i]) prs.push_back(i), np[i] = i;
            for(int p: prs) {
                if(i*p >= N) break;
                np[i*p] = p;
                if(i%p == 0) break;
            }
        }
        for(int p: prs) {
            long long cur = 1, icur = 1, ip = modinv(p);
            for(int i = 0; i < 21; i++) {
                ppow[p][i] = cur;
                ippow[p][i] = icur;
                cur = cur * p % MOD, icur = icur * ip % MOD;
            }
        }
    }
} primeFactor;
int n, q, v[N], ans[N];
signed main() {
    primeFactor.init();
    n = nextint(), q = nextint();
    for(int i = 1; i <= n; i++) v[i] = nextint();
    for(int i = 0; i < q; i++) {
        int l = nextint(), r = nextint();
        Q[l].push_back({l, r, i});
    }
    prod.init(n);
    for(int i = n; i >= 1; i--) {
        for(auto [p, e]: primeFactor(v[i]))
            ins(p, e, i);
        for(auto [l, r, id]: Q[i])
            ans[id] = prod.query(r) * modinv(prod.query(l-1)) % MOD;
    }
    for(int i = 0; i < q; i++) printf("%d\n", ans[i]);
}
