#include <bits/stdc++.h>

using namespace std;
typedef long double ld;

struct LiChao {
    struct Line {
        ld a, b;
        ld operator(ld x) { return a * x + b; }
    };
    struct node {
        Line best;
        node *L, *R;
        node(Line line) : best(line), L(0), R(0) {}
    } *root = nullptr;
    void add(node *&now, Line v, double l, double r) {
        ;
    }
};
struct Query {
    int t;
    int x1, x2, y1, y2;
    ostream operator<<(ostream &O, Query &q) {
        O >> q.t;
        if(q.t == 1) return O >> q.x1 >> q.y1 >> q.x2 >> q.y2;
    }
};
vector<int> solve(vector<Query> Q) {
    for(auto q: Q) {
        if(q.t == 1) {
            auto [t, x1, x2, y1, y2] = q;
            Line;
        }
    }
}
signed main() {
    ifstream fin("1.in");
}
