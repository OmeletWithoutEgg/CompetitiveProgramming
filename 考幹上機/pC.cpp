#include <bits/stdc++.h>
#define DEBUG 0
#define debug(x) DEBUG&&(cout << #x << ':' << x << '\n')
#define mkp make_pair
#define ff first
#define ss second
#define mid (l+(r-l>>1))
#define N 100000
#define MOD 1000000007

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
const ll INF = 1e18;
const long double PI = acos(-1);

template<typename U,typename V>
ostream& operator<<(ostream &o,pair<U,V> p){return o << p.ff << ' ' << p.ss;}
ll input(){ll x;cin>>x;return x;}
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
/*ll fracMod[N+1] = {1};
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
}*/

pll slope(pll f,pll t){
    ll dy = f.ss-t.ss, dx = f.ff-t.ff;
    if(!dx || !dy)return dy?pll(1,0):pll(0,1);
    if(dx < 0)dy *= -1, dx *= -1;
    ll g = __gcd(abs(dy),abs(dx));
    dy /= g, dx /= g;
    return pll(dy,dx);
}
pll dots[6000] = {};
map<pll,pll> mp;
void solve(){
	int n,l = 0;
	ll x,y;
	scanf("%d",&n);
    mp.clear();
	for(int i = 0;i < n+1;i++)scanf("%lld%lld", &x, &y),mp[pll(x,y)]=pll(0,0);
	for(auto p:mp)dots[l++]=p.ff;
	if(l<=2)return puts("Safe"),void();
	for(int i = 0;i < l;i++){
        mp.clear();
        for(int j = i+1;j < l;j++){
            pll s = slope(dots[j],dots[i]);
            if(mp.count(s))return debug(dots[i]),debug(dots[j]),debug(mp[s]),puts("Dangerous"),void();
            else mp[s] = dots[j];
        }
	}
	puts("Safe");
}

signed main(){
    //ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    //init();
    int t;
    scanf("%d",&t);
    for(int i = 0;i < t;i++)debug(i),solve();
    //system("PAUSE");
}
