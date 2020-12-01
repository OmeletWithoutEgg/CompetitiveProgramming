//#pragma GCC optimize("Ofast")
//#pragma loop_opt(on)
#include <bits/stdc++.h>
#define DEBUG 0
#define debug(x) DEBUG&&(cout << #x << ':' << x << '\n')
#define mkp make_pair
#define REP(i,l,r) for(int i = (l);i < (r);i++)
#define EL cout<<'\n' // end line
#define ff first
#define ss second
#define th third
#define mid (l+(r-l>>1))
#define N 200000
#define MOD 1000000007
#define int ll

using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
struct piii{ int ff,ss,th; piii(int f=0,int s=0,int t=0):ff(f),ss(s),th(t){} };
constexpr ll INF = 1e18;

template<typename U,typename V>
ostream& operator<<(ostream &o,pair<U,V> p){return o << p.ff << ' ' << p.ss;}

int n,q,l,r,c;
ll a[N+1] = {},k;
/*
8 10
9 4 8 7 7 1 2 2
1 2 3 4
2 3 4
2 1 7
2 3 8
1 3 6 13789
1 2 4 732
2 8 8
1 6 7 1
2 6 7
2 5 6

19
38
31
2
13792
27575
##
5 10
1 2 3 4 5
1 3 4 1024
1 2 5 123
2 1 4
2 3 5
2 2 2
1 2 4 832
2 3 5
1 3 4 283
2 2 4
2 1 5

2417
2421
121
3829
3968
4095
*/
signed main(){
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> q;
    for(int i = 1;i <= n;i++)cin >> a[i];
    for(int i = 0;i < q;i++){
        cin >> c;
        if(c == 1){
            cin >> l >> r >> k;
            for(int i = l;i <= r;i++)a[i]^=k;
        }else if(c == 2){
            cin >> l >> r;
            int res = 0;
            for(int i = l;i <= r;i++)res+=a[i];
            cout << res << '\n';
        }
    }
}

