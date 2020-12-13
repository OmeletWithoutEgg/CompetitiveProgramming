#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>
#include <cstdint>
#include <utility>
#include <algorithm>
#define fread fread_unlocked
#define fwrite fwrite_unlocked

using namespace std;
const uint32_t N = 100025, MOD = 1000000007, K = 880301, LG = 19;

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

struct FastOut {
    char *buf;
    int q;
    const int B;
    inline void writesp(int x) {
        static char stk[20];
        char p = 0;
        if(!x) stk[p++] = '0';
        while(x) stk[p++] = x%10^'0', x/=10;
        while(p) buf[q++] = stk[--p];
        buf[q++] = ' ';
        if(q + 20 >= B) fwrite(buf, 1, q, stdout), q = 0;
    }
    FastOut(int B = 1<<20) : B(B), q(0), buf(new char[B]){}
    ~FastOut() {
        fwrite(buf, 1, q, stdout);
        delete [] buf;
    }
};

struct PersistentSegtree {
    struct node {
        uint32_t sum;
        int32_t val;
        int32_t l, r;
    } T[N + N * LG * 2];
    uint32_t tot;
    void pull(uint32_t x) {
        T[x].sum = T[T[x].l].sum ^ T[T[x].r].sum;
    }
    uint32_t build(uint32_t s[], uint32_t v[], uint32_t l, uint32_t r) {
        uint32_t now = tot++;
        if(l+1 == r) {
            T[now].sum = s[l];
            T[now].val = v[l];
        } else {
            uint32_t m = l+(r-l)/2;
            T[now].l = build(s, v, l, m);
            T[now].r = build(s, v, m, r);
            pull(now);
        }
        return now;
    }
    uint32_t edit(uint32_t p, uint32_t s, uint32_t v, uint32_t old, uint32_t l, uint32_t r) {
        uint32_t now = tot++;
        if(l+1 == r) {
            T[now].sum = s, T[now].val = v;
            return now;
        }
        uint32_t m = l+(r-l)/2;
        if(p < m) {
            T[now].l = edit(p, s, v, T[old].l, l, m);
            T[now].r = T[old].r;
        } else {
            T[now].l = T[old].l;
            T[now].r = edit(p, s, v, T[old].r, m, r);
        }
        pull(now);
        return now;
    }
    bool compare(uint32_t a, uint32_t b, uint32_t l, uint32_t r) {
        if(T[a].sum == T[b].sum) return a < b;
        while(l+1 != r) {
            uint32_t m = l+(r-l)/2;
            if(T[T[a].l].sum == T[T[b].l].sum)
                a = T[a].r, b = T[b].r, l = m;
            else
                a = T[a].l, b = T[b].l, r = m;
        }
        return T[a].val < T[b].val;
    }
} pst;
uint32_t pw[N], s[N], p[N];
pair<uint32_t, uint32_t> ans[N];
signed main() {
    uint32_t n, m;
    n = nextint(), m = nextint();
    for(uint32_t i = 0; i < n; i++) p[i] = nextint() - 1;
    pw[0] = K;
    for(uint32_t i = 1; i < n; i++) pw[i] = pw[i-1] * K;
    for(uint32_t i = 0; i < n; i++) s[i] = p[i] * pw[i];
    uint32_t cur = pst.build(s, p, 0, n);
    ans[0] = { cur, 0 };
    for(uint32_t i = 1; i < m; i++) {
        uint32_t x, y;
        x = nextint(), y = nextint();
        --x, --y;
        swap(p[x], p[y]);
        cur = pst.edit(x, p[x] * pw[x], p[x], cur, 0, n);
        cur = pst.edit(y, p[y] * pw[y], p[y], cur, 0, n);
        ans[i] = { cur, i };
    }
    sort(ans, ans+m, [n](const auto &a, const auto &b) {
        return pst.compare(a.first, b.first, 0, n);
    });
    FastOut ouf;
    for(uint32_t i = 0; i < m; i++)
        ouf.writesp(ans[i].second);
}
