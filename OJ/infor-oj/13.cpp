#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

ll _seed = 7122;
ll RAND(){return _seed=_seed*0xdefaced+1;}
struct node{
    ll val, sz;
    bool inv;
    node *l,*r;
    node(ll x):val(x),sz(1),inv(0),l(nullptr),r(nullptr){}
    friend ll size(node *p){return p?p->sz:0;}
    void inverse(){
        swap(l,r);
        inv ^= 1;
    }
    void push(){
        if(!inv) return;
        if(l) l->inverse();
        if(r) r->inverse();
        inv = 0;
    }
    void pull(){sz = size(l)+1+size(r);}
} *root;
node *merges(node *a,node *b){
    if(!a||!b) return a?a:b;
    a->push(), b->push();
    if(RAND()&4) return a->r = merges(a->r,b), a->pull(), a;
    else return b->l = merges(a,b->l), b->pull(), b;
}
void splits(node *o, node*&a,node *&b,ll k){
    if(!o) return a = b = nullptr,void();
    o->push();
    if(size(o->l)+1 < k) a = o, splits(o->r,a->r,b,k-size(o->l)-1);
    else b = o, splits(o->l,a,b->l,k);
    o->pull();
}
void trav(node *p){
    if(!p) return;
    p->push();
    trav(p->l);
    cout << p->val << ' ';
    trav(p->r);
}
ll n,m,c;
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;
    for(int i = 1; i <= n; i++) root = merges(root,new node(i));
    for(int i = 0; i < m; i++){
        cin >> c;
        if(c == 1){
            ll l,r;
            cin >> l >> r;
            node *a,*b,*c;
            splits(root,b,c,r+1);
            splits(b,a,b,l);
            b->inverse();
            //trav(b);cout<<'\n';
            root = merges(a,merges(b,c));
        }else if(c == 2){
            ll l1,r1,l2,r2;
            cin >> l1 >> r1 >> l2 >> r2;
            node *a,*b,*c,*d,*e;
            splits(root,d,e,r2+1);
            splits(d,c,d,l2); // d
            splits(c,b,c,r1+1);
            splits(b,a,b,l1); // b
            //trav(b),cout<<'\n',trav(d),cout<<'\n';
            root = merges(merges(merges(merges(a,d),c),b),e);
        }
        //trav(root);
        //cout << '\n';
    }
    trav(root);
}
