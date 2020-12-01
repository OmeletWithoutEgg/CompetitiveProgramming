#include <bits/stdc++.h>
#define safe cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"

using namespace std;
const int K = 26;

struct AhoCorasick {
    struct node {
        node *ch[K], *fail;
        int cnt;
        node() : ch{}, fail(nullptr), cnt(0) {}
    } *root;
    vector<node*> bfs;
    AhoCorasick() : root(new node()), bfs{root} {}
    node* insert(const string &s) {
        node *now = root;
        for(char c: s) {
            c -= 'a';
            if(!now->ch[c])
                now->ch[c] = new node();
            now = now->ch[c];
        }
        return now;
    }
    void buildFail() {
        queue<node*> q;
        bfs = vector<node*>{root};
        for(int c = 0; c < K; c++) {
            if(root->ch[c])
               root->ch[c]->fail = root, q.push(root->ch[c]);
        }
        while(!q.empty()) {
            node *now = q.front(); q.pop();
            bfs.push_back(now);
            for(int c = 0; c < K; c++) {
                if(now->ch[c]) {
                    node *f = now->fail;
                    while(f != root && !f->ch[c]) f = f->fail;
                    now->ch[c]->fail = f->ch[c] ? f->ch[c] : root;
                    q.push(now->ch[c]);
                }
            }
        }
    }
    void run(const string &s) {
        node *now = root;
        for(char c: s) {
            c -= 'a';
            while(now != root && !now->ch[c]) now = now->fail;
            now = now->ch[c] ? now->ch[c] : root;
            now->cnt += 1;
        }
    }
    void DP() {
        for(int i = int(bfs.size())-1; i >= 0; i--) {
            node *x = bfs[i];
            if(x->fail) x->fail->cnt += x->cnt;
        }
    }
    void clear() {
        for(node *p: bfs) delete p;
        bfs.clear();
        root = new node();
    }
} AC;
signed main() {
    int t;
    cin >> t;
    while(t--) {
        int q;
        string T;
        cin >> T >> q;
        vector<AhoCorasick::node*> ed;
        AC.clear();
        while(q--) {
            string P;
            cin >> P;
            ed.push_back(AC.insert(P));
        }
        AC.buildFail();
        AC.run(T);
        AC.DP();
        for(auto p: ed) cout << p->cnt << '\n';
    }
}
