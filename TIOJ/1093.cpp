#pragma GCC optimize("Ofast, no-stack-protector, unroll-loops")
#pragma loop_opt(on)
#define ff first
#define ss second
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <utility>

using namespace std;
typedef double ld;
typedef pair<ld,ld> pld;
constexpr ld eps = 1e-5;
constexpr int N = 2025;
inline int readchar() {
    const int B = 1<<20;
    static char buf[B];
    static char *p = buf, *tail = buf;
    if(p == tail) {
        if((tail = buf + fread(buf, 1, B, stdin)) == buf) return EOF;
        p = buf;
    }
    return *p++;
}
inline int next_int() {
    //bool neg=false;
    int x = 0, c = readchar();
    while('0'>c || c>'9') c=readchar();
    //if(c=='-') neg=true, c=readchar();
    while('0'<=c && c<='9') x=x*10+c-'0', c=readchar();
    //if(neg) x=-x;
    return x;
}
//inline int next_int() { int x; scanf("%d", &x); return x; }

pld v[N];
ld dist(pld a,pld b){return hypot(a.ff-b.ff, a.ss-b.ss);}
ld dot(pld a,pld b){return a.ff*b.ff + a.ss*b.ss;}
ld cross(pld a,pld b){return a.ff*b.ss-a.ss*b.ff;}
pld midpoint(pld a,pld b) {return pld((a.ff+b.ff)/2, (a.ss+b.ss)/2);}
pld center(pld a,pld b,pld c) {
    ld d = (cross(a,b)+cross(b,c)+cross(c,a))*2;
    ld A2 = a.ss*a.ss+a.ff*a.ff;
    ld B2 = b.ss*b.ss+b.ff*b.ff;
    ld C2 = c.ss*c.ss+c.ff*c.ff;
    ld x = (A2*(b.ss-c.ss)+B2*(c.ss-a.ss)+C2*(a.ss-b.ss))/d;
    ld y = (A2*(c.ff-b.ff)+B2*(a.ff-c.ff)+C2*(b.ff-a.ff))/d;
    return pld(x,y);

    /*pld m = midpoint(a,b);
    pld n{b.ss-a.ss, a.ff-b.ff}; // vector that perpendicular to AB
    // res = m+kn, |c-m-kn|^2 = |kn|^2 + |m-a|^2, |m-c|^2 - |m-a|^2 = 2 k ((c-m)dot(n))
    ld prod = (dot(n,m) - dot(n,c))*2;
    if(abs(prod) < eps) {
        ld AB = dist(a,b);
        ld BC = dist(b,c);
        ld CA = dist(c,a);
        if(abs(AB+BC-CA) < eps) return midpoint(c,a);
        if(abs(CA+AB-BC) < eps) return midpoint(b,c);
        if(abs(BC+CA-AB) < eps) return midpoint(a,b);
    }
    ld AM = dist(a,m), CM = dist(c,m);
    ld k = (AM*AM - CM*CM)/prod;
    return pld(m.ff+k*n.ff, m.ss+k*n.ss);*/
}
int C,n;
long long area(pld a,pld b,pld c) {
    a.ff-=c.ff, a.ss-=c.ss;
    b.ff-=c.ff, b.ss-=c.ss;
    return abs(a.ff*b.ss-a.ss*b.ff);
}
int lcp,ucp;
pld lc[N],uc[N];
void ins(pld p) {
    while(lcp >= 2 && area(lc[lcp-2],lc[lcp-1],p) >= 0) --lcp;
    while(ucp >= 2 && area(uc[ucp-2],uc[ucp-1],p) <= 0) --ucp;
    lc[lcp++] = uc[ucp++] = p;
}
void get_pts() {
    int mx[1025],mi[1025];
    for(int i = 0; i <= C; i++) mx[i]=0, mi[i]=C;
    for(int i = 0,x,y; i < n; i++) x=next_int(), y=next_int(), mx[x]=max(mx[x],y), mi[x]=min(mi[x],y);
    lcp=ucp=0;
    for(int i = 0; i <= C; i++) if(mx[i] >= mi[i]) {
        ins({i,mi[i]});
        ins({i,mx[i]});
    }
    n = 0;
    for(int i = 1; i < lcp; i++) v[n++] = lc[i];
    for(int i = 0; i+1 < ucp; i++) v[n++] = uc[i];
}
signed main() {
    while(C=next_int(), n=next_int(), (C||n)) {
        if(n > 900000) return 3;
        get_pts();
        //shuffle(v,v+n,rng);
        pld O = v[0];
        ld r = 0;
        for(int i = 1; i < n; i++) if(dist(O,v[i])-r > eps) {
            O = v[i];
            r = 0;
            for(int j = 0; j < i; j++) if(dist(O,v[j])-r > eps) {
                O = midpoint(v[i],v[j]);
                r = dist(O,v[i]);
                for(int k = 0; k < j; k++) if(dist(O,v[k])-r > eps) {
                    O = center(v[i],v[j],v[k]);
                    r = dist(O,v[i]);
                }
            }
        }
        printf("%.3f\n", r);
    }
}

