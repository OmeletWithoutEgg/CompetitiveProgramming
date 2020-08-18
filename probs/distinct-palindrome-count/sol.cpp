#include <bits/stdc++.h>

using namespace std;

const int K = 26;
struct PalindromeTree {
    struct node {
        int len;
        node *fail, *ch[K];
        node(int len, node *fail = nullptr) : len(len), fail(fail) { for(int i = 0; i < K; i++) ch[i] = nullptr; }
    } *root, *last, *zero;
    void calc(const string &s) {
        root = new node(-1);
        zero = last = new node(0, root);
        root->fail = root;
        int cnt = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = s[i]-'a';
            while(s[i] != s[i-last->len-1]) last = last->fail;
            if(last->ch[c] == nullptr) {
                node *cur = last->fail;
                while(s[i] != s[i-cur->len-1]) cur = cur->fail;
                last = last->ch[c] = new node(last->len+2, last==root ? zero : cur->ch[c]);
                // cout << s.substr(i-last->len+1, last->len) << '\n';
                // cout << last->len << '\n';
                ++cnt;
            } else last = last->ch[c];
        }
        cout << cnt << '\n';
        // cerr << s.size() << '\t' << cnt << '\n';
    }
} PT;

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    string s;
    cin >> s;
    PT.calc(s);
}

