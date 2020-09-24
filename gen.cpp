#include <bits/stdc++.h>
#define y1 y_1
#define pdi pair<double,int>
#define ff first
#define ss second
using namespace std;
 
const int MAXN = 2000;
const int MAXC = 200000;
const double INF = 1e18;
int Q;
string testcase;
struct line{
  double a, b;
} p[MAXN+1], tmp;
int cnt;
int x1, x2, y1, y2;
pdi mmax;
 
double calc(int id, int x) {
  return p[id].a * x + p[id].b;
}
 
signed main(int argc, char *argv[]) {
  srand(time(NULL));
  testcase = argv[1];
  ofstream gen(testcase + ".in");
  ofstream ans(testcase + ".out");
  Q = atoi(argv[2]);
  gen << Q << "\n";
  while (Q--) {
    if (!cnt || rand() % 2) {
      x1 = 1, x2 = MAXC;
      y1 = rand() % MAXC + 1;
      y2 = rand() % MAXC + 1;
      gen << "add " << x1 << " " << y1 << " " << x2 << " " << y2 << "\n";
      if (x1 == x2)
        tmp.a = 0, tmp.b = max(y1, y2);
      else
        tmp.a = 1.0 * (y1 - y2) / (x1 - x2), tmp.b = y1 - x1 * tmp.a;
      p[++cnt] = tmp;
    } else {
      x1 = rand() % MAXC + 1;
      gen << "qry " << x1 << "\n";
      mmax = pdi(-INF, 0);
      for (int i = 1; i <= cnt; i++)
        mmax = max(mmax, pdi(calc(i, x1), i));
      ans << fixed << setprecision(6) << mmax.ff << " " << mmax.ss << "\n";
    }
  }
  return 0;
}
