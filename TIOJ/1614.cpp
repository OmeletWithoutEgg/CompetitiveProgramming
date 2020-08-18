#include <bits/stdc++.h>
#define debug(x) cout << #x << ':' << x << '\n'
#define mkp make_pair
#define ff first
#define ss second
#define REP(i,l,r) for(int i = l;i < r;i++)
#define mid (l+(r-l>>1))
#define N 100000
#define INF INT_MAX
#define MOD 1000000007
#define EL cout<<'\n'
#define int ll

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
struct piii{
    int ff,ss,th;
    piii(int f=0,int s=0,int t=0):ff(f),ss(s),th(t){}
    bool operator<(piii b){return ff!=b.ff?ff<b.ff:ss!=b.ss?ss<b.ss:th<b.th;}
};

const long double PI = acos(-1);

#define __fast_IO
#ifdef __fast_IO
template<typename T> bool input(T &x){
    x = 0;
    char c = getchar(),f = 0;
    while(c!=EOF&&c!='-'&&!isdigit(c))c = getchar();
    if(c == '-')f = 1,c = getchar();
    while(c!=EOF&&isdigit(c))x=x*10+c-'0',c = getchar();
    if(f)x = -x;
    return c!=EOF;
}
const int __buf_max = 100; int __buf_p = 0; char __buf[__buf_max] = {};
void out(){__buf[__buf_p++] = '\0', puts(__buf), __buf_p = 0;}
void out(char c){if(__buf_p+1>=__buf_max)out();__buf[__buf_p++] = c;}
template<typename T> void out(T x){
    if(__buf_p+40>=__buf_max)out();
    if(x<0)out('-'),x=-x;
    if(x==0)return out('0'),void();
    char tmp[40] = {},p = 0;
    while(x)tmp[p++]=x%10+'0',x/=10;
    while(p--)__buf[__buf_p++] = tmp[p];
}
#endif // __fast_IO
#ifdef __number_theorem
ll Zm(ll x,ll m = MOD){for(x%=m;x<0;x+=m);return x;}
ll modpow(ll e,ll p,ll mod = MOD){
    ll r = 1;
    while(p){
        if(p&1)r=r*e%mod;
        e=e*e%mod,p>>=1;
    }
    return Zm(r,mod);
}
ll invmod(ll a,ll mod = MOD){
    ll x = 1,y = 0, t, m = mod;
    while(mod){
        t = x-(a/mod)*y, x = y, y = t;
        t = a%mod, a = mod, mod = t;
    }
    return Zm(x,m);
}
ll fracMod[N+1] = {1};
ll mu[N+1] = {},phi[N+1] = {};
vector<ll> primes;
void init(){//O(N) builds phi, mu, primes, fracMod
    for(int i = 1;i <= N;i++)fracMod[i] = fracMod[i-1]*i%MOD;
    phi[1] = mu[1] = 1;
    bitset<N+1> notP;
    for(ll i = 2;i <= N;i++){
        if(!notP[i]){
            primes.push_back(i);
            phi[i] = i-1, mu[i] = -1;
        }
        for(auto p:primes){
            if(i*p>N)break;
            notP[i*p] = true;
            if(i%p){
                phi[i*p] = phi[i]*(p-1), mu[i*p] = -mu[i];
            }else{
                phi[i*p] = phi[i]*p, mu[i*p] = 0;
                break;
            }
        }
    }
}
ll C(ll n,ll m,ll p = MOD){
    ll res = 1;
    while(m){
        ll a = n%p, b = m%p;
        if(b<0||a-b<0)return 0;
        res *= fracMod[a]*invmod(fracMod[a-b])*invmod(fracMod[b]);
        n/=p, m/=p;
    }
    return res;
}
#endif // __number_theorem

//heap
int data[N+1] = {};
int siz = 0;
void build(){
    for(int i=siz;i>1;i--)for(int j=i;j>1&&data[j]<data[j>>1];j>>=1)swap(data[j],data[j>>1]);
}
int pop(){
    int res = data[1],i = 1,chd,t = data[siz--];
    while((i<<1)<=siz){
        if((i<<1)==siz||data[i<<1]<data[i<<1|1])chd = i<<1;
        else chd = i<<1|1;
        if(t>data[chd])data[i]=data[chd],i=chd;
        else break;
    }
    data[i] = t;
    return res;
}
void push(int x){
    data[++siz] = x;for(int i=siz;i>1&&data[i>>1]>data[i];i>>=1)swap(data[i],data[i>>1]);
}
signed main(){
    //ios::sync_with_stdio(0), cin.tie(0);//, cout.tie(0);
    //init();
    int n,p,res;
    while(input(n)){
        res = 0;
        REP(i,1,n+1)input(data[i]);siz = n;
        build();
        while(siz > 2){
            p = pop();
            p += pop();
            res+=p, push(p);
        }
        while(siz)res += pop();
        out(res), out('\n');
    }
    out();
}
