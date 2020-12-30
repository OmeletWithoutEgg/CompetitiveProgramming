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
constexpr ll N = 1 << 10, INF = 1e18, MOD = 1000000007, K = 26, inf = 1e9;
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m=MOD) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

int KMP(const string &T, const string &P) {
    vector<int> F(P.size());
    for(size_t i = 1, j = 0; i < P.size(); i++) {
        while(j && P[i] != P[j]) j = F[j-1];
        if(P[i] == P[j]) ++j;
        F[i] = j;
    }
    int ans = 0;
    for(size_t i = 0, j = 0; i < T.size(); i++) {
        while(j && T[i] != P[j]) j = F[j-1];
        if(T[i] == P[j]) ++j;
        if(j == P.size()) {
            ++ans;
            j = F[j-1];
        }
    }
    return ans;
}

struct HASH {
    const int MOD = 998244353;
    vector<int> h, pw;
    HASH(string s) : h(s.size() + 1), pw(s.size() + 1) {
        for(int i = 0; i < s.size(); i++) h[i+1] = (h[i] * 147LL + s[i]) % MOD;
        pw[0] = 1;
        for(int i = 1; i <= s.size(); i++) pw[i] = pw[i-1] * 147LL % MOD;
        safe;
    }
    int operator()(int l, int len) {
        return (h[l+len] - 1LL * h[l] * pw[len] % MOD + MOD) % MOD;
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    string s0, t;
    cin >> n >> q >> s0 >> t;
    vector<array<ll,26>> cnt(n+1);
    for(int i = 0; i < n; i++) {
        int c = t[i] - 'a';
        for(int j = 0; j < 26; j++) {
            cnt[i+1][j] = cnt[i][j];
        }
        cnt[i+1][c] = (cnt[i+1][c] + modpow(modpow(2, MOD-2), i+1)) % MOD;
    }
    for(int i = 0; i < q; i++) {
        int k;
        string w;
        cin >> k >> w;
        string s = s0;
        int L = 0;
        while(L < k && s.size() < w.size())
            s = s + t[L++] + s;
        if(w.size() > s.size()) {
            cout << 0 << '\n';
            continue;
        }
        HASH hashs(s), hashw(w);
        // occurence in sL * 2^{k-L}
        // + occurence not properly in sL -> suffix(sL, i) + t[j] + prefix(sL, |w|-i) where 0 <= i <= n, L < j < n
        // count of t[j]: 2^{k-j-1} (L <= j < k)
        int sum = 0;
        // assert(w.size() <= s.size());
        for(int j = 0; j < w.size(); j++) {
            int c = w[j] - 'a';
            if(hashs(s.size() - j, j) == hashw(0, j) && hashs(0, w.size() - j - 1) == hashw(j+1, w.size() - j - 1)) {
                debug(k, L, cnt[k]);
                sum = (sum + cnt[k][c] - cnt[L][c] + MOD) % MOD;
            }
        }
        debug(sum, s, w, KMP(s, w));
        sum = (sum * modpow(2, k) + KMP(s, w) * modpow(2, k - L)) % MOD;
        cout << sum << '\n';
    }
}
