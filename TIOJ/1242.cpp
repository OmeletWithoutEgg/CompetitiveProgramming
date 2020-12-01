#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>

typedef long long ll;
constexpr ll N = 1025;
inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p=buf, *q=buf;
    if(p == q && (q=buf+fread(buf,1,B,stdin)) == (p=buf)) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while('0'>c || c>'9') c = readchar();
    while('0'<=c&&c<='9') x=x*10+(c^'0'), c=readchar();
    return x;
}

int n,m,q;
ll cnt[N][N],xsum[N][N],ysum[N][N],ans[100001];
ll sum(ll v[][N],int x1,int x2,int y1,int y2) {
    return v[x2][y2] - v[x1-1][y2] - v[x2][y1-1] + v[x1-1][y1-1];
}
signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
    //cin >> n >> m;
    n = nextint(), m = nextint();
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) cnt[i][j] = nextint();
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        xsum[i][j] = cnt[i][j] * i;
        ysum[i][j] = cnt[i][j] * j;
    }
    for(int i = 1; i <= n; i++) for(int j = 1; j <= m; j++) {
        cnt[i][j] += cnt[i-1][j]+cnt[i][j-1]-cnt[i-1][j-1];
        xsum[i][j] += xsum[i-1][j]+xsum[i][j-1]-xsum[i-1][j-1];
        ysum[i][j] += ysum[i-1][j]+ysum[i][j-1]-ysum[i-1][j-1];
    }
    //cin >> q;
    q = nextint();
    for(int i = 0; i < q; i++) {
        int x1,x2,y1,y2;
        //cin >> x1 >> x2 >> y1 >> y2;
        x1 = nextint();
        x2 = nextint();
        y1 = nextint();
        y2 = nextint();
        ll tot = sum(cnt,x1,x2,y1,y2), half = (tot+1)/2;
        int x = x1-1, y = y1-1, s = 1024;
        while(s) {
            if(x+s <= x2 && sum(cnt,x1,x+s,y1,y2) < half) x += s;
            if(y+s <= y2 && sum(cnt,x1,x2,y1,y+s) < half) y += s;
            s>>=1;
        }
        ++x, ++y;
        //debug(x), debug(y);
        ans[i] += x*sum(cnt,x1,x-1,y1,y2) - sum(xsum,x1,x-1,y1,y2);
        ans[i] += sum(xsum,x+1,x2,y1,y2) - x*sum(cnt,x+1,x2,y1,y2);
        ans[i] += y*sum(cnt,x1,x2,y1,y-1) - sum(ysum,x1,x2,y1,y-1);
        ans[i] += sum(ysum,x1,x2,y+1,y2) - y*sum(cnt,x1,x2,y+1,y2);
    }
    for(int i = 0; i < q; i++) printf("%lld\n", ans[i]);
}

