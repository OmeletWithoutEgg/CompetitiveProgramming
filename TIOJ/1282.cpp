#pragma Ofast
#pragma loop-opt(on)
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
// #include <bits/stdc++.h>
#include <cstdint>
#include <unistd.h>
#include <algorithm>

using ll = int_fast64_t;

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if (p == q) {
        p = buf;
        q = p + read(0, buf, B);
    }
    // if (p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline ll nextint() {
    ll x = 0;
    char c = readchar();
    while (c < '0') c = readchar();
    while (c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

struct FastOut {
    constexpr static int B = 1 << 20;
    static char buf[B], *q;
    inline void writeint(ll x, char sep = '\n') {
        static char stk[20];
        char *p = stk;
        if (!x) *p++ = '0';
        while (x) {
            // ll y = x / 10;
            *p++ = (x % 10) ^ '0';
            x /= 10;
            // x = y;
        }
        while (p != stk) *q++ = *--p;
        *q++ = sep;
        // if (q - buf + 20 >= B) fwrite(buf, 1, q - buf, stdout), q = buf;
    }
    ~FastOut() {
        write(1, buf, q - buf);
        // fwrite(buf, 1, q - buf, stdout);
    }
} ouf;
char FastOut::buf[B], *FastOut::q = FastOut::buf;

inline ll bgcd(ll a, ll b) {
    // return llabs(std::gcd(a, b));
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    if (!a) return b;
    int s = __builtin_ctzll(a|b);
    a >>= __builtin_ctzll(a);
    while (b) {
        b >>= __builtin_ctzll(b);
        if (a > b) {
            std::swap(a, b);
        }
        b -= a;
    }
    return a << s;
}

const int maxn = 100025;
int n,q;
ll v[maxn], d[maxn<<1];
void inc(int l, int r, ll k) {
    for (int i=l+1; i<=n; i+=i&-i) v[i] += k;
    for (int i=r+1; i<=n; i+=i&-i) v[i] -= k;
    for (d[l+=n]+=k; l>1; l>>=1) d[l>>1] = bgcd(d[l],d[l^1]);
    for (d[r+=n]-=k; r>1; r>>=1) d[r>>1] = bgcd(d[r],d[r^1]);
}
ll qry(int l,int r) {
    ll res = 0;
    for (int i=r; i; i-=i&-i) res += v[i];
    for (++l, l+=n, r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) res=bgcd(res, d[l++]);
        if (r&1) res=bgcd(res, d[--r]);
    }
    return res;
}
signed main() {
    n = nextint(), q = nextint();
    /*
    while (q--) {
        ll a = nextint();
        ll b = nextint();
        printf("%lld\n", bgcd(a, b));
    }
    return 0;
    */
    for (int i = 1; i <= n; i++) v[i] = nextint();
    for (int i = 0; i < n; i++) d[i+n] = v[i+1]-v[i];
    for (int i = n-1; i > 0; i--) d[i] = bgcd(d[i<<1], d[i<<1|1]);
    for (int i = n; i >= 1; i--) v[i] -= v[i-(i&-i)];
    while (q--) {
        ll t, l, r, k;
        t = nextint();
        if (t == 1) {
            l = nextint(), r = nextint(), k = nextint(), --l;
            inc(l,r,k);
        } else if (t == 2) {
            l = nextint(), r = nextint(), --l;
            ouf.writeint(qry(l, r));
        }
    }
}
