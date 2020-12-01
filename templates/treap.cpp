#include <bits/stdc++.h>
#define ff first
#define ss second

template<typename T>
class treap{ //merge-split treap
	private:
	struct node{
		static int rseed;
		T key;
		int pri, siz;
		node *l, *r;
		node(const T &k):key(k), pri(rseed=rseed*0xdefaced%1000000007+1), siz(1), l(nullptr), r(nullptr){}
		static int get_siz(node *p){return p?p->siz:0;}
		void pull(){siz=1+get_siz(l)+get_siz(r);}
	} *root;
	node *merge(node *a, node *b){//a<b (key)
		return (!a||!b) ? (a?a:b) : (a->pri < b->pri) ? (a->r=merge(a->r, b), a->pull(), a) : (b->l=merge(a, b->l), b->pull(), b);
	}
	void split(node *o, node *&a, node *&b, const T &k){
		if(!o)return a=b=nullptr, void();
		if(k < o->key)b = o, split(o->l, a, b->l, k), b->pull();
		else a = o, split(o->r, a->r, b, k), a->pull();
	}
	void split_by_rank(node *o, node *&a, node *&b, int r){
		if(!o)return a=b=nullptr, void();
		int new_r = r - node::get_siz(o->l) - 1;
		if(new_r < 0)b = o, split_by_rank(o->l, a, b->l, r), b->pull();
		else a = o, split_by_rank(o->r, a->r, b, new_r), a->pull();
	}
	public:
	void insert(const T &n){
		if(count(n))return;
		node *a, *b, *t=new node(n);
		split(root, a, b, n);
		root = merge(a, merge(t, b));
	}
	void erase(const T &n){
		node *a, *b, *c;
		split(root, a, b, n), split(b, b, c, n+1), delete b;
		root = merge(a, c);
	}
	int rank(const T &k){
		node *a, *b;
		split(root, a, b, k);
		int res =  node::get_siz(a);
		return root = merge(a, b), res;
	}
	T kth(int r){
		node *a, *b, *c;
		return split_by_rank(root, a, c, r), split_by_rank(a, a, b, r-1), root = merge(a, merge(b, c)), b->key;
	}
	bool count(int n){
		node *t = root;
		while(t && t->key!=n)t = n<t->key ?t->l:t->r;
		return t && t->key == n;
	}
	int size(){return node::get_siz(root);}
	void travel(){
		std::pair<int, node *> stk[100000] = {};
		int p = 0;
		stk[p++] = {0, root};
		while(p){
			auto cur = stk[--p];
			for(int i = 0;i < cur.ff<<1;i++)std::cout << '\t';
			std::cout << "key:" << cur.ss->key << " pri:" << cur.ss->pri << " siz:" << cur.ss->siz << '\n';
			if(cur.ss->l)stk[p++] = {cur.ff+1, cur.ss->l};
			if(cur.ss->r)stk[p++] = {cur.ff+1, cur.ss->r};
		}
	}
	treap(){root = nullptr;}
	treap(std::vector<int>& sorted){for(auto i:sorted)root = merge(root, new node(i));}
};
treap<int> a;
template<typename T> int treap<T>::node::rseed = 7122;

using namespace std;

int main(){
	int t;
	for(int i = 0;i < 10;i++)cin >> t, a.insert(t);
	cout << '\n';
	a.travel();
	for(int i = 0;i < 10;i++)cin >> t, cout << a.rank(t) << '\n';//, a.travel();
	return 0;
}
