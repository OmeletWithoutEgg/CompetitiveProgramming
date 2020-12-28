//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\Q
//   \###################\Q
//    \        ____       \B
//     \_______\___\_______\X
// An AC a day keeps the doctor away.
 
#ifdef local
#include <bits/extc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(deque, "[", "]", e); NIE(vector, "[", "]", e); NIE(set, "{", "}", e);
NIE(multiset, "{", "}", e); NIE(unordered_set, "{", "}", e);
NIE(map , "{", "}", e.first << ":" << e.second);
NIE(unordered_map , "{", "}", e.first << ":" << e.second);
template <typename ...T> TAK(std::pair<T...> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> TAK(std::array<T,N> a) { return O << std::vector<T>(a.begin(), a.end()); }
template <typename ...T> TAK(std::tuple<T...> t) {
    return O << "(", std::apply([&O](T ...s){ int f=0; (..., (O << (f++ ? ", " : "") << s)); }, t), O << ")";
}
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    if(!cnt) return std::cerr << "\033[1;32m() = ()\033\[0m\n", void();
    (std::cerr << "\033[1;32m(" << s << ") = (" , ... , (std::cerr << args << (--cnt ? ", " : ")\033[0m\n")));
}
#else
#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <bits/extc++.h>
#include <bits/stdc++.h>
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)
#define get_pos(v,x) int(lower_bound(begin(v),end(v),x)-begin(v))
#define sort_uni(v) sort(begin(v),end(v)),v.erase(unique(begin(v),end(v)),end(v))
#define pb emplace_back
#define ff first
#define ss second
#define mem(v,x) memset(v,x,sizeof v)
 
using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = std::priority_queue<T,vector<T>,less<T> >;
template <typename T> using min_heap = std::priority_queue<T,vector<T>,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 1000025, INF = 1e18, MOD = 1000000007, K = 14699, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

inline ll HB(ll x) { return 1LL << __lg(x); }
struct XorBase {
    bool ok;
    ll id, has;
    XorBase() : ok(true), id(0), has(0) {}
    int isIndep(int x) {
        // returns non-zero if independent
        for(ll s = has; s; s -= HB(s)) {
            int i = __lg(HB(s));
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
int tranElem[375][32], tranObj[375][375];
int trans(int x, int c, bool type) {
    if(x == -1 || c == -1) return -1;
    if(type == 0)
        return tranElem[x][c];
    else
        return tranObj[x][c];
}
void precalc() {
    int tot = 0;
    map<XorBase,int> vis;
    map<int,XorBase> mp;
    function<int(XorBase)> dfs = [&](XorBase org) {
        assert(org.ok);
        if(vis.count(org)) return vis[org];
        int &id = vis[org];
        id = tot++;
        mp[id] = org;
        for(int i = 0; i < 32; i++) {
            XorBase B = org;
            B += i;
            if(B.ok) {
                int jd = dfs(B);
                tranElem[id][i] = jd;
            } else {
                tranElem[id][i] = -1;
            }
        }
        return id;
    };
    dfs(XorBase());
    debug(vis.size());
    for(int i = 0; i < tot; i++) {
        for(int j = 0; j < tot; j++) {
            auto A = mp[i];
            auto B = mp[j];
            A += B;
            if(A.ok)
                tranObj[i][j] = vis[A];
            else
                tranObj[i][j] = -1;
        }
    }
}

void add(int &x, int v) {
    x += v - MOD;
    x += (x >> 31) & MOD;
}
signed main() {
    precalc();
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<tuple<int,int,int>> cross;
    vector<vector<pair<int,int>>> g(n);
    vector<bool> nei(n);
    for(int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        --a, --b;
        g[a].pb(c, b);
        g[b].pb(c, a);
        if(a == 0) nei[b] = true;
        if(b == 0) nei[a] = true;
    }
    debug(nei);
    vector<int> group(n, -1), xorSum(n);
    vector<bool> vis(n);
    for(auto [weight, root]: g[0]) {
        function<void(int,int,int)> dfs = [&](int i, int p, int xo) {
            xorSum[i] = xo;
            group[i] = root;
            vis[i] = true;
            for(auto [w, j]: g[i])
                if(j != p) {
                    if(nei[j] || vis[j]) {
                        if(i < j) cross.pb(i, j, w);
                    } else
                        dfs(j, i, xo ^ w);
                }
        };
        dfs(root, 0, weight);
    }
    debug(group);
    vector<int> bases(n);
    // sort_uni(cross);
    for(auto [a, b, c]: cross) {
        // if(group[a] == -1 || group[b] == -1) continue;
        if(group[a] == group[b])
            bases[group[a]] = trans(bases[group[a]], c ^ xorSum[a] ^ xorSum[b], 0);
    }
    vector<bool> calced(n); // if this group is calculated as triangle
    int DP[2][374] = {};
    DP[1][0] = 1;
    int dir = 0;
    for(auto [a, b, c]: cross) {
        // if(group[a] == -1 || group[b] == -1) continue;
        if(group[a] != group[b]) {
            assert(nei[a] && nei[b] && group[a] == a && group[b] == b);
            assert(!calced[a] && !calced[b]);
            calced[a] = calced[b] = true;
            // DP[B + (bases[ga] + bases[gb])] += 2 * DP[B]
            // DP[B + (bases[ga] + bases[gb] + { c ^ xorSum[a] ^ xorSum[b] })] += DP[B]
            int A = trans(bases[a], bases[b], 1);
            if(A == -1) continue;
            for(int i = 0; i < 374; i++) DP[dir][i] = DP[!dir][i];
            for(int i = 373; i >= 0; i--) {
                int B = i;
                int val = DP[!dir][i];
                B = trans(B, A, 1);
                if(B == -1) continue;
                add(DP[dir][B], val * 2 < MOD ? val * 2 : val * 2 - MOD);
                B = trans(B, c ^ xorSum[a] ^ xorSum[b], 0);
                if(B == -1) continue;
                add(DP[dir][B], val);
            }
            dir = !dir;
        }
    }
    for(auto [weight, root]: g[0]) if(!calced[root]) {
        // DP[B + bases[root]] += DP[B]
        int A = bases[root];
        if(A == -1) continue;
        for(int i = 0; i < 374; i++) DP[dir][i] = DP[!dir][i];
        for(int i = 373; i >= 0; i--) {
            int B = i;
            int val = DP[!dir][i];
            B = trans(B, A, 1);
            if(B == -1) continue;
            add(DP[dir][B], val);
        }
        dir = !dir;
    }
    int ans = 0;
    for(int i = 0; i < 374; i++) add(ans, DP[!dir][i]);
    cout << ans << '\n';
}
