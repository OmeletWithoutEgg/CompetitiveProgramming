#include <cstdio>
#include <algorithm>

using namespace std;
constexpr int N = 1 << 19;

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

struct Segtree {
    int lz[N*2], ans[N*2];
    void upd(int p, int d, int len) {
        lz[p] += d;
        ans[p] = lz[p] ? len : (p < N ? ans[p<<1] + ans[p<<1|1] : 0);
    }
    void pull(int p) {
        for(int h = 1; p > 1; p>>=1, ++h)
            ans[p>>1] = (lz[p>>1] ? 1 << h : ans[p] + ans[p^1]);
    }
    void add(int l, int r, int d) {
        int L = l, R = r, len = 1;
        for(l+=N, r+=N; l<r; l>>=1, r>>=1, len<<=1) {
            if(l&1) upd(l++, d, len);
            if(r&1) upd(--r, d, len);
        }
        pull(L+N), pull(R-1+N);
    }
    int query() {
        return ans[1];
    }
} sgt;
struct Event {
    int x, l, r, w;
    bool operator<(const Event &rhs) const {
        return x < rhs.x;
    }
} E[N*2];
signed main(){
    int n = nextint();
    for(int i = 0; i < n; i++) {
        int l, r, d, u;
        l = nextint();
        r = nextint();
        d = nextint();
        u = nextint();
        E[i << 1 | 0] = {l, d, u, 1};
        E[i << 1 | 1] = {r, d, u, -1};
    }
    sort(E, E+n*2);
    int lastx = 0;
    long long ans = 0;
    for(int i = 0; i < n*2; i++) {
        auto [x, l, r, w] = E[i];
        ans += 1LL * sgt.query() * (x - lastx);
        sgt.add(l, r, w);
        lastx = x;
    }
    printf("%lld\n", ans);
}
