#include "Bruno.h"
#include <vector>

namespace {

int N;
int variable_example[1000000];
int count;

bool FunctionExample(bool P) {
  return !P;
}

}  // namespace

void InitB(int N, std::vector<int> P) {
  ::N = N;
  for(int i = 0; i < N; i++) {
    variable_example[i] = P[i];
  }
  count = 0;
}

void ReceiveB(bool y) {
  if (count < 10000) {
    SendB(FunctionExample(y));
    ++count;
  }
}
