#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>

using namespace std;

void update_state(int& cur_gang, int& cur_cows, int cow_gang) {
  if(cur_cows == 0) {
    cur_gang = cow_gang;
  }
  if(cur_gang == cow_gang) {
    cur_cows++;
  } else {
    cur_cows--;
  }
}

/* Compute the number of cows from the first gang can be on the field at the
 * end. */
int max_cows(int cur_gang, int cur_cows, vector<int> G) {
  /* Keep trying to place the gang from the largest gang left. */
  sort(G.begin() + 1, G.end());
  while(G.back() > 0) {
    for(int i = G.size() - 1; i > 0; i--) {
      update_state(cur_gang, cur_cows, i);
      G[i]--;
      if(G[i - 1] <= G[i]) {
        break;
      }
    }
  }
  /* Finish by placing all of Bessie's gang. */
  for(int i = 0; i < G[0]; i++) {
    update_state(cur_gang, cur_cows, 0);
  }
  return cur_gang == 0 ? cur_cows : 0;
}

int main() {
  // freopen("gangs.in", "r", stdin);
  // freopen("gangs.out", "w", stdout);

  int N, M; cin >> N >> M;
  vector<int> G(M);
  for(int i = 0; i < M; i++) {
    cin >> G[i];
  }

  int cur_gang = 0;
  int cur_cows = 0;
  int res = max_cows(cur_gang, cur_cows, G);
  if(res > 0) {
    cout << "YES\n" << res << "\n";
    for(int i = 0; i < N; i++) {
      /* Find the smallest gang to place next. */
      int prev_cur_gang = cur_gang;
      int prev_cur_cows = cur_cows;
      for(int j = 0; ; j++) {
        if(G[j] == 0) {
          continue;
        }

        G[j]--;
        update_state(cur_gang, cur_cows, j);
        if(max_cows(cur_gang, cur_cows, G) == res) {
          cout << j + 1 << '\n';
          break;
        }

        /* Placing gang j next didn't work out.  Undo the changes. */
        G[j]++;
        cur_gang = prev_cur_gang;
        cur_cows = prev_cur_cows;
      }
    }
  } else {
    cout << "NO" << endl;
  }
  return 0;
}
