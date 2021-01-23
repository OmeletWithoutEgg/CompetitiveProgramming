#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define TAK(args...) std::ostream &operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { int f=0; O << BEG; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(vector, "[", "]", e)
NIE(map, "{", "}", e.first << ',' << e.second)
template <typename T, size_t N> TAK(std::array<T,N> v) { return O << std::vector<T>(v.begin(), v.end()); }
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
#define int ll

using namespace std;
using ll = long long;
using ld = double;
const int N = 100002, MOD = 1000000007, K = 128;
const ll INF = 1e18;
const ld PI = acos(-1);

struct Basis {
    vector<int> b;
    array<int,7> cnt;
    Basis() : b{}, cnt{} {}
    Basis & operator+=(int x) {
        for(int y: b)
            x = min(x, x^y);
        if(x) {
            b.pb(x);
            for(int j = 0; j < 7; j++) if(x >> j & 1) ++cnt[j];
        }
        return *this;
    }
    vector<int> span() const {
        int n = b.size();
        vector<int> res(1<<n);
        for(int i = 0; i < n; i++) res[1<<i] = b[i];
        for(int i = 1; i < (1<<n); i++) res[i] = res[i&-i] ^ res[i-(i&-i)];
        return res;
    }
    size_t size() const { return b.size(); }
    int calc(int x) {
        // return sum(y^x for y in span());
        int res = 0;
        // for(int y: span())
        //     res += y ^ x;
        // return res;
        auto take = [](int n, int d) {
            if(n == 0) return d ? 0 : 1;
            return 1 << n-1;
        };
        int n = b.size();
        for(int j = 0; j < 7; j++)
            res += (1<<j) * (1<<(n-cnt[j])) * take(cnt[j], ~x>>j&1);
        return res;
    }
};

Basis A[1005][1005], B[1005][1005], C[1005][1005];

struct Segtree {
    bitset<128> st[2005];
    bitset<128>
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];
    cin >> q;
    vector<int> pw(q+1);
    pw[0] = 1;
    for(int i = 1; i <= q; i++) pw[i] = pw[i-1] * 2LL % MOD;
    vector<tuple<int,int,int>> Qs(q);
    vector<tuple<int,int,int>> evt;
    for(auto &[l, r, x]: Qs) {
        cin >> l >> r >> x;
        --l, --r;
        evt.pb(l, 1, x);
        evt.pb(r+1, -1, x);
    }

    int ans = 0;
    sort(all(evt));
    map<int,int> mp;
    for(int i = 0, j = 0; i < n; i++) {
        while(j < q*2 && get<0>(evt[j]) <= i) {
            auto [_, v, x] = evt[j++];
            if(_ != i) continue;
            mp[x] += v;
            if(mp[x] == 0) mp.erase(x);
        }
        debug(mp);
        Basis b;
        // make basis
        for(auto [val, cnt]: mp)
            b += val;
        // enumerate basis
        int cnt = 1LL * pw[q - b.size()] * (i+1) * (n-i);
        for(int x: b.span()) {
            int ai = a[i] ^ x;
            ans = (ans + 1LL * ai * ai * cnt) % MOD;
            debug(ai, cnt);
        }
    }

    auto calc = [&](int i, int j) {
        /*
        for(auto [l, r, x]: Qs) {
            if(l <= i && j <= r) {
                C += x;
            } else if(l <= i && r >= i && r < j) {
                A += x;
            } else if(l > i && l <= j && r >= j) {
                B += x;
            }
        }
        */
        int res = 0;
        for(int x: C[i][j].span()) {
            int ai = a[i] ^ x, aj = a[j] ^ x;
            debug(ai, aj);
            res = (res + 1LL * A[i][j].calc(ai) * B[i][j].calc(aj)) % MOD;
        }
        debug(res);
        return res * pw[q - C[i][j].size() - A[i][j].size() - B[i][j].size()] % MOD;
    };

    sgt.init(n);
    for(int i = 0, it = 0; i < n; i++) {
        while(it < q*2 && get<0>(evt[it]) <= i) {
            auto [l, r, x] = evt[j++];
            if(l != i) continue;
            sgt.add(r, x);
        }
        for(int j = i+1; j < n; j++) {
            auto p = sgt.query(j, n);
            // C += p;
            for(int b = 0; b < K; b++) if(p[b]) C[i][j] += b;
            auto q = sgt.query(i, j);
            // A += q;
            for(int b = 0; b < K; b++) if(q[b]) A[i][j] += b;
        }
    }
    sort(all(evt), [](auto a, auto b){return get<1>(a) > get<1>(b);});
    sgt.init(n);
    for(int j = n-1, it = 0; j >= 0; j--) {
        while(it < q*2 && get<1>(evt[it]) >= j) {
            auto [l, r, x] = evt[it--];
            if(r != j) continue;
            sgt.add(l, x);
        }
        for(int i = 0; i < j; i++) {
            auto m = sgt.query(i+1, j+1);
            // B += m;
            for(int b = 0; b < K; b++) if(m[b]) B[i][j] += b;
        }
    }


    for(int i = 0; i < n; i++) {
        for(int j = i+1; j < n; j++) {
            int cnt = 2 * (i+1) * (n-j);
            ans = (ans + 1LL * calc(i, j) * cnt) % MOD;
        }
    }

    cout << ans << '\n';
}
