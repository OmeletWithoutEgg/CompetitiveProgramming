#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include <cstdio>
#include <random>

const int N = 130025;

inline char readchar() {
    constexpr int B = 1<<20;
    static char buf[B], *p, *q;
    if(p == q && (q=(p=buf)+fread(buf,1,B,stdin)) == buf) return EOF;
    return *p++;
}
inline int nextint() {
    int x = 0, c = readchar();
    while(c < '0') c = readchar();
    while(c >= '0') x=x*10+(c^'0'), c=readchar();
    return x;
}

inline void readuntil(char *s, char esc = '\n') {
    char c = readchar();
    while(c != esc) *s++ = c, c = readchar();
}

std::mt19937 rnd(7122);
struct BST {
	struct node {
		int pri, sz, rev;
		int l, r;
	} S[N];
	void flip(int x) {
		S[x].rev = !S[x].rev;
		std::swap(S[x].l, S[x].r);
	}
	void pull(int x) {
		S[x].sz = S[S[x].l].sz + 1 + S[S[x].r].sz;
	}
	void push(int x) {
		if(!S[x].rev) return;
		flip(S[x].l), flip(S[x].r);
		S[x].rev = false;
	}
	void split(int o, int &a, int &b, int k) {
		if(!o) return a = b = 0, void();
		push(o);
		int s = S[S[o].l].sz + 1;
		//debug(k,s,o,S[o].l);
		if(k < s)
			b = o, split(S[o].l, a, S[b].l, k), pull(b);
		else
			a = o, split(S[o].r, S[a].r, b, k - s), pull(a);
	}
	int join(int a, int b) {
		if(!a || !b) return a ? a : b;
		push(a), push(b);
		if(S[a].pri < S[b].pri)
			return S[a].r = join(S[a].r, b), pull(a), a;
		else
			return S[b].l = join(a, S[b].l), pull(b), b;
	}
	void dfs(int i, bool r = true, int d = 0) {
	    if(!i) return;
	    push(i);
	    dfs(S[i].l, 0, d+1);
	    printf("%d%c", i, (r && !S[i].r ? '\n' : ' '));
        dfs(S[i].r, r, d+1);
	}
} trp;
signed main() {
    //ios_base::sync_with_stdio(0), cin.tie(0);
	int n=nextint(), q=nextint();
	int root = 0;
	for(int i = 1; i <= n; i++) trp.S[i] = {rnd(), 1, 0, 0, 0}, root = trp.join(root, i);
	//trp.dfs(root);
	while(q--) {
        char com[5];
        readuntil(com, ' ');
		if(com[0] == 'R') {
            int a, b, c, l, r;
            l = nextint(), r = nextint();
            trp.split(root, b, c, r);
            trp.split(b, a, b, l-1);
            trp.flip(b);
            //cout << "rev ";
            //trp.dfs(b);
            root = trp.join(a, trp.join(b,c));
		} else {
		    int l1, r1, l2, r2, a, b, c, d, e;
            l1 = nextint(), r1 = nextint(), l2 = nextint(), r2 = nextint();
            trp.split(root, d, e, r2);
            trp.split(d, c, d, l2-1);
            trp.split(c, b, c, r1);
            trp.split(b, a, b, l1-1);
            root = trp.join(a, trp.join(d, trp.join(c, trp.join(b, e))));
		}
	}
	trp.dfs(root);
}

