#include "average.h"

#include <cassert>
#include <cstdio>

#include <string>
#include <vector>

int main() {
  int Q;
  assert(1 == scanf("%d", &Q));

  std::vector<int> type(Q), K(Q), L(Q), R(Q);
  for (int i = 0; i < Q; ++i) {
    assert(1 == scanf("%d", &type[i]));
    if (type[i] == 0) {
      assert(1 == scanf("%d", &K[i]));
    } else if (type[i] == 1) {
      assert(2 == scanf("%d %d", &L[i], &R[i]));
    }
  }
  
  init();

  std::vector<double> maximum_averages;
  for (int i = 0; i < Q; ++i) {
    if (type[i] == 0) {
      addMonth(K[i]);
    } else if (type[i] == 1) {
      maximum_averages.push_back(maximumAverage(L[i], R[i]));
    }
  }

  for (int i = 0; i < static_cast<int>(maximum_averages.size()); ++i) {
    printf("%.9lf\n", maximum_averages[i]);
  }
  return 0;
}
