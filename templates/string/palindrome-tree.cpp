#include <bits/stdc++.h>

using namespace std;

const int K = 26, maxn = 100025;
struct PalindromeTree {
    struct node {
        int len;
        node *fail, *ch[K];
        int cnt;
        node() = default;
        node(int len, node* fail = nullptr) : len(len), fail(fail) {
            for (int i = 0; i < K; i++) ch[i] = nullptr;
        }
    };
    node pool[maxn], *ptr;
    node *root, *last, *zero;
    void build(const string& s) {
        ptr = pool;
        root = new (ptr++) node(-1);
        root->fail = root;
        last = zero = new (ptr++) node(0, root);
        int distinct_cnt = 0;
        vector<node*> nd(s.size());
        for (int i = 0; i < s.size(); i++) {
            int c = s[i] - 'a';
            const auto getFail = [&s, i](node* p) {
                while (i - p->len - 1 < 0 || s[i] != s[i - p->len - 1])
                    p = p->fail;
                return p;
            };
            last = getFail(last);
            if (last->ch[c] == nullptr) {
                node* cur = getFail(last->fail);
                last = last->ch[c] = new (ptr++)
                    node(last->len + 2, last == root ? zero : cur->ch[c]);
                ++distinct_cnt;
            } else
                last = last->ch[c];
            last->cnt += 1;
            nd[i] = last;
        }
        while (ptr != pool) {
            --ptr;
            ptr->fail->cnt += ptr->cnt;
        }
        for (int i = 0; i < s.size(); i++) {
            node* p = nd[i];
            // cerr << p->cnt << ' ' << s.substr(i - p->len
            // + 1, p->len) << endl;
        }
        // cout << distinct_cnt << '\n';
    }
} PT;

signed main() {
    string s;
    cin >> s;
    PT.build(s);
}
