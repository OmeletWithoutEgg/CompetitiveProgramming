#include <cstdio>
#include <vector>
#include <utility>

using namespace std;
const int N = 1000001;

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

vector<pair<int,int>> qs[N];
unsigned h[N],ans[N],mn[N],n;
void ins(int p, int d) {
    for(; p<=n; p+=p&-p) if(mn[p] > d) mn[p] = d;
}
int qry(int p) {
    int r = 1e9;
    for(; p; p -= p&-p) if(r > mn[p]) r = mn[p];
    return r;
}
signed main() {
    n = nextint();
    for(int i = 1; i <= n; i++) h[i] = nextint();
    for(int i = 1; i <= n; i++) mn[i] = -1;
    for(int i = 0; i < n; i++) {
        int l = nextint();
        int r = nextint();
        qs[l].emplace_back(r, i);
    }
    for(int i = n; i >= 1; i--) {
        ins(i, h[i]);
        for(auto [r, id]: qs[i]) ans[id] = qry(r);
    }
    for(int i = 0; i < n; i++) printf("%d\n", ans[i]+1);
}
