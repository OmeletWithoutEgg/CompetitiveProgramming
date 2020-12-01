#include "average.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 200005;
typedef complex<double> point;
double slope(point d){ return d.imag() / double(d.real()); };
bool check(point a, point b, point c) {
    return slope(b-a) >= slope(c-a);
}
double qry(vector<point> &v, point p) {
    if(v.empty()) return -1e18;
    int x = -1;
    for(int s = 1<<__lg(v.size()); s; s>>=1) if(x+s+1 < v.size() && slope(p - v[x+s]) <= slope(p - v[x+s+1])) x += s;
    return slope(p - v[++x]);
}
struct Segtree {
    int n = N;
    vector<point> st[N<<1];
    void ins(int p, point P) {
        for(p+=n; p>0; p>>=1) {
            auto &dq = st[p];
            while(dq.size() >= 2 && check(dq[dq.size()-2], dq[dq.size()-1], P)) dq.pop_back();
            dq.push_back(P);
        }
    }
    double query(int l, int r, point P) {
        double res = -1e18;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res = max(res, qry(st[l++], P));
            if(r&1) res = max(res, qry(st[--r], P));
        }
        return res;
    }
} sgt;
int64_t pre[N];
int now;
void init() {
    now = 0;
    sgt.ins(0, point(now, pre[now]));
}

void addMonth(int K) {
    ++now;
    pre[now] = pre[now-1] + K;
    sgt.ins(now, point(now, pre[now]));
}

double maximumAverage(int L, int R) {
    return sgt.query(L, R+1, point(now, pre[now]));
}
