#pragma g++ optimize("O3")
#pragma loop_opt(on)
#include <cstdio>
#include <vector>
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
const int N = 10000001;
std::vector<int> prs;
int d[N];
char np[N];
signed main() {
    d[1] = 1;
    for(int i = 2; i < N; i++) {
        if(!np[i]) {
            np[i] = 1;
            d[i] = 2;
            if(1LL*i*i < N) prs.emplace_back(i);
        }
        for(long long p: prs) {
            if(i*p >= N) break;
            if(i%p) {
                np[i*p] = 1;
                d[i*p] = d[i]*d[p];
            }else {
                np[i*p] = np[i]+1;
                d[i*p] = d[i]/(np[i]+1)*(np[i]+2);
                break;
            }
        }
    }
    int q = nextint();
    while(q--) {
        int n = nextint();
        printf("%d\n", d[n]);
    }
}
