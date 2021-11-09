// must support:
// - T + T
// - T += F
// - F += F
// example: RMQ, range add
struct LazyTag {
    int add;
    LazyTag() : add(0) {}
    LazyTag& operator&(LazyTag& rhs) {
        add += rhs.add;
        return *this;
    }
};
struct Data {
    int mx;
    Data(int x = 0) : mx(x) {}
    friend Data operator+(const Data& lhs, const Data& rhs) {
        Data res;
        res.mx = max(lhs.mx, rhs.mx);
        return res;
    }
    Data& operator+=(const LazyTag& tag) {
        mx += tag.add;
        return *this;
    }
};
template <typename T, typename F>
class Segtree {
   private:
    vector<F> lz;
    vector<T> st;
    size_t sz;
    void upd(size_t p, F f) {
        st[p] += f;
        if (p < sz) lz[p] += f;
    }
    void pull(size_t p) {
        while (p >>= 1) {
            st[p] = st[p << 1] + st[p << 1 | 1];
            st[p] += lz[p];
        }
    }
    void push(size_t p) {
        for (int h = __lg(sz); h >= 0; h--) {
            size_t i = p >> h;
            upd(i, lz[i >> 1]);
            upd(i ^ 1, lz[i >> 1]);
            lz[i >> 1] = 0;
        }
    }

   public:
    void apply(size_t l, size_t r, F f) {
        size_t tl = l, tr = r;
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) upd(l++, f);
            if (r & 1) upd(--r, f);
        }
        pull(tl + sz), pull(tr - 1 + sz);
    }
    T query(size_t l, size_t r) {
        T res;
        push(l + sz), push(r - 1 + sz);
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) res = res + st[l++];
            if (r & 1) res = res + st[--r];
        }
        return res;
    }
    Segtree(size_t n, T t = T(), F f = F()) : sz(n), st(n * 2, t), lz(n, f) {
        for (size_t i = n - 1; i > 0; i--) st[i] = st[i << 1] + st[i << 1 | 1];
    }
    template <typename Iter>
    Segtree(Iter L, Iter R)
        : sz(distance(L, R)), st(L, R), lz(distance(L, R), F{}) {}
};
