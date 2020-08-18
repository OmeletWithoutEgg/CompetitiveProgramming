#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const ll N = 200020;

ll __seed = 7122;
ll RAND(){return __seed = __seed*0xdefaced+1;}
struct node{
    ll key, ans, mi, mx;
    node *l,*r;
    node(ll x):key(x),ans(0),mi(x),mx(x),l(nullptr),r(nullptr){}
    void pull(){
        ans = 0, mi = mx = key;
        if(l) ans = max({ans, key-l->mx-1, l->ans}), mi = l->mi;
        if(r) ans = max({ans, r->mi-key-1, r->ans}), mx = r->mx;
    }
};
node *merges(node *a, node *b){
    if(!a||!b) return a?a:b;
    if(RAND()&4) return a->r = merges(a->r,b), a->pull(), a;
    else return b->l = merges(a,b->l), b->pull(), b;
}
void splits(node *o, node *&a, node*&b, ll k){
    if(!o) return a = b = nullptr, void();
    if(o->key < k) a = o, splits(o->r,a->r,b,k), a->pull();
    else b = o, splits(o->l,a,b->l,k), b->pull();
}
node *insert(node *o, ll x){
    node *a,*b;
    splits(o,a,b,x);
    return merges(a,merges(new node(x),b));
}
node *erase(node *o,ll x){
    node *a,*b,*c;
    splits(o,a,b,x);
    splits(b,b,c,x+1);
    delete b;
    return merges(a,c);
}
void trav(node *o,int d=0){
    if(!o) return;
    trav(o->l,d+1);
    for(int i=0;i<d;i++)cout<<'\t';
    cout << o->key << ',' << o->ans << '\n';
    trav(o->r,d+1);
}
ll a[N],n,q,k,x,y,c;
map<ll,node *> mp;
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n >> q >> c;
    for(int i = 0; i < n; i++){
        cin >> a[i];
        if(mp.count(a[i])) mp[a[i]] = insert(mp[a[i]],i);
        else mp[a[i]] = new node(i);
    }
    for(int i = 0; i < q; i++){
        cin >> c;
        if(!c) {
            cin >> x >> k;
            mp[a[x]] = erase(mp[a[x]],x);
            a[x] = k;
            mp[a[x]] = insert(mp[a[x]],x);
        }else{
            cin >> x >> y >> k;
            node *a,*b,*c;
            splits(mp[k],a,b,x);
            splits(b,b,c,y);
            //cout<<"ans:";
            if(!b) cout << y-x << '\n';
            else cout << max({y-b->mx-1, b->mi-x, b->ans}) << '\n';
            mp[k] = merges(a,merges(b,c));
            //cout<<"===========\n",trav(mp[k]),cout<<"\n===========\n";
        }
    }
}
/*
5 5 4
2 2 2 2 2
1 0 5 2
0 1 3
1 2 4 3
0 3 3
1 1 5 3
*/
