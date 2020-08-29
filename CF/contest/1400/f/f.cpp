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
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
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
constexpr ll N = 15025, INF = 1e18, MOD = 1000000007, K = 10, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

struct AhoCorasick {
    int ch[N][K], fail[N], isTail[N];
    int tot;
    void ins(array<int,20> &v, int s) {
        int now = 0;
        for(int i = 0; i < s; i++) {
            int c = v[i] - 1;
            if(!ch[now][c])
                ch[now][c] = ++tot;
            now = ch[now][c];
        }
        isTail[now] = 1;
    }
    void buildFail() {
        queue<int> q;
        for(int c = 0; c < K; c++) if(ch[0][c]) q.push(ch[0][c]);
        while(!q.empty()) {
            int i = q.front(); q.pop();
            int f = fail[i];
            isTail[i] |= isTail[f];
            for(int c = 0; c < K; c++) {
                if(ch[i][c]) {
                    fail[ch[i][c]] = ch[f][c];
                    q.push(ch[i][c]);
                } else {
                    ch[i][c] = ch[f][c];
                }
            }
        }
    }
    void dbg(int i=0, string s="") {
        cout<<i<<'\t'<<s<<'\n';
        for(int c=0;c<K;c++) if(ch[i][c]) dbg(ch[i][c], s+char('1'+c));
    }
    int goDp(string &s) {
        /* dbg(0); */
        vector<int> dp(tot+1, inf);
        dp[0] = 0;
        for(char c: s) {
            c -= '1';
            vector<int> DP(tot+1, inf);
            for(int i = 0; i <= tot; i++) {
                int j = ch[i][c];
                if(isTail[j]) continue;
                DP[j] = min(DP[j], dp[i]);
            }
            for(int i = 0; i <= tot; i++)
                dp[i] = min(dp[i]+1, DP[i]);
        }
        return *min_element(dp.begin(), dp.end());
    }
} AC;
void dfs(int x, int sum = 0) {
    static array<int,20> s;
    static int p = 0;
    if(sum > x) return;
    if(sum == x) {
        /* for(int i = 0; i < p; i++) cout<<s[i]<<' '; */
        /* cout<<'\n'; */
        AC.ins(s, p);
        return;
    }
    for(int i = 1; i <= 9; i++) {
        s[p++] = i;
        bool ok = 1;
        for(int j = p-1, now = 0; j >= 0; j--) {
            now += s[j];
            if(now!=x && x%now == 0) ok = 0;
        }
        if(ok) dfs(x, sum+i);
        --p;
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string S;
    int x;
    cin >> S >> x;
    dfs(x);
    AC.buildFail();
    cout << AC.goDp(S) << '\n';
}
