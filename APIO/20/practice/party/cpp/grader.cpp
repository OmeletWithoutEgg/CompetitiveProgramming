#include "party.h"

#include <cassert>
#include <cstdio>

#include <string>
#include <vector>

static int N, M, Q;

static std::vector<long long> male_acquaintances;
static std::vector<long long> female_acquaintances;

static void wrongAnswer(std::string message) {
  printf("WA: %s\n", message.c_str());
  exit(0);
}

std::vector<int> ask(std::vector<int> G) {
  if (--Q < 0) {
    wrongAnswer("Too many queries");
  }
  long long males = 0;
  long long females = 0;

  int previous_index = -1;
  for (int i = 0; i < G.size(); ++i) {
    if (G[i] <= previous_index || G[i] >= N + M) {
      wrongAnswer("Invalid index");
    }
    if (G[i] < N) {
      females |= male_acquaintances[G[i]];
    } else {
      males |= female_acquaintances[G[i] - N];
    }
  }

  std::vector<int> result;
  while (males > 0) {
    int male_index = __builtin_ctzll(males);
    result.push_back(male_index);
    males ^= 1LL << male_index;
  }
  while (females > 0) {
    int female_index = __builtin_ctzll(females);
    result.push_back(female_index + N);
    females ^= 1LL << female_index;
  }
  return result;
}

int main() {
  assert(3 == scanf("%d %d %d", &N, &M, &Q));
  male_acquaintances.resize(N);
  female_acquaintances.resize(M);

  for (int i = 0; i < N + M; ++i) {
    char buffer[N + M + 1];
    assert(1 == scanf("%s", buffer));
    for (int j = 0; j < N + M; ++j) {
      if (buffer[j] == '1') {
        if (i < N) {
          male_acquaintances[i] |= 1LL << (j - N);
        } else {
          female_acquaintances[i - N] |= 1LL << j;
        }
      }
    }
  }

  int unusual_guest = findUnusualGuest(N, M, Q);

  if (unusual_guest < 0 || unusual_guest >= N + M) {
    wrongAnswer("Invalid index");
  }
  if (unusual_guest < N) {
    if (__builtin_popcountll(male_acquaintances[unusual_guest]) == 1) {
      wrongAnswer("Non-unusual guest found");
    }
  } else {
    if (__builtin_popcountll(female_acquaintances[unusual_guest - N]) == 1) {
      wrongAnswer("Non-unusual guest found");
    }
  }

  printf("%d\n", unusual_guest);
  
  return 0;
}
