namespace linear_recurrence {
template <typename T>
vector<T> BerlekampMassey(vector<T> a) {
    auto scalarProduct = [](vector<T> v, T c) {
        for (T& x : v) x *= c;
        return v;
    };
    vector<T> s, best;
    int bestPos = -1;
    for (size_t i = 0; i < a.size(); i++) {
        T error = a[i];
        for (size_t j = 0; j < s.size(); j++) error -= s[j] * a[i - 1 - j];
        if (error == 0) continue;
        vector<T> fix = scalarProduct(best, error);
        fix.insert(fix.begin(), i - bestPos, 0);
        if (fix.size() >= s.size()) {
            best = scalarProduct(s, -1 / error);
            best.insert(best.begin(), 1 / error);
            bestPos = i + 1;
            s.resize(fix.size());
        }
        for (size_t j = 0; j < fix.size(); j++) s[j] += fix[j];
    }
    return s;
}
template <typename T>
T deduce(vector<T> a, int n) {
    vector<T> s = BerlekampMassey(a);
    if (s.empty()) return 0;
    debug(s);
    // a[i] = \sum s[j] * a[i-j-1]
    vector<T> r = {1};     // 1
    vector<T> e = {0, 1};  // x;
    auto mul = [&s](vector<T> a, vector<T> b) {
        // return a * b % (x^m - s)
        vector<T> c(a.size() + b.size() - 1);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++) c[i + j] += a[i] * b[j];
        for (size_t i = c.size() - 1; i >= s.size(); i--)
            for (size_t j = 0; j < s.size(); j++) c[i - j - 1] += c[i] * s[j];
        c.resize(s.size());
        return c;
    };
    while (n) {
        if (n & 1) r = mul(r, e);
        e = mul(e, e);
        n >>= 1;
    }
    T sum = 0;
    for (size_t j = 0; j < r.size(); j++) sum += r[j] * a[j];
    return sum;
}
}  // namespace linear_recurrence
