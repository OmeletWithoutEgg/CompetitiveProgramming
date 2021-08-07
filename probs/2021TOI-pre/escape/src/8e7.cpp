//Challenge: Accepted
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <assert.h>
using namespace std;
void debug() {cout << endl;}
template <class T, class ...U> void debug(T a, U ... b) { cout << a << " "; debug(b...);}
template <class T> void pary(T l, T r) {
	while (l != r) {cout << *l << " ";l++;}
	cout << endl;
}
#define ll long long
#define ld long double
#define maxn 505
#define mod 1000000007
#define pii pair<int, int>
#define pdd pair<double, double>
#define ff first
#define ss second
#define io ios_base::sync_with_stdio(0);cin.tie(0);
int a[maxn][maxn];
int lx[maxn], ly[maxn], mx[maxn], my[maxn];
bool vx[maxn], vy[maxn], check[maxn];
int slack[maxn];
int tot;
bool dfs(int n, bool ch) {
	if (vx[n]) return false;
	vx[n] = 1;
	for (int v = 1;v <= tot;v++) {
		slack[v] = min(slack[v], a[n][v] - lx[n] - ly[v]);
		if (a[n][v] - lx[n] - ly[v] > 0) continue;
		vy[v] = 1;
		if (!my[v] || dfs(my[v], ch)) {
			if (ch) mx[n] = v, my[v] = n;
			return true;
		}
	}
	return false;
}
int main() {
	io
	int n;
	cin >> n;
	tot = n;
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) {
			cin >> a[i][j];
			a[i][j] = -a[i][j];
		}
	}
	for (int i = 1;i <= n;i++) {
		lx[i] = 1<<30;
		for (int j = 1;j <= n;j++) lx[i] = min(lx[i], a[i][j]);
	}
	
	for (int i = 1;i <= n;i++) {
		for (int j = 1;j <= n;j++) vx[j] = vy[j] = check[j] = 0;
		for (int j = 1;j <= n;j++) slack[j] = 1<<30;
		check[i] = 1;
		bool aug = 0;
		while (!aug) {
			for (int j = 1;j <= n;j++) {
				if (check[j] && dfs(j, 0)) {
					aug = 1;
					break;
				}
			}
			if (aug) break;
			int delta = 1<<30;
			for (int j = 1;j <= n;j++) {
				if (!vy[j]) delta = min(delta, slack[j]);
				check[j] = 0;
			}
			for (int j = 1;j <= n;j++) {
				if (vx[j]) lx[j] += delta;
				if (vy[j]) ly[j] -= delta;
				else {
					slack[j] -= delta;
					if (slack[j] == 0) {
						vy[j] = 1;
						if (!my[j]) {
							aug = 1;
						} else {
							check[my[j]] = 1;
						}
					}
				}
			}
		}
		for (int j = 1;j <= n;j++) vx[j] = vy[j] = 0;
		dfs(i, 1);
	}
	int ans = 0;
	for (int i = 1;i <= n;i++) lx[i] = -lx[i], ly[i] = -ly[i], ans += lx[i] + ly[i];
	cout << ans << "\n";
	for (int i = 1;i <= n;i++) cout << lx[i] << " ";
	cout << "\n";
	for (int i = 1;i <= n;i++) cout << ly[i] << " ";
	cout << "\n";
}	
