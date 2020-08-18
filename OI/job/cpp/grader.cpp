#include "job.cpp"
#include <cstdio>
#include <cassert>

using namespace std;

int main() {
	int n;
	srand(7122);
	assert(1 == scanf("%d", &n));
	vector<int> p(n);
	for (int i = 0; i < n; i++)
		p[i] = i-1;//assert(1 == scanf("%d", &p[i]));
	vector<int> u(n);
	for (int i = 0; i < n; i++)
		u[i]=rand()%10+1;//assert(1 == scanf("%d", &u[i]));
	vector<int> d(n);
	for (int i = 0; i < n; i++)
		d[i]=rand()%10+1;//assert(1 == scanf("%d", &d[i]));
	fclose(stdin);
    //for(int i: p) cout << i << ' '; cout << '\n';
    //for(int i: u) cout << i << ' '; cout << '\n';
    //for(int i: d) cout << i << ' '; cout << '\n';

    long long t = 0, pe = 0;
    for(int i = 0; i < n; i++) {
        t += d[i];
        pe += t*u[i];
    }
    printf("%lld\n", pe);

	long long result = scheduling_cost(p, u, d);

	printf("%lld\n", result);
	fclose(stdout);
	return 0;
}

/*


3
-1 0 1
5 2 5
3 4 1

3
-1 0 0
5 2 5
3 4 1

4
-1 0 1 2
6 1 3 7
8 3 3 1

3
-1 0 1
7 2 4
8 9 4
*/
