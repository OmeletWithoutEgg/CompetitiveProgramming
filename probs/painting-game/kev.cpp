#include<bits/stdc++.h>
#define pb emplace_back
using namespace std;
using ll = long long;
#ifdef KEV
#define DE(i, e) cerr << #i << ' ' << i << e
void debug(auto L, auto R) { while (L < R) cerr << *L << " \n"[L+1==R], ++L; }
#else
#define DE(...) 0
void debug(...) {}
#endif
#define int ll
const int maxn = 500010;
int n, m;
ll k;
int e, mod, w[maxn];
vector<int> st[maxn], ed[maxn];
ll res;
void add(ll &a, ll v) {
	a += v - mod;
	a += (a>>63) & mod;
}
void solve() {
	map<int, int> cnt, block;
	block[e] = block[0] = 1;
	cnt[e] = n;
	ll prof = 0;
	for (int i = n;i >= 1;--i) {
		for (int t : ed[i]) {
			int nxt = block.upper_bound(t)->first, lst = prev(block.lower_bound(t))->first;
			if (--block[t])  {
				continue;
			}
			block.erase(t);
			cnt[ nxt - lst] += i;
			cnt[ nxt - t ] -= i;
			cnt[ t - lst ] -= i;
		}
		for (int t : st[i]) {
			int nxt = block.upper_bound(t)->first, lst = prev(block.lower_bound(t))->first;
			if (++block[t] > 1) {
				continue;
			}
			//cerr << "[L M R] : " << lst << ' ' << t << ' ' << nxt << endl;
			cnt[ nxt - lst ] -= i;
			cnt[ nxt - t ] += i;
			cnt[ t - lst ] += i;
		}
		int f = next(block.begin())->first;
		assert(f > 0 && block[0] >= 1 && block.rbegin()->first == e);
		if (block[0] == 1)
			prof += f, --cnt[f];
	}
	vector<pair<int,int>> use;
	for (auto [f, s] : cnt)
		if (s) use.pb(f, s);
	reverse(use.begin(), use.end());

	auto sum = [&](ll a, ll b, ll t) {
		//cerr << "A B " << a << ' ' << b << endl;
		if (t&1) return ((a+b)/2 % mod) * t % mod;
		else return ((a+b) % mod) * (t / 2) % mod;
	};
	prof %= mod;
	//DE(prof, '\n');
	for (auto [f, s] : use) {
		assert(f > 0 && s > 0);
		if (k >= s) {
			add(res, sum(prof + f, prof + (ll)s * f, s));
			prof += s * f;
			k -= s;
		}
		else {
			add(res, sum(prof + f, prof + (ll)k * f, k));
			prof += k * f;
			k = 0;
			break;
		}
	}
        cerr << "mod = " << mod << endl;
	add(res, prof % mod * (ll) k % mod);
	cerr << "prof " << prof << endl;
	//res %= mod;
}
signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> n >> m >> k >> e >> mod;
	for (int i = 0;i < n;++i)
		cin >> w[i];
	sort(w, w+n);
	for (int t, l, r;m--;) {
		cin >> t >> l >> r;
		l = lower_bound(w, w+n, l) - w;
		r = prev(upper_bound(w, w+n, r)) - w;
		if (l > r) continue;
		//DE(t, ' '), DE(l, ' '), DE(r, '\n');
		st[r+1].pb(t);
		ed[l].pb(t);
	}
	solve();
	cout << res << '\n';
}
