#include "Catherine.h"
#include <vector>

namespace {

int A, B;
int variable_example = 0;

}  // namespace

void Init(int A, int B) {
  ::A = A;
  ::B = B;
}

int Move(std::vector<int> y) {
  ++variable_example;
  int sum = 0;
  for(int c: y) sum += c;
  if(sum == 0) return rev = true, -1;
  if(sum == 1) {
    for (int j = 0; j < A; ++j) {
      if (y[j] != 0) {
        return j;
      }
    }
  }
  if(sum == 2) {
    ;
  }
  for(int j = 0; j < A; ++j) {
    ;
  }
}
