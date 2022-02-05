#include <bits/stdc++.h>
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
#define pb emplace_back

using namespace std;
const int maxn = 100025;

#define TIME Timer __timer(__PRETTY_FUNCTION__)
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};

// must support:
// - T + T
// - T += F
// - F += F
// example: RMQ, range add
struct NullTag {
    NullTag& operator+=(NullTag& rhs) {
        return *this;
    }
};
struct Data {
    // nand
    int out[2];
    Data() {
        out[0] = 0;
        out[1] = -1;
    }
    Data(int x) {
        out[0] = ~0;
        out[1] = ~x;
    }
    friend Data operator+(const Data& lhs, const Data& rhs) {
        Data res;
        res.out[0] = (lhs.out[0] & rhs.out[1]) | (~lhs.out[0] & rhs.out[0]);
        res.out[1] = (lhs.out[1] & rhs.out[1]) | (~lhs.out[1] & rhs.out[0]);
        return res;
    }
    int calc(int x) {
        return (x & out[1]) | (~x & out[0]);
    }
    Data& operator+=(const NullTag& tag) {
        return *this;
    }
};
template <typename T>
class Segtree {
   private:
    vector<T> st;
    size_t sz;
    void pull(size_t p) {
        while (p >>= 1) {
            st[p] = st[p << 1] + st[p << 1 | 1];
        }
    }

   public:
    void edit(size_t p, T t) {
        st[p + sz] = t;
        pull(p + sz);
    }
    T query(size_t l, size_t r) {
        T resl, resr;
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) resl = resl + st[l++];
            if (r & 1) resr = st[--r] + resr;
        }
        return resl + resr;
    }
    Segtree(size_t n, T t = T())
        : sz(n), st(n * 2, t) {
        assert (n != 0);
        for (size_t i = n - 1; i > 0; i--)
            st[i] = st[i << 1] + st[i << 1 | 1];
    }
    template <typename Iter>
    Segtree(Iter L, Iter R)
        : sz(distance(L, R)),
          st(distance(L, R) * 2) {
        assert (sz != 0);
        for (size_t i = 0; i < sz; i++)
            st[i + sz] = *(L + i);
        for (size_t i = sz - 1; i > 0; i--)
            st[i] = st[i << 1] + st[i << 1 | 1];
    }
};
signed main() {
    TIME;
    ios_base::sync_with_stdio(0), cin.tie(0);
    int C;
    int n, q;
    cin >> n >> q >> C;
    const int MASK = (1 << C) - 1;
    vector<int> a(n);
    for (int &ai: a) cin >> ai;
    Segtree<Data> sgt(a.begin(), a.end());

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            cout << (sgt.query(l, r).calc(a[l-1]) & MASK) << '\n';
        } else {
            int p, x;
            cin >> p >> x;
            --p;
            a[p] = x;
            sgt.edit(p, x);
        }
    }
}
