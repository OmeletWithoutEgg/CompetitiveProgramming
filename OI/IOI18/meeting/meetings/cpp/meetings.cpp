#include "meetings.h"
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
const int inf = 1e9;

std::vector<long long> minimum_costs(std::vector<int> H, std::vector<int> L,
                                     std::vector<int> R) {
  int Q = L.size();
  std::vector<long long> C(Q);
  for (int j = 0; j < Q; ++j) {
      int x = min_element(H.begin() + L[j], H.begin() + R[j] + 1) - H.begin();
      int mx = H[x];
      long long ans = H[x];
      for (int i = x-1; i >= L[j]; i--) {
          mx = max(mx, H[i]);
          ans += mx;
      }
      mx = H[x];
      for (int i = x+1; i <= R[j]; i++) {
          mx = max(mx, H[i]);
          ans += mx;
      }
      C[j] = ans;
  }
  return C;
}
