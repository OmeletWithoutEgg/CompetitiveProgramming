#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>
#include <utility>
#include <vector>
#include <functional>

using namespace std;
const int inf = 1e9;
typedef int node[200][200];

inline int min(int a, int b){return a<b ? a : b;}
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

int R, C, Q;
int H[5000][200], V[5000][200];
void brute(int l, int r, node dp) { // (r-l) * C^2
    for(int i = 0; i < C; i++) for(int j = 0; j < C; j++) dp[i][j] = (i==j ? 0 : inf);
    int nd[200], suf[200] = {};
    for(int s = 0; s < C; s++) {
        auto &dis = dp[s];
        for(int i = l; i < r && i < R; i++) {
            for(int x = 0; x < C; x++) nd[x] = inf;
            for(int x = C-2; x >= 0; x--) suf[x] = suf[x+1] + H[i][x];
            {
                int mn = inf;
                for(int x = 0; x < C; x++) {
                    mn = min(mn, dis[x] + suf[x]);
                    nd[x] = min(nd[x], mn - suf[x] + V[i][x]);
                }
            }
            {
                int mn = inf;
                for(int x = C-1; x >= 0; x--) {
                    mn = min(mn, dis[x] - suf[x]);
                    nd[x] = min(nd[x], mn + suf[x] + V[i][x]);
                }
            }
            for(int x = 0; x < C; x++) dis[x] = nd[x];
        }
    }
}
void mul(node A, node B, node res) {
    for(int i = 0; i < C; i++) for(int j = 0; j < C; j++) res[i][j] = inf;
    node fr = {};
    for(int i = 0; i < C; i++) for(int k = 0; k < C; k++) {
        if(res[i][i] > A[i][k]+B[k][i])
            res[i][i] = A[i][k]+B[k][i], fr[i][i] = k;
    }
    for(int i = C-1; i >= 0; i--) for(int j = 0; j < C; j++) {
        // fr[i][j-1] <= fr[i][j] <= fr[i+1][j]
        int l = j ? fr[i][j-1] : 0;
        int r = i+1<C ? fr[i+1][j] : C-1;
        for(int k = l; k <= r; k++) {
            if(res[i][j] > A[i][k]+B[k][j])
                res[i][j] = A[i][k]+B[k][j], fr[i][j] = k;
        }
    }
}
node seg[1000];
int s, K;
void update(int p) {
    brute(p*K, p*K+K, seg[p+s]);
    p += s;
    while(p > 1) {
        p >>= 1;
        mul(seg[p<<1], seg[p<<1|1], seg[p]);
    }
}
signed main() {
    R = nextint(), C = nextint();
    for(int i = 0; i < R; i++) for(int j = 0; j < C-1; j++) H[i][j] = nextint();
    for(int i = 0; i < R-1; i++) for(int j = 0; j < C; j++) V[i][j] = nextint();
    std::vector<std::tuple<int,int,int,int>> Qs(Q = nextint());
    int upd = 1, qry = 1;
    for(auto &[c, p, q, x]: Qs) {
        c = nextint();
        p = nextint();
        q = nextint();
        if(c == 1 || c == 2) x = nextint(), ++upd;
        else ++qry;
    }
    K = R >= 2000 ? 16 : 8;
    //assert(upd <= 500);
    //K = sqrt(R*C / upd) + 1;
    //cout << K << '\n';
    s = 1<<__lg(R/K+1)+1;
    for(int i = 0; i < s; i++) brute(i*K, i*K+K, seg[i+s]); // C^2 * R
    for(int i = s-1; i > 0; i--) mul(seg[i<<1], seg[i<<1|1], seg[i]); // C^3 * R / K
    // total = upd * (C^2 K + C^3 log(R/K)) + C^3 * R / K
    for(auto [c, p, q, x]: Qs) {
        if(c == 1) H[p][q] = x, update(p/K);
        if(c == 2) V[p][q] = x, update(p/K);
        if(c == 3) {
            auto &res = seg[1];
            printf("%d\n", res[p][q]);
        }
    }
}
