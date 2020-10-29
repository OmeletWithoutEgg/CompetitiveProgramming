//   __________________
//  | ________________ |
//  ||          ____  ||
//  ||   /\    |      ||
//  ||  /__\   |      ||
//  || /    \  |____  ||
//  ||________________||
//  |__________________|
//  \###################\
//   \###################\
//    \        ____       \
//     \_______\___\_______\
// An AC a day keeps the doctor away.
 
#ifdef local
#include <bits/extc++.h>
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
using ost = std::ostream;
#define DESTL(STL, BEG, END, OUT) \
    template <typename ...T> ost& operator<<(ost &O, std::STL<T...> v) { int f=0; for(auto x: v) O << (f++ ? ", " : BEG) << OUT; return O << END; }
DESTL(deque, "[", "]", x); DESTL(vector, "[", "]", x);
DESTL(set, "{", "}", x); DESTL(multiset, "{", "}", x); DESTL(unordered_set, "{", "}", x);
DESTL(map , "{", "}", x.first << ":" << x.second); DESTL(unordered_map , "{", "}", x.first << ":" << x.second);
template <typename U, typename V> ost& operator<<(ost &O, std::pair<U,V> p) { return O << '(' << p.first << ',' << p.second << ')'; }
template <typename T, size_t N> ost& operator<<(ost &O, std::array<T,N> a) { int f=0; for(T x: a) O << (f++ ? ", " : "[") << x; return O << "]"; }
template <typename T, size_t ...I> ost& prtuple(ost &O, T t, std::index_sequence<I...>) { return (..., (O << (I ? ", " : "(") << std::get<I>(t))), O << ")"; }
template <typename ...T> ost& operator<<(ost &O, std::tuple<T...> t) { return prtuple(O, t, std::make_index_sequence<sizeof...(T)>()); }
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
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
constexpr ll N = 300025, INF = 1e18, MOD = 1000000007, K = 26, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct RMQ {
    int mx[N<<1], n;
    void edit(int p, int x) {
        for(mx[p+=n] = x; p>1; p>>=1)
            mx[p>>1] = max(mx[p], mx[p^1]);
    }
    int query(int l, int r) {
        int res = 0;
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res = max(res, mx[l++]);
            if(r&1) res = max(res, mx[--r]);
        }
        return res;
    }
} rmq;
struct TR {
    int pa[N], sz[N], mxs[N], vis[N];
    int top[N], tot;
    vector<int> g[N];
    void addEdge(int a, int b) {
        g[a].pb(b);
    }
    void edit(int p, int x) {
        rmq.edit(vis[p], x);
    }
    void getSz(int i) {
        sz[i] = 1;
        mxs[i] = -1;
        for(int j: g[i]) {
            pa[j] = i;
            getSz(j);
            sz[i] += sz[j];
            if(mxs[i] == -1 || sz[mxs[i]] < sz[j]) mxs[i] = j;
        }
    }
    void dfs(int i, int t) {
        top[i] = t;
        vis[i] = tot++;
        if(mxs[i] != -1) dfs(mxs[i], t);
        for(int j: g[i]) {
            if(j != mxs[i]) {
                dfs(j, j);
            }
        }
    }
    int query(int p) {
        int res = 0;
        while(p) {
            int t = top[p];
            res = max(res, rmq.query(vis[t], vis[p]+1));
            p = pa[t];
        }
        return res;
    }
} tr;
struct AhoCorasick {
    int ch[N][K], fail[N];
    int tot;
    int ins(const string &s) {
        int i = 0;
        for(char c: s) {
            c -= 'a';
            if(!ch[i][c])
                ch[i][c] = ++tot;
            i = ch[i][c];
        }
        return i;
    }
    void buildFail() {
        queue<int> q;
        for(int c = 0; c < K; c++) if(ch[0][c]) q.push(ch[0][c]);
        while(!q.empty()) {
            int i = q.front(); q.pop();
            tr.addEdge(fail[i], i);
            for(int c = 0; c < K; c++) {
                if(ch[i][c]) {
                    fail[ ch[i][c] ] = ch[ fail[i] ][c];
                    q.push(ch[i][c]);
                } else {
                    ch[i][c] = ch[fail[i]][c];
                }
            }
        }
    }
    int run(const string &s) {
        int i = 0, ans = 0;
        for(char c: s) {
            c -= 'a';
            i = ch[i][c];
            ans = max(ans, tr.query(i));
        }
        return ans;
    }
} AC;
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> ed(n);
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        ed[i] = AC.ins(s);
    }
    AC.buildFail();
    tr.getSz(0);
    tr.dfs(0, 0);
    rmq.n = tr.tot;
    vector<multiset<int, greater<int>>> ms(AC.tot+1);
    vector<int> val(n);
    for(int i = 0; i < n; i++) tr.edit(ed[i], 1), ms[ed[i]].insert(1), val[i] = 1;
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int i, x;
            cin >> i >> x;
            --i, ++x;
            ms[ed[i]].erase(ms[ed[i]].find(val[i]));
            val[i] = x;
            ms[ed[i]].insert(val[i]);
            tr.edit(ed[i], *ms[ed[i]].begin());
        } else {
            string s;
            cin >> s;
            int ans = AC.run(s);
            --ans;
            cout << ans << '\n';
        }
    }
}
