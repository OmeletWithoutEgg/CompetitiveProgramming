#include <cstdio>
#include <algorithm>
#include <vector>

const int N = 4001;
int s, n, r;
std::pair<int,int> p[N];
int pa[N], sz[N];
std::vector<int> ans;
int dis(std::pair<int,int> a, std::pair<int,int> b) {return (a.first-b.first)*(a.first-b.first) + (a.second-b.second)*(a.second-b.second);}
int anc(int x) {return x==pa[x]?x:pa[x]=anc(pa[x]);}
void uni(int x, int y) {
    if((x=anc(x)) == (y=anc(y))) return;
    if(sz[x] < sz[y]) s=x, x=y, y=s;
    pa[y] = x, sz[x] += sz[y];
}
signed main() {
    while(~scanf("%d%d%d", &s, &n, &r)) {
        p[0] = {s, s};
        for(int i = 1; i <= n; i++) {
            p[i].first = (p[i-1].first*269+11)%103;
            p[i].second = (p[i-1].second*271+13)%97;
            pa[i] = i, sz[i] = 1;
        }
        sort(p+1, p+n+1);
        for(int i = 1; i <= n; i++) {
            for(int j = i+1; j <= n; j++) {
                if(p[j].first - p[i].first > r) break;
                if(dis(p[i],p[j]) <= r*r)
                    uni(i, j);
            }
        }
        ans.clear();
        for(int i = 1; i <= n; i++) if(pa[i] == i) ans.emplace_back(sz[i]);
        std::sort(ans.begin(), ans.end());
        printf("%d\n", int(ans.size()));
        for(int x: ans) printf("%d ", x);
        puts("");
    }
}
