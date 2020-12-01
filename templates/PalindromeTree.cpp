#include <bits/stdc++.h>

using namespace std;

const int K = 26;
struct PalindromeTree {
    struct node {
        int len;
        node *fail, *ch[K];
        node(int len, node *fail = nullptr) : len(len), fail(fail) { for(int i = 0; i < K; i++) ch[i] = nullptr; }
    } *root, *last, *zero;
    void init(const string &s) {
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
                cout << s.substr(i-last->len+1, last->len) << '\n';
                // cout << last->len << '\n';
                ++cnt;
            } else last = last->ch[c];
        }
        cout << cnt << '\n';
    }
} PT;

/*bool pal(string &&s) {
    for(int i = 0; i < s.size(); i++) if(s[i] != s[s.size()-1-i]) return false;
    return true;
}*/

signed main() {
    string s; cin >> s;
    /*unordered_set<string> se;
    for(int i = 0; i < s.size(); i++) for(int j = 1; i+j <= s.size(); j++) if(pal(s.substr(i,j))) se.insert(s.substr(i,j));
    cout << se.size() << '\n';
    //for(auto &&s: se) cout << s << ' '; cout << '\n'
    cout << "---\n";*/
    PT.init(s);
}
