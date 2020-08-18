#include <bits/stdc++.h>
#define pb emplace_back
#define mem(v,x) memset(v, x, sizeof(v))
#define ff first
#define ss second

using namespace std;
const int N = 100025;

int sum[N<<1],tag[N];
vector<pair<int,int>> stk;
void upd(int p, int d, int h) {
    sum[p] += d * (1<<h);
    if(p < N) tag[p] += d;
}
void push(int p) {
    for(int h = __lg(N); h >= 0; h--) {
        int i = p>>h;
        if(!tag[i>>1]) continue;
        upd(i, tag[i>>1], h);
        upd(i^1, tag[i>>1], h);
        tag[i>>1] = 0;
    }
}
void pull(int p) {
    for(int h = 0; p > 1; h++, p>>=1) sum[p>>1] = sum[p]+sum[p^1] + tag[p>>1] * (2<<h);
}
void modify(int l, int r, int d) {
    int L = l, R = r, h = 0;
    for(l+=N, r+=N; l<r; l>>=1, r>>=1, h++) {
        if(l&1) upd(l++, d, h);
        if(r&1) upd(--r, d, h);
    }
    pull(L+N), pull(R-1+N);
}
int query(int l, int r) {
    push(l+N), push(r-1+N);
    int res = 0;
    for(l+=N, r+=N; l<r; l>>=1, r>>=1) {
        if(l&1) res += sum[l++];
        if(r&1) res += sum[--r];
    }
    return res;
}
void ins(int l, int r, int c) {
    c -= query(l, r);
    if(c <= 0) return;
    int now = r;
    while(stk.size() && now - stk.back().ss <= c) {
        c -= now - stk.back().ss;
        now = stk.back().ff;
        modify(stk.back().ff, stk.back().ss, -1);
        stk.pop_back();
    }
    stk.pb(now-c, r);
    modify(now-c, r, 1);
    //for(auto s: stk) cout << '[' << s.ff << ',' << s.ss-1 << ']' << ' '; cout << '\n';
}
struct seg {
    int l, r, c;
} v[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    while(cin >> n && n) {
        for(int i = 0; i < n; i++) cin >> v[i].l >> v[i].r >> v[i].c;
        sort(v,v+n, [](seg &a, seg &b){return a.r<b.r;});
        stk.clear();
        mem(sum, 0), mem(tag, 0);
        for(int i = 0; i < n; i++) ins(v[i].l, v[i].r, v[i].c);
        int sum = 0;
        for(auto s: stk) sum += s.ss - s.ff;
        cout << sum << '\n';
    }
}
