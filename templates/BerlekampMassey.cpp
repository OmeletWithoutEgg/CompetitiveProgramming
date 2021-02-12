template <typename T> vector<T> BerlekampMassey(vector<T> a) {
    auto scalarProduct = [](vector<T> v, T c) -> vector<T> {
        for (T &x: v) x *= c;
        return v;
    };
    vector<T> s, ls;
    int last = 0;
    for (size_t i = 0; i < a.size(); i++) {
        T error = a[i];
        for (size_t j = 0; j < s.size(); j++)
            error -= s[j] * a[i-j-1];
        if (error == 0) continue;
        if (s.empty()) {
            s.resize(i + 1);
            last = i;
            ls.emplace_back(1 / error);
            continue;
        }
        vector<T> fix = scalarProduct(ls, error);
        fix.insert(fix.begin(), i - last - 1, 0); // fill zeros
        if (fix.size() >= s.size()) {
            ls = scalarProduct(s, - 1 / error);
            ls.insert(ls.begin(), 1 / error);
            last = i;
        }
        if (s.size() < fix.size()) s.resize(fix.size());
        for (size_t j = 0; j < fix.size(); j++)
            s[j] += fix[j];
    }
    return s;
}
