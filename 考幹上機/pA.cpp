#include <bits/stdc++.h>
#define debug(x) cout << #x << ':' << x << '\n'
#define mkp make_pair
#define ff first
#define ss second
#define mid (l+(r-l>>1))
#define N 100000
#define INF INT_MAX
#define MOD 880301
#define int ll

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

const long double PI = acos(-1);

int input(){int x;cin>>x;return x;}
int Zm(int x,int m = MOD){for(x%=m;x<0;x+=m);return x;}
int invmod(int a,int mod = MOD){
    int x = 1,y = 0, t, m = mod;
    while(mod){
        t = x-(a/mod)*y, x = y, y = t;
        t = a%mod, a = mod, mod = t;
    }
    return Zm(x,m);
}
int modpow(int e,int p,int mod = MOD){
    if(p<0)p=-p,e=invmod(e);
    int r = 1;
    while(p){
        if(p&1)r=r*e%mod;
        e=e*e%mod,p>>=1;
    }
    return Zm(r,mod);
}
int fracMod[1000000] = {1};
//int mu[N+1] = {},phi[N+1] = {};
//vector<int> primes;
void init(){//O(N) builds phi, mu, primes, fracMod
    for(int i = 1;i <= MOD;i++)fracMod[i] = Zm(fracMod[i-1]*i,MOD);//,i<100&&debug(fracMod[i]);
    /*phi[1] = mu[1] = 1;
    bitset<N+1> notP;
    for(int i = 2;i <= N;i++){
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
    }*/
}

int C(int n,int m){
    //debug(n),debug(m);
    //assert(m>=0 && n>=m);
    if(m<0 || n<m)return 0;
    return Zm(fracMod[n]*Zm(invmod(fracMod[m])*invmod(fracMod[n-m])));
}
int solve(int n,int m){
    int res = 1;
    while(m){
        res = Zm(res*C(n%MOD,m%MOD));
        n/=MOD,m/=MOD;
    }
    return res;
}

signed main(){
    //ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    init();
    int q = input(),n,m;
    while(q--){
        cin >> n >> m;
        cout << solve(n,m) << '\n';
    }
}

