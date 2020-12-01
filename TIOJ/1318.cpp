#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#define pb emplace_back
#define all(v) begin(v),end(v)
#define ff first
#define ss second
using namespace std;
const int N = 200001, inf = 1e9;
inline char readchar() {
    const int B = 1<<20;
    static char buf[B], *p = buf, *q = buf;
    if(p==q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while('0'>c||c>'9') c=readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    return x;
}

int T,mx[N],mn[N],n;
vector<int> easy;
vector<pair<int,int>> hard;
int take(int t) {
    if(t < 0) return -inf;
    return upper_bound(all(easy),t) - easy.begin();
}
signed main() {
    n = nextint(), T = nextint();
    for(int i = 0,h,c; i < n; i++) {
        c = nextint(), h = nextint();
        if(h <= c-h) easy.pb(h), easy.pb(c-h);
        else hard.pb(c,h);
    }
    sort(all(easy));
    for(int i = 1; i < easy.size(); i++) easy[i] += easy[i-1];

    sort(all(hard), [](pair<int,int> a,pair<int,int> b){return a.ff<b.ff;});
    int last;
    last = -inf;
    for(int i = 0; i < hard.size(); i++) last = mx[i] = max(last,hard[i].ff-hard[i].ss);
    last = inf;
    for(int i = int(hard.size())-1; i >= 0; i--) last = mn[i] = min(last,hard[i].ss);

    int ans = take(T);
    for(int i = 0; i < hard.size(); i++) {
        ans = max(ans, take(T-mn[i]) + i*2+1);
        T -= hard[i].ff;
        ans = max(ans, take(T) + (i+1)*2);
        ans = max(ans, take(T+mx[i]) + (i+1)*2-1);
    }
    printf("%d\n", ans);
}

/*
5 12
4 3
6 2
5 3
4 3
5 2
*/

