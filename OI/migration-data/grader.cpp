#include <cstdio>
#include <vector>
#include <bits/stdc++.h>

using namespace std;
int N, M, L, ans[500];
pair<int,int> p[500];
vector<pair<pair<int,int>,pair<int,int>>> seg;
vector<int> g[300];
bool ori(pair<int,int> a, pair<int,int> b) {
    //cout << a.first * b.second - a.second * b.first << ';' << '\n';
    return a.first * b.second - a.second * b.first > 0;
}
pair<int,int> dif(pair<int,int> a, pair<int,int> b) {
    return pair<int,int>(a.first-b.first, a.second-b.second);
}
bool intersect(pair<pair<int,int>,pair<int,int>> X, pair<pair<int,int>,pair<int,int>> Y) {
    auto [a, b] = X;
    auto [c, d] = Y;
    return ori(dif(c, a), dif(b, a)) != ori(dif(d, a), dif(b, a)) &&
           ori(dif(a, c), dif(d, c)) != ori(dif(b, c), dif(d, c));
}
int calc() {
    int cnt = 0;
    seg.clear();
    for(int i = 0; i < N; i++) {
        for(int j: g[i]) if(j < i) {
            seg.emplace_back(p[ans[i]], p[ans[j]]);
        }
    }
    for(int i = 0; i < int(seg.size()); i++) {
        for(int j = 0; j < i; j++) {
            if(intersect(seg[i], seg[j])) {
                ++cnt;
            }
        }
    }
    return cnt;
}
int main() {
    freopen("in/01.txt", "r", stdin);
    scanf("%d%d", &N, &M);
    for(int i = 0; i < M; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        --a, --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    scanf("%d", &L);
    for(int i = 0; i < L; i++) {
        scanf("%d%d", &p[i].first, &p[i].second);
    }
    /*for(int i = 0; i < N; i++) {
        cout << i << ':';
        for(int j: g[i]) {
            cout << ' ' << j;
        }
        cout << '\n';
    }*/
    for(int i = 0; i < L; i++) ans[i] = i;
    //sort(ans, ans+L, [&](int a, int b){return g[a].size() < g[b].size();});
    //printf("%d\n", calc());
    freopen("jizz.txt", "w", stdout);
    mt19937_64 rng(20073);
    for(int i = 0; i < 10000; i++) {
        shuffle(ans, ans+L, rng);
        int r = calc();
        if(r < 250) {
            printf("%d\n", r);
            for(int i = 0; i < N; i++) {
                printf("%d%c", ans[i], i==N-1 ? '\n' : ' ');
            }
        }
    }
}
