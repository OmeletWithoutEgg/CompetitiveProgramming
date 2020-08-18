#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define debug(x) cerr<<#x<<" = "<<x<<'\n'
#define ff first
#define ss second

using namespace std;
typedef long long ll;
const int SZ = 75;

int dim, n, d, m;
int b[SZ*3][SZ*3][SZ*3];
ll res = 0;
void mdf(int x, int y, int z, int d) {
    x += m, y += m, z += m;
    //if(x < 0 || y < 0 || z < 0) exit(0);
    for(int i = x; i < m*3; i += i&-i)
        for(int j = y; j < m*3; j += j&-j)
            for(int k = z; k < m*3; k += k&-k)
                b[i][j][k] += d;
}
int qry(int x, int y, int z) {
    x += m, y += m, z += m;
    if(x < 0 || y < 0 || z < 0) return 0;
    if(x >= m*3) x = m*3-1;
    if(y >= m*3) y = m*3-1;
    if(z >= m*3) z = m*3-1;
    int res = 0;
    for(int i = x; i; i -= i&-i)
        for(int j = y; j; j -= j&-j)
            for(int k = z; k; k -= k&-k)
                res += b[i][j][k];
    return res;
}
signed main(){
    ios_base::sync_with_stdio(0), cin.tie(0);
    cin >> dim >> n >> d >> m;
    int a, b, c;
    if(dim == 3) {
        typedef tuple<int,int,int> Pt;
        vector<pair<int,Pt> > v(n);
        for(auto &p:v) {
            cin >> a >> b >> c;
            p.ff = a+b+c;
            p.ss = Pt(-a+b+c, a-b+c, a+b-c); // 2-m ~ m*2-1
        }
        sort(v.begin(), v.end(), [](const pair<int,Pt> &a,const pair<int,Pt> &b){return a.ff<b.ff;});
        for(int i = 0, j = 0; i < n; i++) {
            while(v[i].ff - v[j].ff > d) {
                const auto &t = v[j++].ss;
                mdf(get<0>(t), get<1>(t), get<2>(t), -1);
            }
            const auto &s = v[i].ss;
            int x1 = get<0>(s)-d-1, y1 = get<1>(s)-d-1, z1 = get<2>(s)-d-1;
            int x2 = get<0>(s)+d,   y2 = get<1>(s)+d,   z2 = get<2>(s)+d  ;
            res += qry(x2,y2,z2)
                 - qry(x1,y2,z2) - qry(x2,y1,z2) - qry(x2,y2,z1)
                 + qry(x2,y1,z1) + qry(x1,y2,z1) + qry(x1,y1,z2)
                 - qry(x1,y1,z1);
            mdf(get<0>(s), get<1>(s), get<2>(s), 1);
        }
    }else if(dim == 2) {
        typedef pair<int,int> pii;
        struct BIT : vector<long long>{
            BIT(size_t sz = 255){resize(sz+25);}
            void add(int p, int d){
                for(;p<size();p+=p&-p) at(p) += d;
            }
            int query(int p){
                if(p <= 0) return 0;
                if(p >= size()) p = size()-1;
                long long res = 0;
                for(;p;p-=p&-p) res += at(p);
                return res;
            }
        } pre(m*2);
        vector<pii> v(n);
        for(auto &p:v) cin >> a >> b, p.ff = a-b, p.ss = a+b;
        sort(v.begin(), v.end());
        for(int i = 0, j = 0; i < n; i++) {
            while(v[i].ff - v[j].ff > d) pre.add(v[j++].ss, -1);
            res += pre.query(v[i].ss+d) - pre.query(v[i].ss-d-1);
            pre.add(v[i].ss, 1);
        }
    }else if(dim == 1) {
        vector<int> v(n);
        for(auto &x:v) cin >> x;
        sort(v.begin(), v.end());
        for(int i = 0, j = 0; i < n; i++) {
            while(v[i] - v[j] > d) j++;
            res += i-j;
        }
    }
    cout << res << '\n';
}
