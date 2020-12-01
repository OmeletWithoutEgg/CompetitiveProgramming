//#include "job.h"
#include <bits/stdc++.h>
using namespace std;

long long scheduling_cost(std::vector<int> P, std::vector<int> U, std::vector<int> D) {
    vector<int64_t> p(P.begin(),P.end());
    vector<int64_t> u(U.begin(),U.end());
    vector<int64_t> d(D.begin(),D.end());
    int n = p.size();
    struct node {
        long long u, d;
        int id;
        bool operator<(node p)const{
            return u*p.d < d*p.u;
        }
    };
    long long ans = 0;
    vector<int> pa(n);
    iota(pa.begin(), pa.end(), 0);
    function<int(int)> anc = [&](int x){
        return x==pa[x] ? x : pa[x]=anc(pa[x]);
    };
    auto add = [&](int a, int i) {
        //cerr << a << ' ' << i << '\n';
        ans -= 1LL * d[i] * u[a];
        //cerr << "ans="<<ans << '\n';
        d[a] += d[i];
        u[a] += u[i];
    };
    priority_queue<node> pq;
    for(int i = 0; i < n; i++)
        pq.push({u[i],d[i],i});
    while(pq.size()) {
        node x;
        do x=pq.top(), pq.pop(); while(pq.size() && (x.u!=u[x.id] || x.d!=d[x.id]));
        int i = x.id;
        if(p[i] == -1 || pa[i] != i) continue;
        //cerr << "u,d = " << x.u << ' ' << x.d << '\n';
        //cerr << "i = " << i << '\n';
        int a = anc(p[i]);
        pa[i] = a;
        add(a, i);
        //cout << "a: " << a << ' ' << u[a] << ' ' << d[a] << '\n';
        pq.push({u[a],d[a],a});
    }
    //cerr << "ans = " << ans << '\n';
    //cerr << u[0] << ' ' << d[0] << '\n';
    ans += 1LL * u[0] * d[0];
    return ans;
}
