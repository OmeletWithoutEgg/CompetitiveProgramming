#include <bits/stdc++.h>
#define ff first
#define ss second
#define pb emplace_back
#define debug(x) 0&&(cout<<#x<<':'<<x<<'\n')
#define mid (l+(r-l>>1))
using namespace std;
typedef long long ll;
constexpr ll N = 100025;

int K = 30;
ll n,a[N] = {},cnt;
ll res = 0;
void merges(int l,int m,int r){
    vector<ll> tmp;
    int i=l, j=m;
    while(i<m || j<r){
        if((j==r) || (i<m&&a[i]<=a[j]))
            tmp.pb(a[i++]);
        else
            tmp.pb(a[j++]),res+=m-i;
    }
    for(int i = l; i < r; i++) a[i] = tmp[i-l];
}
void CDQ(int l,int r){
    if(r-l <= K) {
        for(int i = l; i < r; i++)
            for(int j = l; j < i; j++)
                if(a[i]<a[j]) ++res;
        sort(a+l,a+r);
    }else {
        CDQ(l,mid), CDQ(mid,r);
        merges(l,mid,r);
    }
}
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n,n){
        for(int i = 0; i < n; i++) cin >> a[i];
        res = 0;
        CDQ(0,n);
        cout << "Case #" << ++cnt << ": " << res << '\n';
    }
}
