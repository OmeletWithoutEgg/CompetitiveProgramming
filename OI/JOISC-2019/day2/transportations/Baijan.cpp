#include "Baijan.h"
#include <vector>

namespace {

int N;
int count;

bool FunctionExample(bool P) {
  return !P;
}

}  // namespace

void InitB(int N, int B, std::vector<int> S, std::vector<int> T,
           std::vector<int> D) {
  ::N = N;
  count = 0;
}

void ReceiveB(bool y) {
  ++count;
  if (count < 58000) {
    SendB(FunctionExample(y));
    ++count;
  }
}
