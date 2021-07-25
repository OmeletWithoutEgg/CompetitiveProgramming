#include <bits/stdc++.h>
using namespace std;

class Hash {
    private:
        static constexpr int P = 127, Q = 1051762951;
        static int add(int a, int b) {
            a += b;
            if (a >= Q) a -= Q;
            return a;
        }
        static int sub(int a, int b) {
            a -= b;
            if (a < 0) a += Q;
            return a;
        }
        static int mul(int64_t a, int64_t b) {
            return static_cast<int>(a * b % Q);
        } 
        vector<int> h, p;
    public:
        void init(const vector<int> &s) {
            h.assign(s.size() + 1, 0);
            p.resize(s.size() + 1);
            for (size_t i = 0; i < s.size(); ++i) {
                h[i + 1] = add(mul(h[i], P), s[i]);
            }
            generate(p.begin(), p.end(), [x=1,y=1,this] () mutable {
                y = x;
                x = mul(x, P);
                return y;
            });
        }
        size_t size() const {
            return h.size() - 1;
        }
        int query(int l, int r) const {
            return sub(h[r], mul(h[l], p[r - l]));
        }
} hasher;


const int maxn = 1000025;
int dq[maxn * 2];
int note(string s) {
    static const char * notes[] = {"do","re","mi","fa","sol","la","si"};
    for (int i = 0; i < 7; i++) if (notes[i] == s) return i;
    return -1;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int l = maxn, r = l;
    vector<pair<int,int>> range(n);
    for (int i = 0; i < n; i++) {
        char c;
        string nt;
        cin >> c >> nt;
        int x = note(nt);
        if (c == 'p') {
            dq[--l] = x;
        } else if (c == 'a') {
            dq[r++] = x;
        }
        range[i] = { l, r };
    }
    for (int i = 0; i < n; i++)
        range[i].first -= l, range[i].second -= l;


    vector<int> seq(dq + l, dq + r);
    hasher.init(seq);

    /*
    for (auto [l, r] : range)
        cerr << l << ',' << r << endl;
    for (int i = 0; i < n; i++)
        cerr << seq[i] << ' ';
    cerr << endl;
    */

    auto valid = [](pair<int,int> R, int step) {
        auto [l, r] = R;
        int len = r - l;
        for (int i = step; i < len; i += step) {
            if (i + step > len) {
                int s = len - i;
                if (hasher.query(l, l+s) != hasher.query(l+i, l+i+s))
                    return false;
            } else {
                if (hasher.query(l, l+step) != hasher.query(l+i, l+i+step))
                    return false;
            }
        }
        return true;
    };
    auto bin_search = [n, &valid, &range](int k) {
        int l = 0, r = n;
        // [l, r) is valid
        while (r - l > 1) {
            int m = l + (r - l) / 2;
            if (valid(range[m], k)) {
                l = m;
            } else {
                r = m;
            }
        }
        return r;
    };

    // cerr << "QQ " << valid(range[1], 1) << endl;
    vector<int> ans(n + 1);
    for (int k = 1; k <= n; k++) {
        int r = bin_search(k);
        // cerr << r << endl;
        ans[k-1] += 1;
        ans[r] -= 1;
    }
    for (int i = 1; i <= n; i++)
        ans[i] += ans[i-1];
    for (int i = 0; i < n; i++)
        cout << ans[i] << '\n';
    return 0;
}
