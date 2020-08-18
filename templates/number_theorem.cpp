ll invmod(ll a,ll m = MOD){
    ll mod = m, x = 1, y = 0, t;
    while(m)t=x-(a/m)*y,x=y,y=t, t=a%m,a=m,m=t;
    x%=mod, x<0&&(x+=mod);
    return x;
}
ll modadd(ll&a,ll b,ll m = MOD){ return a+=b, (a>=m)&&a%=m, (a<0)&&a+=m, a;}
ll modpow(ll e,ll p,ll m = MOD){ ll r = 1; while(p) (p&1)&&(r=r*e%m), e=e*e%m, p>>=1; return r;}
int facMod[N] = {1};
bool notP[N];
int mu[N] = {}, phi[N] = {};
vector<int> primes;
void init(){//O(N) builds phi, mu, primes, facMod
    for(int i = 1;i < N;i++)facMod[i] = 1LL*facMod[i-1]*i%MOD;
    phi[1] = mu[1] = 1;
    for(int i = 2;i < N;i++){
        if(!notP[i]){
            primes.pb(i);
            phi[i] = i-1, mu[i] = -1;
        }
        for(int p:primes){
            if(i*p>=N)break;
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
bool is_p(int x){}
ll C(ll n,ll m,ll p){
    ll res = 1;
    while(m){
        ll a = n%p, b = m%p;
        if(b<0||a-b<0)return 0;
        res = res*facMod[a]%p*invmod(facMod[a-b],p)%p*invmod(facMod[b],p)%p;
        n/=p, m/=p;
    }
    return res;
}

