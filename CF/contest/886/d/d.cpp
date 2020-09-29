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
template <typename ...T> void qqbx(const char *s, T ...args) {
    std::cerr << "\033[1;32m" << '(' << s << ')' << " = " << '(';
    constexpr int size = sizeof...(T);
    int cnt = size, dummy[size] = { (std::cerr << args << (--cnt ? ", " : ")\033[0m\n"), 0)... };
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
constexpr ll N = 525, INF = 1e18, MOD = 1000000007, K = 26, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + ((x<0 ^ m>0) && (x%m)); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

template <typename U, typename V> ostream & operator<<(ostream &O, pair<U,V> p) { return O << "(" << p.first << ", " << p.second << ")"; }
int match(const string &T, const string &P) {
    vector<int> fail(P.size());
    for(int i = 1, j = 0; i < P.size(); i++) {
        while(j && P[i] != P[j]) j = fail[j-1];
        if(P[i] == P[j]) ++j;
        fail[i] = j;
    }
    int res = 0;
    for(int i = 0, j = 0; i < T.size(); i++) {
        while(j && T[i] != P[j]) j = fail[j-1];
        if(T[i] == P[j]) ++j;
        if(j == P.size()) {
            ++res;
            j = fail[j-1];
        }
    }
    return res;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<string> v(n);
    for(auto &s: v) cin >> s;
    if(n > 500) return cout << "NO\n", 0;
    for(auto s: v) {
        if(s.size() > 26) return cout << "NO\n", 0;
        bool has[26] = {};
        for(char c: s) {
            if(has[c-'a']) return cout << "NO\n", 0;
            has[c-'a'] = true;
        }
    }
    vector<int> nxt(26, -1);
    vector<int> in(26), has(26), vis(26);
    for(string s: v) {
        for(int i = 1; i < s.size(); i++) {
            int a = s[i-1]-'a', b = s[i]-'a';
            if(nxt[a] != -1 && nxt[a] != b) return cout << "NO\n", 0;
            nxt[a] = b;
            ++in[b];
        }
        for(char c: s) has[c-'a'] = true;
    }
    vector<string> chain;
    for(int i = 0; i < 26; i++) {
        if(in[i] == 0 && has[i]) {
            string ans;
            for(int x = i; x != -1 && !vis[x]; x = nxt[x]) ans += char('a'+x), vis[x] = true;
            chain.pb(ans);
            debug(ans);
        }
    }
    sort(all(chain));
    string res;
    for(string s: chain) res += s;
    debug(res);
    if(res.empty()) return cout << "NO\n", 0;
    for(int i = 0, h = res.size(); i < h; i++) {
        for(int j = 1; i+j <= h; j++) {
            if(match(res, res.substr(i, j)) != 1) {
                return cout << "NO\n", 0;
            }
        }
    }
    for(string P: v) if(match(res, P) != 1) return cout << "NO\n", 0;
    cout << res << '\n';
}