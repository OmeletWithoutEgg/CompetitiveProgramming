#include <cstdio>
#include <deque>
#include <vector>
#include <utility>
#define pb emplace_back
using namespace std;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline unsigned nextint() {
    unsigned x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}


int n, m;
unsigned k;
struct DQ {
    static const size_t N = 1000025;
    pair<int, unsigned> v[N];
    int head = 0, tail = 0;
    pair<int, unsigned> front() const {return v[head];}
    pair<int, unsigned> back() const {return v[tail-1];}
    bool empty() const {return head==tail;}
    void pop_front() { if(++head == N) head = 0; }
    void pop_back() { if(--tail == -1) tail = N-1; }
    void push_back(pair<int, unsigned> p) {
        v[tail] = p;
        if(++tail == N) tail = 0;
    }
} mn, mx;
signed main() {
    n = nextint(), m = nextint(), k = nextint();
    vector<pair<int,int> > ans;
    for(int i = 0; i < n; i++) {
        unsigned x = nextint();
        while(!mn.empty() && mn.front().first <= i-m) mn.pop_front();
        while(!mx.empty() && mx.front().first <= i-m) mx.pop_front();
        while(!mn.empty() && mn.back().second >= x) mn.pop_back();
        while(!mx.empty() && mx.back().second <= x) mx.pop_back();
        mn.push_back({i, x}), mx.push_back({i, x});
        if(mx.front().second - mn.front().second == k) {
            int l = i-m+1, r = i;
            if(l < 0) l = 0;
            if(r-l >= 1) ans.pb(l, r);
        }
    }
    for(int i = n; i < n+m-1; i++) {
        while(!mn.empty() && mn.front().first <= i-m) mn.pop_front();
        while(!mx.empty() && mx.front().first <= i-m) mx.pop_front();
        if(mx.front().second - mn.front().second == k) {
            int l = i-m+1, r = n-1;
            if(l < 0) l = 0;
            if(r-l >= 1) ans.pb(l, r);
        }
    }
    printf("%d\n", int(ans.size()));
    for(auto p: ans) printf("%d %d\n", p.first+1, p.second+1);
}
