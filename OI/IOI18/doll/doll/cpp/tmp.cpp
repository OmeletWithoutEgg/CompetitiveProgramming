#include "doll.h"
#include <bits/stdc++.h>
#ifdef local
#define debug(x...) qqbx(#x, x)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "\e[1;32m(" << s << ") = ("), ... , (std::cerr << a << (--cnt ? ", " : "\e[0m)\n")));
}
#define pary(x...) danb(#x, x)
template <typename T> void danb(const char *s, T L, T R) {
    std::cerr << "\e[1;32m[ " << s << " ] = [ ";
    for (int f = 0; L != R; ++L)
        std::cerr << (f++ ? ", " : "") << *L;
    std::cerr << " ]\e[0m\n";
}
#else
#define debug(...) ((void)0)
#define pary(...) ((void)0)
#endif // local
#define all(v) begin(v),end(v)

using namespace std;
const int maxn = 500025;

int odd[maxn];
int ls[maxn], rs[maxn];
int leaf[maxn];
int counter = 0;
int build(function<int(int)> & F, int l, int r, int a, int b) {
    int cur = counter++;
    if (l+1 == r) {
        ls[cur] = F(b);
        rs[cur] = F(b+a);
        return cur;
    }
    leaf[cur] = -1;
    int m = l+(r-l)/2;
    ls[cur] = build(F, l, m, a*2, b);
    rs[cur] = build(F, m, r, a*2, b+a);
    return cur;
}
void create_circuit(int M, std::vector<int> A) {

  int N = A.size();
  /*
  vector<int> cnt(N + 1);
  for (int i = 0; i < N; i++) cnt[A[i]] += 1;
  vector<int> tmp;
  for (int i = 0; i < N; i++) {
      if (cnt[A[i]] != 1) {
          tmp.push_back(i);
      }
  }
  tmp.push_back(71222);
  pary(all(tmp));
  */
  
  std::vector<int> C(M + 1);
  int cur = 0;
  int last = -1;
  for (int i = 19; i >= 1; i--) {
      while (N >= (1<<i)-1) {
          int aux = counter++;
          int root =
              build([&](int idx){
                  if (idx < (1<<i)-1) {
                      return A[idx + cur];
                  } else {
                      return aux;
                  }
              }, 0, 1 << (i-1), 1, 0);
          N -= (1 << i) - 1;
          ls[aux] = root;
          if (last == -1) {
              C[0] = aux;
          } else {
              rs[last] = aux;
          }
      }
  }
  assert ( N == 0 );
  rs[last] = 0;

  std::vector<int> X(counter), Y(counter);
  for (int i = 0; i < counter; i++) {
      X[i] = -ls[i]-1;
      Y[i] = -rs[i]-1;
  }

  int cur = root;
  do {
      if (leaf[cur] != -1) {
          debug(cur, leaf[cur], odd[cur]);
          // pary(odd, odd+counter);
      }
      int nxt = odd[cur] ? rs[cur] : ls[cur];
      odd[cur] ^= 1;
      cur = nxt;
  } while (accumulate(odd, odd+counter, 0) != 0);

  answer(C, X, Y);
}
