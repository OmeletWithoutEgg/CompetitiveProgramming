#include "Azer.h"
#include <vector>

namespace {

int N;
int variable_example[500000];
int count;

}  // namespace

void InitA(int N, int A, std::vector<int> U, std::vector<int> V,
           std::vector<int> C) {
  ::N = N;
  for (int i = 0; i < A; ++i) {
    variable_example[i] = U[i] + V[i] - C[i];
  }
  SendA(true);
  count = 1;
}

void ReceiveA(bool x) {
  ++count;
  if (count < 58000) {
    SendA(x);
    ++count;
  }
}

std::vector<int> Answer() {
  std::vector<int> ans(N);
  for (int k = 0; k < N; ++k) {
    ans[k] = variable_example[k];
  }
  return ans;
}
