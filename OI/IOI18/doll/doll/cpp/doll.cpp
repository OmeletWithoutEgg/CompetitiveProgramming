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
const int maxn = 800025;

int odd[maxn];
int ls[maxn], rs[maxn];
int leaf[maxn];
int counter = 0;
int build(int root, int lev) {
    if (lev == 0) {
        debug("LEAF");
        return -2;
    }
    int cur = counter++;
    ls[cur] = build(root, lev - 1);
    rs[cur] = build(root, lev - 1);
    return cur;
}

void dfs(vector<int> &A, int root, int cur, int a, int b) {
    if (ls[cur] != -1)
        dfs(A, root, ls[cur], a*2, b);
    else
        ls[cur] = b < A.size() ? A[b] : root;
    if (rs[cur] != -1)
        dfs(A, root, rs[cur], a*2, b+a);
    else
        rs[cur] = b+a < A.size() ? A[b+a] : root;
}
void create_circuit(int M, std::vector<int> A) {

  int N = A.size();
  int L = __lg(N) + 1;
  vector<int> aux(L);
  for (int i = 0; i < L; i++) {
      aux[i] = counter++;
  }

  vector<int> C(M + 1, -aux[0] - 1);
  for (int i = 0; i < L; i++) {
      if (i != 0)
          rs[aux[i-1]] = aux[i];
      int lev = L - 1 - i;
      debug(i);
      if (N >> lev & 1) {
          ls[aux[i]] = build(aux[0], lev);
      } else {
          ls[aux[i]] = aux[0];
      }
  }
  rs[aux[L-1]] = -1;

  int it = 0;
  int cur = aux[0];
  while (cur != -1) {
      debug(cur);
      int nxt = odd[cur] ? rs[cur] : ls[cur];
      if (nxt == -2) {
          debug("JIZZ");
          if (it < A.size()) {
              debug(A[it]);
              (odd[cur] ? rs[cur] : ls[cur]) = -A[it++]-1;
              nxt = aux[0];
          } else {
              nxt = (odd[cur] ? rs[cur] : ls[cur]) = aux[0];
          }
      }
      odd[cur] ^= 1;
      cur = nxt;
  }
  pary(odd, odd+counter);

  vector<int> X(counter), Y(counter);
  for (int i = 0; i < counter; i++) {
      X[i] = -ls[i]-1;
      Y[i] = -rs[i]-1;
  }

  answer(C, X, Y);
}
