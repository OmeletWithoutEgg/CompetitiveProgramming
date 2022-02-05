#include "messy.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
#define pary(x...) danb(#x, x)
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ..., (std::cerr << a << (--cnt ? ", " : ")\e[0m\n")));
}
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#define safe ((void)0)
#endif // local
#define all(v) begin(v),end(v)


using namespace std;
const int maxn = 128;

int n;
int p[maxn];
int write_cnt, read_cnt;
void dc_add(int l, int r, string s) {
    if (l+1 == r) return;
    int m = l+(r-l)/2;
    for (int i = m; i < r; i++) {
        string tmp = s;
        tmp[i] = '1';
        add_element(tmp);
        ++write_cnt;
    }
    string L = s, R = s;
    for (int i = m; i < r; i++) L[i] = '1';
    for (int i = l; i < m; i++) R[i] = '1';
    dc_add(l, m, L);
    dc_add(m, r, R);
}
void dc_check(int l, int r, string s, vector<int> candidate) {
    assert (r - l == candidate.size());
    if (l+1 == r) {
        p[l] = candidate[0];
        return;
    }
    int m = l+(r-l)/2;
    vector<int> lson, rson;
    for (int i: candidate) {
        string tmp = s;
        tmp[i] = '1';
        ++read_cnt;
        if (check_element(tmp)) {
            rson.push_back(i);
        } else {
            lson.push_back(i);
        }
    }
    string L = s, R = s;
    for (int i: rson) L[i] = '1';
    for (int i: lson) R[i] = '1';
    dc_check(l, m, L, lson);
    dc_check(m, r, R, rson);
}
vector<int> restore_permutation(int _n, int w, int r) {
    n = _n;
    string init(n, '0');
    dc_add(0, n, init);
    compile_set();
    vector<int> id(n);
    iota(all(id), 0);
    dc_check(0, n, init, id);
    debug(write_cnt, read_cnt, w, r);
    vector<int> ans(n);
    for (int i = 0; i < n; i++)
        ans[p[i]] = i;
    return ans;
}
