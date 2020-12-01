#include <cstdio>
#include <vector>
#include <utility>

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

const int N = 250001, M = 1000001, K = 16;
int mx[N], n, q;
int query(int l, int r) {
    return 0;
}
std::vector<std::pair<int,int>> Q[N];
inline int max(int a, int b){return a>b ? a : b;}
int main() {
    scanf("%d%d", &n, &q);
    for(int i = 0; i < q; i++) {
        int l, r;
        scanf("%d%d", &l, &r);
        Q[r].emplace_back(l, i);
    }
    for(int i = 0; i < n; i++) {
        scanf("%d", &x);
    }
}
/*
4500000 - 3000000 = 1500000;
for(l+=n,r+=n; l<r; l>>=1,r>>=1) {
    if(l&1) res[i] = max(res[i], mx[l++]);
    if(r&1) res[i] = max(res[i], mx[--r]);
}
*/
