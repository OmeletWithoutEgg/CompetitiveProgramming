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
// #define _GLIBCXX_DEBUG AC
#include <bits/extc++.h>
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
#pragma loop_opt(on)
#include <bits/extc++.h>
#include <bits/stdc++.h>
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)
#define mem(v,x) memset(v,x,sizeof v)
#define ff first
#define ss second
 
template <typename T, T MOD> class Modular {
public:
    constexpr Modular() : v() {}
    template <typename U> Modular(const U &u) { v = (0 <= u && u < MOD ? u : (u%MOD+MOD)%MOD); }
    template <typename U> explicit operator U() const { return U(v); }
    T operator()() { return v; }
#define REFOP(type, expr...) Modular &operator type (const Modular &rhs) { return expr, *this; }
    REFOP(+=, v += rhs.v - MOD, v += MOD & (v >> width)) ; REFOP(-=, v -= rhs.v, v += MOD & (v >> width))
    // fits for MOD^2 <= 9e18
    REFOP(*=, v = 1LL * v * rhs.v % MOD) ; REFOP(/=, *this *= inverse(rhs.v))
#define VALOP(op) friend Modular operator op (Modular a, const Modular &b) { return a op##= b; }
    VALOP(+) ; VALOP(-) ; VALOP(*) ; VALOP(/)
    Modular operator-() const { return 0 - *this; }
    friend bool operator == (const Modular &lhs, const Modular &rhs) { return lhs.v == rhs.v; }
    friend bool operator != (const Modular &lhs, const Modular &rhs) { return lhs.v != rhs.v; }
    friend std::istream & operator>>(std::istream &I, Modular &m) { T x; I >> x, m = x; return I; }
    friend std::ostream & operator<<(std::ostream &O, const Modular &m) { return O << m.v; }
private:
    constexpr static int width = sizeof(T) * 8 - 1;
    T v;
    static T inverse(T a) {
        // copy from tourist's template
        T u = 0, v = 1, m = MOD;
        while (a != 0) {
            T t = m / a;
            m -= t * a; std::swap(a, m);
            u -= t * v; std::swap(u, v);
        }
        assert(m == 1);
        return u;
    }
};

using namespace std;
using namespace __gnu_pbds;
typedef int64_t ll;
typedef long double ld;
typedef pair<ll,ll> pll;
typedef pair<ld,ld> pld;
template <typename T> using max_heap = std::priority_queue<T,vector<T>,less<T> >;
template <typename T> using min_heap = std::priority_queue<T,vector<T>,greater<T> >;
template <typename T> using rbt = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template <typename V, typename T> int get_pos(const V &v, T x) { return lower_bound(all(v),x) - begin(v); }
template <typename V> void sort_uni(V &v) { sort(all(v)), v.erase(unique(all(v)),end(v)); }
template <typename T> bool chmin(T &x, const T &v) { return v < x ? (x=v, true) : false; }
template <typename T> bool chmax(T &x, const T &v) { return x < v ? (x=v, true) : false; }
constexpr inline ll cdiv(ll x, ll m) { return x/m + (x%m ? (x<0) ^ (m>0) : 0); } // ceiling divide
constexpr inline ll modpow(ll e,ll p,ll m) { ll r=1; for(e%=m;p;p>>=1,e=e*e%m) if(p&1) r=r*e%m; return r; }

constexpr ld PI = acos(-1), eps = 1e-7;
constexpr ll N = 500025, INF = 1e18, MOD = 998244353, K = 14699, inf = 1e9;
using Mint = Modular<int, MOD>;
Mint modpow(Mint e, uint64_t p) { Mint r = 1; while(p) (p&1) && (r *= e), e *= e, p >>= 1; return r; } // 0^0 = 1

struct Linear {
    Mint a, b;
    Linear() : a(1), b(0) {}
    Linear(Mint a, Mint b) : a(a), b(b) {}
    Linear & operator+=(const Linear &rhs) {
        // rhs.a(ax+b)+rhs.b;
        return a *= rhs.a, b = rhs.a * b + rhs.b, *this;
    }
    friend Linear operator+(Linear lhs, const Linear &rhs) {
        return lhs += rhs;
    }
    Mint operator()(Mint x, size_t len) {
        return a * x + b * len;
    }
    friend ostream &operator<<(ostream &O, Linear &L) {
        return O << "y = " << L.a << "x+" << L.b;
    }
};
struct Segtree {
    vector<Mint> sum;
    vector<Linear> lz;
    size_t n;
    Segtree(size_t _n) : n(_n), sum(_n*2), lz(_n) {}
    void upd(size_t p, Linear f, size_t len) {
        sum[p] = f(sum[p], len);
        if(p < n) lz[p] += f;
    }
    void pull(size_t p) {
        for(size_t len = 2; p>1; p>>=1, len<<=1)
            sum[p>>1] = lz[p>>1](sum[p]+sum[p^1], len);
    }
    void push(size_t p) {
        for(int8_t h = __lg(n); h >= 0; h--) {
            size_t i = p>>h;
            upd(i, lz[i>>1], 1<<h);
            upd(i^1, lz[i>>1], 1<<h);
            lz[i>>1] = Linear();
        }
    }
    void add(size_t l, size_t r, Linear f) {
        debug(l, r, f.a, f.b);
        /* for(size_t i = l; i < r; i++)
            v[i] = f(v[i], 1);
        debug(v);
        return; */
        size_t L = l, R = r, len = 1;
        push(l+n), push(r-1+n);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1, len<<=1) {
            if(l&1) upd(l++, f, len);
            if(r&1) upd(--r, f, len);
        }
        pull(L+n), pull(R-1+n);
    }
    Mint query(size_t l, size_t r) {
        Mint res = 0;
        /* for(size_t i = l; i < r; i++) res += v[i];
        return res; */
        push(l+n), push(r-1+n);
        for(l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if(l&1) res += sum[l++];
            if(r&1) res += sum[--r];
        }
        return res;
    }
};
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, q;
    cin >> n >> q;
    Segtree sgt(n);
    auto add = [&sgt](set<pair<int,int>> &st, pair<int,int> I) {
        if(st.empty()) {
            sgt.add(I.first, I.second, {1, 1});
            st.insert(I);
            return;
        }
        auto it = st.upper_bound({I.first, inf});
        int L = I.first, R = I.second;
        int last = I.first;
        if(it != st.begin()) {
            auto jt = prev(it);
            debug(*jt, I);
            if(jt->second >= I.first) {
                sgt.add(I.first, min(I.second, jt->second), {2, 0});
                L = jt->first;
                R = max(R, jt->second);
                last = jt->second;
                st.erase(jt);
            }
        }
        while(it != st.end() && it->first <= I.second) {
            debug(*it);
            if(last < it->first)
                sgt.add(last, it->first, {1, 1});
            R = max(R, it->second);
            if(it->second < I.second) {
                last = it->second;
            } else {
                last = I.second;
            }
            debug(it->first, last);
            sgt.add(it->first, last, {2, 0});
            st.erase(it++);
        }
        if(last < I.second)
            sgt.add(last, I.second, {1, 1});
        debug(L, R);
        st.insert({L, R});
    };
    vector<set<pair<int,int>>> segs(n+1);
    while(q--) {
        int t;
        cin >> t;
        if(t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            debug(segs[x]);
            add(segs[x], {l, r});
            debug(segs[x], l, r);
        } else if(t == 2) {
            int l, r;
            cin >> l >> r;
            --l;
            cout << sgt.query(l, r) << '\n';
        }
    }
}
