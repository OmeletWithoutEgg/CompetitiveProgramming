#include"holiday.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
void qqbx(const char *s) {}
template <typename H, typename ...T> void qqbx(const char *s, const H& h, T&& ...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) qqbx(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
using namespace std;
using ll = long long;

ll calc(int n, int start, int d, vector<int> &v) {
    ll best = 0;
    vector<vector<ll>> f(n, vector<ll>(n));
    for(int i = 0; i <= start; i++) {
        priority_queue<int, vector<int>, greater<int>> pq;
        ll sum = 0, mx = 0;
        int mxpos = -1;
        for(int j = start-1; j >= i; j--) {
            pq.push(v[j]);
            sum += v[j];
        }
        for(int j = start; j < n; j++) {
            pq.push(v[j]);
            sum += v[j];
            int len = start - i + j - i;
            if(d-len < 0) break;
            while(int(pq.size()) > d-len) sum -= pq.top(), pq.pop();
            if(mx < sum) mxpos = j;
            f[i][j] = sum;
            mx = max(mx, sum);
        }
        /* cerr << mxpos << (i==start ? '\n' : ' '); */
        best = max(best, mx);
    }
    return best;
}
long long int findMaxAttraction(int n, int start, int d, int attraction[]) {
    if(start == 0) {
        priority_queue<int, vector<int>, greater<int>> pq;
        ll sum = 0;
        ll mx = 0;
        for(int i = 0; i < n; i++) {
            pq.push(attraction[i]);
            sum += attraction[i];
            if(d - i > 0) {
                int k = d - i;
                while(pq.size() > k) sum -= pq.top(), pq.pop();
                mx = max(mx, sum);
            }
        }
        return mx;
    }
    ll best = 0;
    vector<int> v(attraction, attraction+n);
    best = max(best, calc(n, start, d, v));
    debug(best);
    reverse(all(v));
    start = n-1-start;
    best = max(best, calc(n, start, d, v));
    return best;
}
