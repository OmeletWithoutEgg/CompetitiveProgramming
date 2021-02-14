#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>

using namespace std;

template <typename T> T fastLinearRecurrence(vector<T> a, vector<T> s, int n) {
    if (n < a.size()) return a[n];
    if (s.empty()) return 0;
    auto mul = [&s](const vector<T> &a, const vector<T> &b) {
        vector<T> c(s.size() * 2);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++)
                c[i+j] += a[i] * b[j];
        for (size_t i = c.size()-1; i >= s.size(); i--)
            for (size_t j = 0; j < s.size(); j++)
                c[i-1-j] += c[i] * s[j];
        c.resize(s.size());
        return c;
    };
    vector<T> r = {1}, e = {0, 1};
    while (n) {
        if (n & 1)
            r = mul(r, e);
        e = mul(e, e);
        n >>= 1;
    }
    T sum = 0;
    for (size_t i = 0; i < r.size(); i++) sum += r[i] * a[i];
    return sum;
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    uint32_t a, b, x, y;
    while (cin >> n >> a >> b >> x >> y && n >= 0) {
        vector<uint32_t> init = {a, b}, rec = {y, x};
        cout << fastLinearRecurrence(init, rec, n) << '\n';
    }
}
