#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
inline char readchar() {
    constexpr int B = 1<<15;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    bool neg = false;
    int x = 0, c = readchar();
    while(('0'>c || c>'9') && c!='-' && ~c) c = readchar();
    if(c == '-') neg = true, c = readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    if(neg) x = -x;
    return x;
}


signed main() {
    int n;
    while(n = nextint()) {
        vector<long long> len;
        while(n--) {
            int x = nextint();
            if(x > 0) len.emplace_back(x);
        }
        sort(len.begin(), len.end());
        int ans = 0;
        for(long long x:len) {
            int i = 0;
            for(long long y:len) {
                if(x == y) break;
                long long s = round(sqrt(x*x+y*y));
                if(s*s == x*x+y*y) {
                    if(binary_search(len.begin(),len.end(),s)) ++ans;
                }
            }
        }
        printf("%d\n", ans);
    }
}
