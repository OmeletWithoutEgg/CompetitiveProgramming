#include <bits/stdc++.h>
#define ff first
#define ss second

using namespace std;
typedef pair<double,double> dpp;
constexpr double pi = acos(-1);

int n,m;
dpp A[60],B[60];
double ans;
void check(double f,double s){
    double amx = -1e18, bmi = 1e18;
    for(int i = 0;i < n;i++) amx = max(amx,A[i].ff*f+A[i].ss*s);
    for(int i = 0;i < m;i++) bmi = min(bmi,B[i].ff*f+B[i].ss*s);
    ans = max(ans,bmi-amx);
}
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    while(cin >> n >> m, n&&m){
        for(int i = 0;i < n;i++) cin >> A[i].ff >> A[i].ss;
        for(int i = 0;i < m;i++) cin >> B[i].ff >> B[i].ss;
        ans = 0;
        double l = 0, r = 2*pi;
        for(int i = 0;i < 200;i++){

            check(sin(theta),cos(theta));
        }
        if(ans <= 0) cout << "IMPOSSIBLE\n";
        else cout << fixed << setprecision(3) << ans << '\n';
    }
}
