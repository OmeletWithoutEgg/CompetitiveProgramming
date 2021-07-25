#include <bits/stdc++.h>

using namespace std;
const int maxn = 400025, sigma = 128;

namespace SAIS {
bool t[maxn * 2];
int _s[maxn * 2], sa[maxn * 2], c[maxn * 2], x[maxn], p[maxn], q[maxn * 2];    
// sa[i]: sa[i]-th suffix is the i-th lexigraphically smallest suffix.
// hi[i]: longest common prefix of suffix sa[i] and suffix sa[i - 1].
void pre(int *sa, int *c, int n, int z) {
    memset(sa, 0, sizeof(int) * n);
    memcpy(x, c, sizeof(int) * z);
}
void induce(int *sa, int *c, int *s, bool *t, int n, int z) {
    memcpy(x + 1, c, sizeof(int) * (z - 1));
    for (int i = 0; i < n; ++i) if (sa[i] && !t[sa[i] - 1]) sa[x[s[sa[i] - 1]]++] = sa[i] - 1;
    memcpy(x, c, sizeof(int) * z);
    for (int i = n - 1; i >= 0; --i) if (sa[i] && t[sa[i] - 1]) sa[--x[s[sa[i] - 1]]] = sa[i] - 1;
}
void sais(int *s, int *sa, int *p, int *q, bool *t, int *c, int n, int z) {
    bool uniq = t[n - 1] = true;
    int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n, last = -1;
    memset(c, 0, sizeof(int) * z);
    for (int i = 0; i < n; ++i) uniq &= ++c[s[i]] < 2;
    for (int i = 0; i < z - 1; ++i) c[i + 1] += c[i];
    if (uniq) {
        for (int i = 0; i < n; ++i) sa[--c[s[i]]] = i;
        return;
    }
    for (int i = n - 2; i >= 0; --i) t[i] = (s[i] == s[i + 1] ? t[i + 1] : s[i] < s[i + 1]);
    pre(sa, c, n, z);
    for (int i = 1; i <= n - 1; ++i) if (t[i] && !t[i - 1]) sa[--x[s[i]]] = p[q[i] = nn++] = i;
    induce(sa, c, s, t, n, z);
    for (int i = 0; i < n; ++i) if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
        bool neq = last < 0 || memcmp(s + sa[i], s + last, (p[q[sa[i]] + 1] - sa[i]) * sizeof(int));
        ns[q[last = sa[i]]] = nmxz += neq;
    }
    sais(ns, nsa, p + nn, q + n, t + n, c + z, nn, nmxz + 1);
    pre(sa, c, n, z);
    for (int i = nn - 1; i >= 0; --i) sa[--x[s[p[nsa[i]]]]] = p[nsa[i]];
    induce(sa, c, s, t, n, z);
}
void build(const string &s) {
    for (int i = 0; i < (int)s.size(); ++i) _s[i] = s[i];
    _s[(int)s.size()] = 0; // s shouldn't contain 0
    sais(_s, sa, p, q, t, c, (int)s.size() + 1, 256);
    for (int i = 0; i < (int)s.size(); ++i) sa[i] = sa[i + 1];
}
}
namespace SuffixArray {
    int n;
    int *sa;
    int rk[maxn], H[maxn];
    bool has[maxn];
    void build(const string &S) {
        SAIS::build(S);
        sa = SAIS::sa;
        n = S.size();
        for (int i = 0; i < n; i++) rk[sa[i]] = i;
        for(int i = 0, h = 0; i < n; i++) {
            if(rk[i] == n-1) continue;
            int j = sa[rk[i]+1];
            while(i+h < n && j+h < n && S[i+h] == S[j+h]) ++h;
            H[rk[i]] = h;
            if(h > 0)
                --h;
        }
    }
    string solve(const string &S, int k, const vector<int> & block) {
        build(S);
        deque<pair<int,int>> dq;
        for(int i = 0, j = 0; i < n; i++) {
            while(has[block[sa[i]]] || has[k]) {
                has[block[sa[j++]]] = false;
                if(dq.size() && dq.front().second < j) dq.pop_front();
            }
            has[block[sa[i]]] = true;
            if(i-j+1 == k && !has[k]) {
                int LCP = dq.size() ? dq.front().first : n - sa[j]; // lcp [j .. i] == min H [j .. i)
                if((j == 0 || H[j-1] < LCP) && (i == n-1 || H[i] < LCP)) {
                    return S.substr(sa[j], LCP);
                }
            }
            while(dq.size() && dq.back().first >= H[i]) dq.pop_back();
            dq.emplace_back(H[i], i);
        }
        return "7122";
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n, tot = 0;
    cin >> n;
    if (n == 1) {
        string s;
        cin >> s;
        return cout << s << '\n', 0;
    }
    vector<int> block;
    block.reserve(400000);
    string T;
    for(int i = 0; i < n; i++) {
        string s;
        cin >> s;
        T += s;
        block.resize(T.size(), i);
        if(i != n-1) T += '$', block.push_back(n);
    }
    cout << SuffixArray::solve(T, n, block) << '\n';
}
