#include "vision.h"

#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename H, typename ...T> void qqbx(const char *s, const H&h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;

void construct_network(int H, int W, int k) {
    int tot = H * W;
    int zero = -1;
    {
        add_not(0);
        add_and({0, tot++});
        zero = tot++;
    }
    vector<vector<int>> id(H, vector<int>(W));
    for(int i = 0; i < H; i++) {
        for(int j = 0; j < W; j++) {
            id[i][j] = i * W + j;
        }
    }
    vector<vector<int>> diagId(2, vector<int>(H+W, zero));
    vector<vector<int>> dId(2, vector<int>(H+W, zero));
    {
        vector<vector<vector<int>>> diag(2, vector<vector<int>>(H+W));
        for(int i = 0; i < H; i++) {
            for(int j = 0; j < W; j++) {
                diag[0][i+j].pb(id[i][j]);
                diag[1][i-j+W-1].pb(id[i][j]);
            }
        }
        for(int c = 0; c < 2; c++) for(int i = 0; i < H+W; i++) {
            if(diag[c][i].size()) {
                add_xor(diag[c][i]);
                diagId[c][i] = tot++;
                add_or(diag[c][i]);
                dId[c][i] = tot++;
            }
        }
    }
    vector<vector<int>> preId(2, vector<int>(H+W, zero));
    vector<vector<int>> pId(2, vector<int>(H+W, zero));
    for(int c = 0; c < 2; c++) for(int i = 0; i < H+W; i++) {
        add_xor({i ? preId[c][i-1] : zero, diagId[c][i]});
        preId[c][i] = tot++;
        add_or({i ? pId[c][i-1] : zero, dId[c][i]});
        pId[c][i] = tot++;
    }
    vector<int> exactly[2], maybe[2];
    for(int c = 0; c < 2; c++) for(int i = 0; i+k < H+W; i++) {
        add_and({diagId[c][i], diagId[c][i+k]});
        exactly[c].pb(tot++);
    }
    for(int c = 0; c < 2; c++) for(int i = -k; i < H+W; i++) {
        int l = i <= 0 ? zero : preId[c][i-1];
        int r = preId[c][min(H+W-1, i+k)];
        add_xor({l, r});
        add_not(tot++);
        int x = tot++, y = pId[c][min(H+W-1, i+k)], z = i <= 0 ? zero : pId[c][i-1];
        add_not(z), z = tot++;
        add_and({x, y, z});
        maybe[c].pb(tot++);
    }
    add_or(exactly[0]);
    int a = tot++;
    add_or(maybe[1]);
    int b = tot++;
    add_and({a, b});
    int X = tot++;
    add_or(exactly[1]);
    int c = tot++;
    add_or(maybe[0]);
    int d = tot++;
    add_and({c, d});
    int Y = tot++;
    add_or({X, Y});
}
