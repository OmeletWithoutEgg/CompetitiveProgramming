#include <bits/stdc++.h>
#define debug(x) 1&&(cout<<#x<<':'<<x<<'\n')
#define mkp make_pair
#define pb emplace_back
#define ff first
#define ss second
#define SZ(v) (ll(v.size())
#define REP(i,l,r) for(int i = l;i < r;i++)
#define PER(i,r,l) for(int i = r;--i >= l;)
#define mid (l+(r-l>>1))

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
struct piii{
    int ff,ss,th;
    piii(int f=0,int s=0,int t=0):ff(f),ss(s),th(t){}
    bool operator<(piii b){return ff!=b.ff?ff<b.ff:ss!=b.ss?ss<b.ss:th<b.th;}
};
const long double PI = acos(-1);
const ll INF = 1e18, MOD = 1000000007;

#define __fast_IO
#ifdef __fast_IO
#define EL out('\n')
template<typename T> bool input(T &x){
    x = 0;
    char c = getchar(),f = 0;
    while(c!=EOF&&c!='-'&&!isdigit(c))c = getchar();
    if(c == '-')f = 1,c = getchar();
    while(c!=EOF&&isdigit(c))x=x*10+c-'0',c = getchar();
    if(f)x = -x;
    return c!=EOF;
}
const int __buf_max = 100000; int __buf_p = 0; char __buf[__buf_max+40] = {};
void out(){ REP(i,0,__buf_p)putchar(__buf[i]); __buf_p = 0; }
void out(char c){__buf[__buf_p++] = c;if(__buf_p >= __buf_max)out();}
template<typename T> void out(T x){
    if(x<0)__buf[__buf_p++] = '-', x = -x;
    if(x==0)return out('0'),void();
    char tmp[40] = {},p = 0;
    while(x)tmp[p++]=x%10+'0',x/=10;
    while(p--)__buf[__buf_p++] = tmp[p];
    if(__buf_p >= __buf_max)out();
}
template<typename iter> void out(iter BGN,iter END){ for(iter it = BGN;it != END;++it)out(*it),out(' '); }
#else
#define EL cout<<'\n'
#endif // __fast_IO

constexpr ll N = 200000, MX_BIT = 30;
ll v[N+1] = {}, n, q, c, k, l, r;
struct node{
    int cnt[MX_BIT][2], tag[MX_BIT];
    node *l,*r;
    void pull(){
        if(!l||!r)return;
        REP(b,0,MX_BIT)cnt[b][0]=l->cnt[b][0]+r->cnt[b][0], cnt[b][1]=l->cnt[b][1]+r->cnt[b][1];
    }
    void push(){
        if(l&&r)REP(b,0,MX_BIT)if(tag[b]){
            swap(l->cnt[b][0],l->cnt[b][1]),l->tag[b]=!l->tag[b];
            swap(r->cnt[b][0],r->cnt[b][1]),r->tag[b]=!r->tag[b];
            tag[b]=0;
        }
    }
    node(int v){
        int f;
        REP(b,0,MX_BIT)f=(v>>b)&1,cnt[b][f]=1,cnt[b][!f]=0;
    }
    node(node *l,node *r):l(l),r(r){pull();}
} *root;
node *build(ll arr[],int l = 0,int r = n){
    return (l+1>=r) ? new node(arr[l]) : new node(build(arr,l,mid),build(arr,mid,r));
}
/*void traversal(node*cur=root,int l=0,int r=n,int d=0){
    if(!cur)return;
    REP(_,0,d)cout<<'\t';
    traversal(cur->l,l,mid,d+1);
    REP(b,0,MX_BIT)cout<<b<<' '<<cur->cnt[b][0]<<'/'<<cur->cnt[b][1]<<','<<' ';cout<<'\n';
    traversal(cur->r,mid,r,d+1);
}*/
ll query(int ql,int qr,node *cur = root,int l = 0,int r = n){
    if(ql>=r || l>=qr || !cur)return 0;
    cur->push();
    if(ql<=l && r<=qr){
        ll res=0;
        REP(b,0,MX_BIT)res+=ll(cur->cnt[b][1])<<b;
        return res;
    }
    return query(ql,qr,cur->l,l,mid)+query(ql,qr,cur->r,mid,r);
}
void modify(int ml,int mr,ll k,node *cur = root,int l = 0,int r = n){
    if(ml>=r || l>=mr || !cur)return;
    cur->push();
    if(ml<=l && r<=mr){
        REP(b,0,MX_BIT)if((k>>b)&1)swap(cur->cnt[b][0],cur->cnt[b][1]), cur->tag[b]=1;
        return;
    }
    modify(ml,mr,k,cur->l,l,mid),modify(ml,mr,k,cur->r,mid,r);
    cur->pull();
}
signed main(){
    //ios::sync_with_stdio(0), cin.tie(0);
    input(n), input(q);
    REP(i,0,n)input(v[i]);
    root = build(v,0,n);
    //traversal();
    REP(i,0,q){
        input(c);
        if(c == 1){
            input(l), input(r), input(k), --l;
            modify(l,r,k);
        }else if(c == 2){
            input(l), input(r), --l;
            out(query(l,r)),out('\n');
        }//else if(c == 3)traversal();
    }
    out();
}
