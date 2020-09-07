#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(...) qqbx(#__VA_ARGS__, __VA_ARGS__)
template <typename H, typename ...T> constexpr void qqbx(const char *s, const H &h, T &&...args) {
    for(; *s && *s != ','; ++s) if(*s != ' ') std::cerr << *s;
    std::cerr << " = " << h << (sizeof...(T) ? ", " : "\n");
    if constexpr(sizeof...(T)) qqbx(++s, args...);
}
#else
#define debug(...) ((void)0)
#define safe ((void)0)
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
typedef long long ll;

struct Point {
    int x, y;
    Point(int x=0, int y=0) : x(x), y(y) {}
    friend Point operator-(const Point &a, const Point &b) { return {a.x-b.x, a.y-b.y}; }
    friend ll operator^(const Point &a, const Point &b) { return 1LL * a.x * b.y - 1LL * a.y * b.x; }
    friend ll operator*(const Point &a, const Point &b) { return 1LL * a.x * b.x + 1LL * a.y * b.y; }
    friend bool operator<(const Point &a, const Point &b) {
        int qa = (a.y == 0 ? (a.x > 0 ? 0 : 2) : (a.y > 0 ? 1 : 3));
        int qb = (b.y == 0 ? (b.x > 0 ? 0 : 2) : (b.y > 0 ? 1 : 3));
        if(qa != qb) return qa < qb;
        return (a ^ b) > 0;
    }
    friend bool operator==(const Point &a, const Point &b) { return a.x==b.x && a.y == b.y; }
    friend ostream& operator<<(ostream &O, Point p) {
        return O << '(' << p.x << ',' << p.y << ')';
    }
};

Point slope(Point p) {
    int g = abs(__gcd(p.x, p.y));
    assert(g);
    p.x /= g, p.y /= g;
    if(p.y < 0 || (p.y == 0 && p.x < 0)) p.x = -p.x, p.y = -p.y;
    return p;
}

int ori(Point a, Point b, Point c) {
    ll C = (b-a) ^ (c-a);
    return C == 0 ? 0 : C>0 ? 1 : -1;
}
vector<Point> buildConvexHull(vector<Point> v) {
    vector<Point> L, U;
    sort(all(v), [](Point a, Point b) { return a.x!=b.x ? a.x<b.x : a.y<b.y; });
    for(auto p: v) {
        while(L.size() >= 2 && ori(L[L.size()-2], L[L.size()-1], p) >= 0) L.pop_back();
        L.push_back(p);
        while(U.size() >= 2 && ori(U[U.size()-2], U[U.size()-1], p) <= 0) U.pop_back();
        U.push_back(p);
    }
    for(int i = int(U.size())-2; i > 0; i--) L.pb(U[i]);
    return L;
}

bool inHull(const vector<Point> &v, Point p) {
    int n = v.size();
    if(n == 0) return false;
    if(n == 1) return p == v[0];
    if(n == 2) return ori(p, v[0], v[1]) == 0 && (v[0] - p) * (v[1] - p) <= 0;
    if(ori(p, v[0], v[1]) > 0 || ori(p, v[0], v[n-1]) < 0) return false;
    int x = 0;
    for(int s = 1<<__lg(n); s; s>>=1) if(x+s < n && ori(p, v[0], v[x+s]) <= 0) x += s;
    return ori(p, v[(x+1)%n], v[x]) >= 0;
}
 
// from Vovuh's submission
inline ll crossp(Point a, Point b) { return a^b; }
inline ll dotp(Point a, Point b) { return a*b; }
bool InsideHull(const vector<Point>& hull, Point p, int& first, int& last) {
  first = last = 0;
  if (hull.size() == 1) return p == hull[0];
  int base = 0;
  if (crossp(hull[0]-p, hull[1]-p) == 0) {
    if (hull.size() == 2) {
      return dotp(p-hull[0], hull[1]-hull[0]) >= 0 &&
             dotp(p-hull[1], hull[0]-hull[1]) >= 0;
    }
    if (p == hull[1]) return true;
    base++;
  }
 
  int H = hull.size();
  int sgn = (crossp(hull[base%H]-p, hull[(base+1)%H]-p) > 0) ? 1 : -1;
  assert(crossp(hull[base%H]-p, hull[(base+1)%H]-p) != 0);
 
  // base->base+1 is strictly up/down.  Find first strictly down/up edge.
  // Iff the point's outside the hull, there must be one.
  int lo = base+1, hi = base + hull.size()-1;
  while (hi > lo) {
    int mid = (lo+hi)/2;
    if (crossp(hull[mid%H]-p, hull[(mid+1)%H]-p) * sgn < 0) {
      hi = mid;  // On downward/upward curve.
    } else if (crossp(hull[mid%H]-p, hull[(base+1)%H]-p) * sgn > 0) {
      hi = mid;  // On second upward/downward curve.
    } else {
      lo = mid+1;
    }
  }
  if (crossp(hull[lo%H]-p, hull[(lo+1)%H]-p) * sgn >= 0) return true;
 
  (sgn > 0 ? last : first) = base = lo%H;
  sgn = -sgn;
 
  lo = base+1, hi = base + hull.size()-1;
  while (hi > lo) {
    int mid = (lo+hi)/2;
    if (crossp(hull[mid%H]-p, hull[(mid+1)%H]-p) * sgn < 0) {
      hi = mid;  // On upward/downward curve.
    } else if (crossp(hull[mid%H]-p, hull[(base+1)%H]-p) * sgn > 0) {
      hi = mid;  // On second downward/upward curve.
    } else {
      lo = mid+1;
    }
  }
 
  (sgn > 0 ? last : first) = lo%H;
  return false;
}

void solve(int n) {
    int S = 0;
    vector<Point> cv, Q;
    for(int i = 0; i < n; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        if(c)
            cv.pb(a, b), ++S;
        else
            Q.pb(a, b);
    }
    if(S <= 1) return cout << S << '\n', void();
    cv = buildConvexHull(cv);
    /* for(auto p: cv) cerr << p << ','; */
    /* cerr << '\n'; */
    int sum = 0, mn = 1e9;
    map<Point,array<int,2>> mp;
    for(auto p: Q) {
        if(inHull(cv, p)) {
            ++sum;
            debug(p);
        } else {
            int a, b;
            assert(!InsideHull(cv, p, a, b));
            Point da = slope(cv[a] - p);
            Point db = slope(cv[b] - p);
            debug(da, db);
            if(da < db) {
                mp[da][0] += 1;
                mp[db][1] -= 1;
            } else if(db < da) {
                mp[da][0] += 1;
                mp[db][1] -= 1;
                sum += 1;
            }
        }
    }
    mn = sum;
    for(auto [_, v]: mp) {
        debug(_, v[0], v[1]);
        sum += v[0];
        mn = min(mn, sum);
        sum += v[1];
        mn = min(mn, sum);
    }
    cout << S+mn << '\n';
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    solve(n);
}
