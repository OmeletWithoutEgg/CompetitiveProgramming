#include <cstdio>
#include <algorithm>
#include <vector>
#define pb emplace_back
#define ff first
#define ss second
#define sort_uni(v) sort(v.begin(),v.end()),v.erase(unique(v.begin(),v.end()),v.end())
#define get_pos(v,x) lower_bound(v.begin(),v.end(),x)-v.begin()

using namespace std;
//using namespace __gnu_pbds;
//template <typename T> using rbt = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread_unlocked(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0;
    char c = readchar(), f = 0;
    while(c < '0' && c != '-') c = readchar();
    if(c == '-') c = readchar(), f = 1;
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    //printf("x = %d\n", f?-x:x);
    return f ? -x : x;
}
inline void readstr(char *s) {
    char c = readchar();
    while('A' > c || c > 'Z') c = readchar();
    while(c != ' ' && c != '\n') *s++ = c, c = readchar();
    *s++ = '\0';
}

vector<pair<int, int>> ops;
struct {
    int sum[200001], n;
    void init(int _n) {
        n = _n;
        for(int i = 1; i <= n; i++) sum[i] = 0;
    }
    void ins(int p) {
        for(; p <= n; p += p&-p) ++sum[p];
    }
    int kth(int k) {
        int x = 0;
        for(int s = 1<<__lg(n)+1; s; s >>= 1)
            if(x+s <= n && sum[x+s] <= k)
                k -= sum[x += s];
        return x+1;
    }
} BIT;
int mp[200001];
void rangeCompress() {
    vector<pair<int,int>> u;
    for(int i = 0; i < ops.size(); i++) if(ops[i].first == 0) u.pb(ops[i].second, i);
    sort(u.begin(), u.end());
    int j = 1;
    for(int i = 0; i < u.size(); i++) {
        if(i && u[i].first != u[i-1].first) ++j;
        ops[u[i].second].second = j;
        mp[j] = u[i].first;
    }
    BIT.init(j);
}
void solve() {
    rangeCompress();
    int tot = 0, k = 0;
    for(auto [t, x]: ops) {
        if(t == 0) {
            //printf("x = %d\n", x);
            BIT.ins(x);
            ++tot;
        }else if(t == 1) {
            if(k < tot) {
                printf("%d\n", mp[BIT.kth(k)]);
                k++;
            }
        }
    }
}
signed main() {
    int x;
    char com[5];
    while(true) {
        readstr(com);
        if(com[0] == 'P')
            ops.pb(0, nextint());
        else if(com[0] == 'G')
            ops.pb(1, -1);
        else if(com[1] == 'X')
            solve(), ops.clear();
        else if(com[1] == 'N')
            break;
    }
}
