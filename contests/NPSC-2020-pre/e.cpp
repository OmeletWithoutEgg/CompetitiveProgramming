#include <bits/stdc++.h>

using namespace std;
const int N = 40025, K = 200;

struct Treap {
    struct node {
        int key, pri;
        int cnt[2];
        int ans[2];
    };
};

struct treap{ //merge-split treap
    struct node{
        static int rseed;
        int key;
        int pri;
        int siz;
        int cnt[2];
        int ans[2];
        int sum;
        bool laz;
        node *l, *r;
        node(int k) : key(k), pri(rseed=rseed*0xdefaced%1000000007+1), siz(0), cnt{}, ans{}, sum(0), laz(false), l(nullptr), r(nullptr) {}
        int sum;
        friend int get_siz(node *p){return p?p->siz:0;}
        void pull() {
            siz=cnt[0]+cnt[1]+get_siz(l)+get_siz(r);
            int dir = get_siz(l);
            ans[0] = (l ? l->ans[0] : 0) + (r ? r->ans[(get_siz(l) + cnt[0] + cnt[1]) & 1] : 0) + ;
            ans[1] = (l ? l->ans[1] : 0) + (r ? r->ans[~(get_siz(l) + cnt[0] + cnt[1]) & 1] : 0) + ;
        }
        void push() {
            ;
        }
    } *root;
    node *merge(node *a, node *b){//a<b (key)
        return (!a||!b) ? (a?a:b) : (a->pri < b->pri) ? (a->push(), a->r=merge(a->r, b), a->pull(), a) : (b->push(), b->l=merge(a, b->l), b->pull(), b);
    }
    void split(node *o, node *&a, node *&b, const T &k){
        if(!o)return a=b=nullptr, void();
        o->push();
        if(k < o->key)
            b = o, split(o->l, a, b->l, k), b->pull();
        else
            a = o, split(o->r, a->r, b, k), a->pull();
    }
    bool count(int n){
        node *t = root;
        while(t && t->key!=n)t = n<t->key ?t->l:t->r;
        return t && t->key == n;
    }
    void insert(const T &n){
        if(count(n))return;
        node *a, *b, *t = new node(n);
        split(root, a, b, n);
        root = merge(a, merge(t, b));
    }
    void erase(const T &n){
        node *a, *b, *c;
        split(root, a, b, n), split(b, b, c, n+1), delete b;
        root = merge(a, c);
    }
};
treap trp;
void add(int x, int parity) {
    ;
}
void remove(int x, int parity) {
    ;
}
int treap::node::rseed = 7122;
tuple<int,int,int> Q[N];
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) cin >> v[i];
    int q;
    cin >> q;
    for(int i = 0; i < q; i++) {
        auto &[l, r, id] = Q[i];
        cin >> l >> r;
        --l, --r;
        id = i;
    }
    sort(Q, Q+q, [](auto a, auto b) {
        auto [la, ra, ida] = a;
        auto [lb, rb, idb] = b;
        la /= K, lb /= K;
        if(la != lb) return la < lb;
        return ra > rb;
    });
    vector<int> ans(q);
    int L = 1, R = 0;
    int cur = 0;
    for(int i = 0; i < q; i++) {
        auto [l, r, id] = Q[i];
        while(L > l) --L, add(a[L], L & 1);
        while(R < r) ++R, add(a[R], R & 1);
        while(L < l) remove(a[L], L & 1), ++L;
        while(R > r) remove(a[R], R & 1), --R;
        ans[id] = cur;
    }
    for(int i = 0; i < q; i++) cout << ans[i] << '\n';
}
