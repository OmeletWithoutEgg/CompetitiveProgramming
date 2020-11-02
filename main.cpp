#pragma GCC optimize("Os")
#include <unistd.h>

inline char readchar() {
    constexpr int B = 1<<10;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+read(0, buf, B)) == buf) return -1;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0' && c != -1) c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}
inline void writestr(const char *s) {
    int len = 0;
    for(; s[len]; ++len);
    write(1, s, len);
}
inline void writeint(int x) {
    static char stk[20], buf[20];
    char p = 0, q = 0;
    if(!x) stk[p++] = '0';
    while(x) stk[p++] = x%10^'0', x/=10;
    while(p) buf[q++] = stk[--p];
    write(1, buf, q);
}

const int N = 225;
int dis[N];
int g[N][N], my[N];
int n, m;
int q[N];
int prv[N], py[N];
bool BFS(int s) {
    int head = 0, tail = 0;
    q[tail++] = s;
    dis[s] = 0;
    while(head != tail) {
        int i = q[head++];
        for(int j = 0; j < m; j++) if(!g[i][j]) {
            int x = my[j];
            if(x == -1) {
                my[j] = i;
                for(int x = i; x != s; x = prv[x]) my[py[x]] = prv[x];
                return true;
            }
            if(dis[x] == -1) {
                dis[x] = dis[i] + 1;
                prv[x] = i;
                py[x] = j;
                q[tail++] = x;
            }
        }
    }
    return false;
}
signed main() {
    int tc = 0;
    while(n = nextint()) {
        m = nextint();
        for(int i = 0; i < n; i++) for(int j = 0; j < m; j++) g[i][j] = nextint();
        int ans = 0;
        for(int i = 0; i < m; i++) my[i] = -1;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) dis[j] = -1;
            if(BFS(i)) {
                ++ans;
            }
        }
        ans = (n+m-ans) * 2;
        writestr("Case ");
        writeint(++tc);
        writestr(": ");
        writeint(ans);
        writestr("\n");
        /* printf("Case %d: %d\n", ++tc, ans); */
    }
}
