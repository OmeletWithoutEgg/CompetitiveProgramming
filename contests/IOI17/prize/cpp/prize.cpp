#include "prize.h"

#include <bits/stdc++.h>
#ifdef local
#define debug(...) QQBX(#__VA_ARGS__, __VA_ARGS__)
void QQBX(const char *s) {}
template <typename H, typename ...T> void QQBX(const char *s, const H&h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if(sizeof...(T)) QQBX(++s, args...);
}
#define safe std::cerr<<__PRETTY_FUNCTION<<" line "<<__LINE__<<" safe\n";
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local

using namespace std;

int find_best(int n) {
    // 1 + 2 + 5 + x + x^2+1 <= 200000
    // non-lolipop box: 
    // x <= 447;
    /* for(int i = 0; i < n; i++) { */
    /*     vector<int> res = ask(i); */
    /*     if(res[0]+res[1]==0) return i; */
    /* } */
    mt19937 rng(7122);
    int mx = 0;
    for(int i = 0; i < 1000; i++) {
        auto res = ask(uniform_int_distribution<int>(0, n-1)(rng));
        mx = max(mx, res[0]+res[1]);
    }
    int x = 0;
    for(int i = 0; i < 500; i++) {
        for(int s = 1<<__lg(n); s; s>>=1) if(x+s < n) {
            auto res = ask(x+s);
            if(res[0]+res[1] == 0) return x+s;
            if(res[0]+res[1] == mx && res[0] == i) x += s;
        }
        auto res = ask(x);
        if(res[0]+res[1] == 0) return x;
        ++x;
    }
    return -1;
}
