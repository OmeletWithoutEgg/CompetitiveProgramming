#include <vector>
#include <tuple>
#include <bitset>
#include <algorithm>
#include <queue>
#define ff first
#define ss second
#define pb emplace_back

const int N = 30025;
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

int n;
std::bitset<N> out;
std::tuple<int,int,int,int> evt[N*2];
signed main() {
    while(n = nextint()) {
        for(int i = 0; i < n; i++) {
            int L = nextint(), H = nextint(), R = nextint();
            evt[i*2] = {L, 0, i, H};
            evt[i*2+1] = {R, 1, i, H};
        }
        for(int i = 0; i <= n; i++) out[i] = false;
        int last = -1;
        std::priority_queue<std::pair<int,int>> pq;
        pq.push({0,n});
        n *= 2;
        std::sort(evt, evt+n);
        for(int i = 0, j; i < n; i = j) {
            int p = std::get<0>(evt[i]);
            for(j = i; j < n; j++) {
                auto [pos, type, id, h] = evt[j];
                if(pos != p) break;
                if(type == 1)
                    out[id] = true;
                else
                    pq.push({h, id});
            }
            while(out[pq.top().ss]) pq.pop();
            int H = pq.top().ff;
            if(last != H) {
                printf("%d %d%c", p, H, (j == n ? '\n' : ' '));
                last = H;
            }
        }
    }
}
