#include <bits/stdc++.h>
#define debug(x) cout << #x << ':' << x << '\n'
#define mkp make_pair
#define ff first
#define ss second
#define REP(i,l,r) for(int i = l;i < r;i++)
#define mid (l+(r-l>>1))
#define N 10000
#define INF INT_MAX
#define MOD 1000000007
#define EL cout<<'\n'

using namespace std;
typedef long long ll;

const long double PI = acos(-1);
template<typename U,typename V> void maxeq(U &u,const V &v){if(u<v)u=v;}
template<typename U,typename V> void mineq(U &u,const V &v){if(u>v)u=v;}
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
ll mu[N+1] = {},phi[N+1] = {};
vector<ll> primes;
bitset<N+1> notP;
bool is_p(int x){
    if(x <= N)return !notP[x];
    for(auto p : primes){
        if(x%p == 0)return 0;
        if(p*p > x)return 1;
    }
    return 1;
}
void init(){//O(N) builds phi, mu, primes, fracMod
    phi[1] = mu[1] = 1;
    for(ll i = 2;i <= N;i++){
        //if(!(i&0xfffff))debug(i);
        if(!notP[i])primes.push_back(i);
        for(auto p:primes){
            if(i*p>N)break;
            notP[i*p] = true;
            if(i%p == 0)break;
        }
    }
    /*for(ll i = N+1;i <= 1e8;){
        if((i&0xffff1) == 0xffff1)debug(i);
        if(is_p(i))primes.push_back(i);
        i+=2;
        if(is_p(i))primes.push_back(i);
        i+=4;
    }*/
}
signed main(){
    //ios::sync_with_stdio(0), cin.tie(0);//, cout.tie(0);
    init();
    ll mx = 0,k;
    cout<<primes.size()<<'\n';
    REP(i,0,primes.size()-1)cout<<primes[i+1]-primes[i]<<' ',maxeq(mx,primes[i+1]-primes[i]);
    cout<<mx<<'\n';
}
