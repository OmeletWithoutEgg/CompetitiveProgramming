#include "Anna.h"
#include <vector>

namespace {

int N, L, R;
int count;

}  // namespace

void InitA(int N, int L, int R) {
  ::N = N;
  ::L = L;
  ::R = R;
  SendA(true);
  count = 1;
}

void ReceiveA(bool x) {
  if (count < 18) {
    SendA(x);
    ++count;
  }
}

int Answer() {
  return L;
}
