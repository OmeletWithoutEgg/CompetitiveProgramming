#include <bits/stdc++.h>
#define ll long long
#define All(x) x.begin(), x.end()
#define pb emplace_back
#define pii pair<int,int>
#define ff first
#define ss second
using namespace std;
#define debug(args...) kout("[ " + string(#args) + " ]", args)
void kout() { cerr << endl; }
template <class T, class ...U> void kout(T a, U ...b) { cerr << a << ' ',kout(b...); }
template <class T> void pary(T L, T R) { while (L != R) cerr << *L << " \n"[++L==R]; }

const int MAXN = 500000;
int N, M, len;
pii pts[MAXN+1];
vector <tuple<int,int,int>> pos;
vector <pii> ord;
int a, w, h;

pii operator - (pii a, pii b) {
	return pii(a.ff - b.ff, a.ss - b.ss);
}

int cnt = 0;
class Seg {
	private:
		vector <int> arr[MAXN*4+5];
		inline bool comp(pii a, pii b) {
			return (ll) a.ss * b.ff >= (ll) a.ff * b.ss;
		}
		inline bool cross(int i, int j, int k) {
			return comp(pts[k] - pts[i], pts[j] - pts[i]);
		}
#define v arr[now]
		void pull(int now) {
			vector <int> tmp(arr[now*2].size() + arr[now*2+1].size());
			merge(All(arr[now*2]), All(arr[now*2+1]), tmp.begin(), [&](int a, int b) {
				return pts[a].ff < pts[b].ff;
			});
			v.pb(tmp[0]), v.pb(tmp[1]);
			for (int i = 2; i < tmp.size(); i++) {
				while (v.size() > 1 && cross(v[v.size()-2], v[v.size()-1], tmp[i])) {
					v.pop_back();
				}
				v.pb(tmp[i]);
			}
		}
		int find(int now, pii sl) {
			int l = 1, r = v.size()-1;
			if (comp(sl, pts[v[1]] - pts[v[0]])) return v[0];
			while (l < r) {
				int mid = (l + r + 1) >> 1;
				if (comp(sl, pts[v[mid]] - pts[v[mid-1]]))
					r = mid - 1;
				else
					l = mid;
			}
			return v[l];
		}
#undef v
	public:
		void build(int now=1, int l=1, int r=len) {
			if (l == r) {
				arr[now].pb(ord[l-1].ss);
				return;
			}
			int mid = l + r >> 1;
			build(now*2  , l, mid);
			build(now*2+1,mid+1,r);
			pull(now);
			return;
		}
		int qry(int ql, int qr, pii sl, int now=1, int l=1, int r=len) {
			if (ql <= l && r <= qr) {
				return l == r ? arr[now][0] : find(now, sl);
			} else if (l > qr || r < ql) return -1;
			int mid = l + r >> 1;
			int L = qry(ql, qr, sl, now*2  , l, mid);
			int R = qry(ql, qr, sl, now*2+1,mid+1,r);
			if (L == -1) return R;
			if (R == -1) return L;
			return comp(sl, pts[R] - pts[L]) ? L : R;
		}
} seg;

void build() {
	for (int i = 1; i <= N; i++) {
		auto [x, y] = pts[i];
		pos.pb(x, y, i);
	}
	sort(All(pos));
	for (int i = 0; i < pos.size(); i++) {
		auto [x, y, id] = pos[i];
		if (i+1 < pos.size() && get<0>(pos[i+1]) == x) continue;
		ord.pb(x, id);
	}
	len = ord.size();
	seg.build();
}

int solve(int a, int w, int h) {
	int L = lower_bound(All(ord), pii(a, 0)) - ord.begin() + 1;
	int R = upper_bound(All(ord), pii(a+w, N+1)) - ord.begin();
	if (L <= R) return seg.qry(L, R, pii(w, h));
	return -1;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0);
	cin >> N;
	for (int i = 1; i <= N; i++) {
		auto &[x, y] = pts[i];
		cin >> x >> y;
	}
	build();
	cin >> M;
	for (int i = 1; i <= M; i++) {
		cin >> a >> w >> h;
		cout << solve(a, w, h) << '\n';
	}
	return 0;
}
