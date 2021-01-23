#pragma GCC optimize("Ofast")
#pragma GCC target("sse3","sse2","sse")
#pragma GCC target("avx","sse4","sse4.1","sse4.2","ssse3")
#pragma GCC target("f16c")
#pragma GCC optimize("inline","fast-math","unroll-loops","no-stack-protector")
#include <cstdio>

inline char readchar() {
    constexpr int B = 1<<16;
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

typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
	ull b, m;
	FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
	ull reduce(ull a) {
		ull q = (ull)((L(m) * a) >> 64), r = a - q * b;
		return r >= b ? r - b : r;
	}
};

signed main() {
    int t = nextint();
    while(t--) {
        int n = nextint();
        int res = nextint(), mod = nextint();
        FastMod fm(mod);
        for(int i = 2; i < n; i++) res = fm.reduce(1LL * res * nextint());
        puts(res ? "zzz..." : "Asssss!!");
    }
}
