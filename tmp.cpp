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
 
#include <bits/extc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
#define TAK(args...) std::ostream& operator<<(std::ostream &O, args)
#define NIE(STL, BEG, END, OUT) template <typename ...T> TAK(std::STL<T...> v) \
    { O << BEG; int f=0; for(auto e: v) O << (f++ ? ", " : "") << OUT; return O << END; }
NIE(deque, "[", "]", e) ; NIE(vector, "[", "]", e)
NIE(set, "{", "}", e) ; NIE(multiset, "{", "}", e) ; NIE(unordered_set, "{", "}", e)
NIE(map , "{", "}", e.first << ":" << e.second)
NIE(unordered_map , "{", "}", e.first << ":" << e.second)
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
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
 

using namespace std;

const int K = 11;

vector<int> match(string T, const string &P) {
    string S = P + '$' + T;
    vector<int> Z(S.size());
    for (int i = 1, j = 0, r = 0; i < S.size(); i++) {
        Z[i] = max(0, min(Z[i-j], r-i));
        while(i+Z[i] < S.size() && S[Z[i]] == S[i+Z[i]]) ++Z[i];
        if (i+Z[i] > r) {
            j = i;
            r = i+Z[i];
        }
    }
    return vector<int>(Z.begin() + P.size() + 1, Z.end());
}

using ll = long long;
using magic = __int128;
const int maxn = 50025, E = 880301;
const ll MOD = 444366734524183;
ll pw[maxn];

struct RollingHash {
    vector<ll> h;
    RollingHash(string s) : h(s.size() + 1) {
        for (int i = 0; i < s.size(); i++) h[i+1] = (magic(1) * h[i] * E + s[i]) % MOD;
    }
    ll substr(int p, int sz) const {
        return (h[p+sz] - magic(1) * h[p] * pw[sz] % MOD + MOD) % MOD;
    }
};
__gnu_pbds::gp_hash_table<ll, int> ans, cnt;
signed main() {
    pw[0] = 1;
    for (int i = 1; i < maxn; i++) pw[i] = magic(1) * pw[i-1] * E % MOD;
    ios_base::sync_with_stdio(0), cin.tie(0);
    string S, T;
    cin >> S >> T;
    int n = S.size(), q;
    RollingHash hT(T), hS(S);
    for (int i = 0; i < n; i++) {
        for (int L = 1; L <= K && i+L <= n; L++) {
            ++cnt[hT.substr(i, L)];
        }
    }
    for(int i = 0; i+1 < n; i++) {
        for (int L = 1; L <= K && i+L <= n; L++) {
            if (--cnt[hT.substr(i, L)] == 0)
                cnt.erase(hT.substr(i, L));
        }
        for (int L = 1; L <= K && i+1-L >= 0; L++) {
            ++cnt[hS.substr(i+1-L, L)];
        }
        // string C = S.substr(0, i+1) + T.substr(i+1);
        for (int L1 = 1; L1 <= K && i + 1 - L1 >= 0; L1++) {
            for (int L2 = 1; L1 + L2 <= K && i+1+L2 <= n; L2++) {
                ll C = (magic(1) * hS.substr(i+1-L1, L1) * pw[L2] + hT.substr(i+1, L2)) % MOD;
                if (cnt.find(C) == cnt.end())
                    ans[C] += 1;
            }
        }
    }

    reverse(all(T));
    cin >> q;
    while(q--) {
        string P;
        cin >> P;
        if (P.size() <= K) {
            cout << ans[RollingHash(P).substr(0, P.size())] << '\n';
            continue;
        }
        auto pre = match(S, P);
        reverse(all(P));
        auto suf = match(T, P);
        reverse(all(suf));
        int L = 0, R = n;
        for (int i = 0; i < S.size(); i++) if (pre[i] == P.size()) {
            R = i + P.size() - 1;
            break;
        }
        for (int i = T.size()-1; i >= 0; i--) if (suf[i] == P.size()) {
            L = i - P.size() + 1;
            break;
        }
        debug(L, R);
        debug(pre, suf);
        int ans = 0;
        for (int i = 0; i + P.size() <= T.size(); i++) {
            int j = i + P.size() - 1;
            int r = i + pre[i];
            int l = j - suf[j];
            // [l, r] can cut
            if (l >= r) continue;
            debug(l, r, i, j);
            ans += max(0, min(R, r) - max(L, l));
        }
        cout << ans << '\n';
    }
}
