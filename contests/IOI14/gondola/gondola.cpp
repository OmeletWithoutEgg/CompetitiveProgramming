#include "gondola.h"
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

int valid(int n, int inputSeq[]) {
    vector<int> v(inputSeq, inputSeq+n), u = v;
    sort(u.begin(), u.end());
    for(int i = 1; i < n; i++) if(u[i] == u[i-1]) return false;
    for(int &x: v) --x;
    queue<int> q;
    for(int i = 0; i < n; i++) if(v[i] < n) q.push(i);
    while(!q.empty()) {
        int i = q.front(); q.pop();
        int j = (i+1)%n;
        if(v[j] >= n) {
            v[j] = (v[i]+1)%n;
            q.push(j);
        } else if(v[j] != (v[i]+1)%n) {
            return false;
        }
    }
    return true;
}

//----------------------

int replacement(int n, int gondolaSeq[], int replacementSeq[]) {
    int L = 0;
    int tot = n;
    vector<int> v(gondolaSeq, gondolaSeq+n), org = v;
    {
        for(int &x: org) --x;
        queue<int> q;
        for(int i = 0; i < n; i++) if(org[i] < n) q.push(i);
        if(q.empty()) {
            for(int i = 0; i < n; i++) org[i] = i+1;
        } else {
            while(!q.empty()) {
                int i = q.front(); q.pop();
                int j = (i+1)%n;
                if(org[j] >= n) {
                    org[j] = (org[i]+1)%n;
                    q.push(j);
                } else {
                    assert(org[j] == (org[i]+1)%n);
                }
            }
            for(int &x: org) ++x;
        }
    }
    vector<pair<int,int>> evt;
    for(int i = 0; i < n; i++) if(v[i] > n) evt.pb(v[i], i);
    sort(evt.begin(), evt.end());
    for(int i = 0; i < int(evt.size()); i++)
        while(tot < evt[i].first) replacementSeq[L++] = org[evt[i].second], org[evt[i].second] = ++tot;
    return L;
}

//----------------------

const int MOD = 1000000009;
int modpow(long long e, int p) {
    long long r = 1;
    for(; p; p>>=1, e=e*e%MOD) if(p&1) r = r*e%MOD;
    return r;
}
int countReplacement(int n, int inputSeq[]) {
    if(!valid(n, inputSeq)) return 0;
    vector<int> v(inputSeq, inputSeq+n);
    vector<pair<int,int>> evt;
    for(int i = 0; i < n; i++) if(v[i] > n) evt.pb(v[i], i);
    sort(evt.begin(), evt.end());
    int tot = n;
    long long ans = 1;
    for(int i = 0; i < int(evt.size()); i++) {
        // tot+1, tot+2, ... evt[i].first-1 can be arbitary placed on evt.size()-i positions
        debug(evt.size()-i, evt[i].first - tot - 1);
        ans = ans * modpow(int(evt.size()) - i, evt[i].first - tot - 1) % MOD;
        tot = evt[i].first;
    }
    if(evt.size() == n) ans = ans * n % MOD;
    return ans;
}
