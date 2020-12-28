#include <bits/stdc++.h>
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
using ld = long double;
const int inf = 1e9;

struct XorBase {
    bool ok;
    ll id, has;
    XorBase() : ok(true), id(0), has(0) {}
    int isIndep(int x) {
        // returns non-zero if independent
        for(ll s = has; s; s -= s & -s) {
            int i = __lg(s & -s);
            x = min(x, x ^ i);
        }
        return x;
    }
    XorBase &operator+=(int x) {
        if(!ok) return *this;
        x = isIndep(x);
        if(!x) {
            ok = false;
            has = 1;
        } else {
            ll nId = id;
            for(int i = 0; i < 32; i++) if(id >> i & 1) nId |= 1LL << (i ^ x);
            nId |= 1LL << x;
            id = nId;
            has |= 1LL << x;
        }
        return *this;
    }
    XorBase &operator+=(const XorBase &rhs) {
        for(ll s = rhs.has; s; s -= s & -s) {
            int i = __lg(s & -s);
            *this += i;
        }
        return *this;
    }
    friend bool operator<(const XorBase &a, const XorBase &b) {
        return a.id < b.id;
    }
};
int cnt = 0;
set<XorBase> vis;
void dfs(XorBase org, int last = 32) {
    if(vis.count(org)) return;
    vis.insert(org);
    debug(bitset<32>(org.has), bitset<32>(org.id));
    for(int i = 0; i < last; i++) {
        XorBase B = org;
        B += i;
        if(B.ok)
            dfs(B, i), ++cnt;
    }
}
signed main() {
    dfs(XorBase());
    debug(cnt);
    debug(vis.size());
}
