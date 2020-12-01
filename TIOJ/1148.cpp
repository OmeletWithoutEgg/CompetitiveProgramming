#pragma g++ optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#ifdef local
#define debug(x) (cerr<<#x<<" = "<<(x)<<'\n')
#else
#define debug(x) ((void)0)
#endif // local
#define int ll

using namespace std;
typedef int64_t ll;
constexpr ll N = 10025, INF = 1e18, MOD = 998244353, K = 64, inf = 1e9;

struct Line {
    ll x1,x2,y1,y2;
} L[525];
int n,emp,last;
vector<int> ans;
vector<double> interest;
void check(Line a,Line b) {
    // y = x * sa + ta = x * sb + tb
    // sa = (y2-y1)/(x2-x1)
    double sa = double(a.y2-a.y1) / (a.x2-a.x1);
    double sb = double(b.y2-b.y1) / (b.x2-b.x1);
    double ta = a.y1 - a.x1*sa;
    double tb = b.y1 - b.x1*sb;
    double x = -(ta-tb) / (sa-sb);
    if(abs(sa-sb) > 1e-6 && a.x1 <= x && x <= a.x2 && b.x1 <= x && x <= b.x2) interest.push_back(x);
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> L[i].x1 >> L[i].y1 >> L[i].x2 >> L[i].y2;
        if(L[i].x1 > L[i].x2) swap(L[i].x1,L[i].x2), swap(L[i].y1,L[i].y2);
        interest.push_back(L[i].x1), interest.push_back(L[i].x2);
    }
    for(int i = 0; i < n; i++) for(int j = 0; j < i; j++) check(L[i],L[j]);
    sort(interest.begin(),interest.end());
    interest.erase(unique(interest.begin(),interest.end()),interest.end());
    for(double c: interest) {
        int mi = -1;
        auto cmp = [c](int a,int b){
            int ya = (L[a].y2 * (c-L[a].x1) + L[a].y1 * (L[a].x2-c)) * (L[b].x2-L[b].x1);
            int yb = (L[b].y2 * (c-L[b].x1) + L[b].y1 * (L[b].x2-c)) * (L[a].x2-L[a].x1);
            return ya < yb;
        };
        for(int i = 0; i < n; i++) if(L[i].x1 <= c && c <= L[i].x2) {
            if(mi == -1 || cmp(i,mi)) mi = i;
        }
        ans.push_back(mi);
        if(mi == -1 && last != -1) emp++;
        last = mi;
    }
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    cout << ans.size() - emp << '\n';

    /*sort(L,L+n,[](Line &a, Line &b){
        // ()/() < ()/();
        return (a.y2-a.y1) * (b.x2-b.x1) < (b.y2-b.y1) * (a.x2-a.x1);
    });
    vector<Line> stk;
    for(int i = 0; i < n; i++) {
        while(stk.size() && )
    }*/
}
