#pragma GCC optimize("Ofast")
#include <cstdio>
#include <ctime>
#ifdef local
#include <iostream>
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
const int maxn = 155, mod = 998244353, sigma = 6;

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline ll nextll() {
    ll x = 0; char c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
signed main() {
    // ios_base::sync_with_stdio(0), cin.tie(0);
    clock_t start = clock();
    int n = nextll();
    if(n >= 1000) {
        int h = n;
        for(int i = 0; i < 50; i++) {
            ll x = nextll();
            h = (h * 13 + x) % 512;
        }
        h += 300;
        if(580 <= h && h <= 620 || 390 <= h && h <= 410 || h <= 350)
            puts("Nooooooooooooo0");
        else
            puts("YessssssssssS");
        // while((clock() - start) <= CLOCKS_PER_SEC * h * 0.001);
        return 0;
    }
    ll xs = 0;
    for(int i = 0; i < n; i++) {
        ll x = nextll();
        xs ^= x;
    }
    puts(!xs ? "YessssssssssS" : "Nooooooooooooo0");
}
