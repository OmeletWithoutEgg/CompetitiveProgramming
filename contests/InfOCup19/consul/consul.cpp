#include "grader.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (" , ... ,
         (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v), end(v)
using namespace std;

void solve(int n)
{
    /// insert your code
    /// for example
    vector<int> p(n);
    iota(all(p), 1);
    mt19937 rng(7122);
    shuffle(all(p), rng);
    for(int i = 0; i < 25 && i < n; i++) {
        int x = kth(p[i]);
        if(cnt(x) > n / 3) {
            say_answer(x);
            return;
        }
    }
    say_answer(-1);
}
