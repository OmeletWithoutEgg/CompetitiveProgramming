#include<bits/stdc++.h>
#define pb emplace_back
#define AI(i) begin(i), end(i)
using namespace std;
using ll = long long;
template<class T>
bool chmax(T &val, T nv) { return val < nv ? (val = nv, true) : false; }
template<class T>
bool chmin(T &val, T nv) { return nv < val ? (val = nv, true) : false; }
#ifdef KEV
#define DE(args...) kout("[ " + string(#args) + " ] = ", args)
void kout() {cerr << endl;}
template<class T1, class ...T2>
void kout (T1 v, T2 ...e) { cerr << v << ' ', kout(e...); }
template<class T>
void debug(T L, T R) { while (L != R) cerr << *L << " \n"[next(L)==R], ++L; }
#else
#define DE(...) 0
#define debug(...) 0
#endif
// What I should check
// 1. overflow
// 2. corner cases
// Enjoy the problem instead of hurrying to AC
// Good luck !
/*
ID: ckevin31
LANG: C++14
TASK: 
*/
inline void IO(string name){}
int32_t main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	IO("gangs");
	int n, m;
	cin >> n >> m;
	vector<int> cnt(m), res;
	for (int &i : cnt) cin >> i;

	int mx = m == 1 ? 0 : *max_element(cnt.begin()+1, cnt.end());

	// x is answer, y is other 1s that we need to put in the front of the answer
	int x = min(cnt[0], n - mx * 2), y = cnt[0] - x;
	// if number of numbers other than one is odd, then we need to eliminate at least one with them
	if ((n - cnt[0]) % 2 == 1 && y == 0) ++y, --x;

	if (x <= 0) return cout << "NO\n", 0;
	
	assert(x + y == cnt[0] && min(x, y) >= 0);


	// Fid : The id of element in stack, Fcnt : The number of element in stack
	
	int Fid = 0, Fcnt = 0, sum = n - x;

	// We need the info of cur_max_element, 
	// the number of elements left other than a bunch of ones
	vector<int> cntcnt(n + 1);
	for (int i = 1;i < m;++i) ++cntcnt[ cnt[i] ];
	int mxpointer = 1, cur_mx_cnt = n;

	auto put = [&](int id) {
		//cerr << "Put " << id+1 << endl;
		if (id == Fid || Fcnt == 0) 
			++Fcnt, Fid = id;
		else 
			--Fcnt;
		if (id) {
			--cntcnt[ cnt[id]-- ], --sum;
			if (cnt[id] >= 0)
				++cntcnt[ cnt[id] ];
		}
		res.pb(id);
	};

	auto get_most_freq = [&]() {
		while (cur_mx_cnt && cntcnt[ cur_mx_cnt ] == 0) --cur_mx_cnt;
		while (mxpointer < m && cnt[mxpointer] < cur_mx_cnt) ++mxpointer;
		return min(mxpointer, m - 1);
	};
	auto valid = [&](int put_id) {
		int g = get_most_freq();
		if (put_id == g || Fcnt == 0 || Fid == put_id) return true;
		return cnt[g] * 2 <= sum + Fcnt - 2;
	};

	for (int i = 0;i < y;++i) put(0);

	for (int i = 1;i < m;++i) {
		while (cnt[i]) {
			if (valid(i)) 
				put(i);
			else 
				put(get_most_freq());
		}
	}

	for (int i = 0;i < x;++i) put(0);

	cout << "YES\n" << x << '\n';
	for (int u : res)
		cout << u+1 << '\n';
}
