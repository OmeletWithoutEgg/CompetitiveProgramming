#include <bits/stdc++.h>
#ifdef local
#define safe std::cerr<<__PRETTY_FUNCTION__<<" line "<<__LINE__<<" safe\n"
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    (std::cerr << "(" << s << ") = (", ..., (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#else
#define debug(...) (void(0))
#define safe (void(0))
#endif // local
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
template <typename T> using min_heap = std::priority_queue<T, vector<T>, greater<T>>;
using ll = long long;
const int N = 500025, inf = 1e9;
const ll INF = 1e18;

void brucia(int n, vector<int> &M, vector<int> &B, vector<ll> &T) {
    min_heap<pair<ll,int>> toL, toR;
    int curL = M[0], curR = M[0];
    auto add = [&](int i, ll t) {
        T[i] = t;
        if(B[i] < M[i]) {
            toL.push({ M[i] + T[i], i });
            curL = min(curL, B[i]);
        } else {
            toR.push({ T[i] - M[i], i });
            curR = max(curR, B[i]);
        }
    };
    auto dist = [&](int i, int j) -> ll {
        int l = M[i], r = B[i];
        if(l > r) swap(l, r);
        if(M[j] < l || M[j] > r) return INF;
        return abs(M[i] - M[j]);
    };
    vector<pair<int,int>> bigger, smaller;
    for(int i = 0; i < n; i++) {
        T[i] = -1;
        if(M[i] == M[0]) {
            add(i, 0);
        } else if(M[i] > M[0]) bigger.pb(M[i], i);
        else if(M[i] < M[0]) smaller.pb(M[i], i);
    }
    sort(all(bigger), greater<>());
    sort(all(smaller));
    while(toL.size() || toR.size()) {
        int nearLeft = smaller.size() ? smaller.back().second : -1;
        int nearRight = bigger.size() ? bigger.back().second : -1;
        if(nearLeft != -1) {
            while(toL.size() && B[toL.top().second] > M[nearLeft]) toL.pop();
        }
        if(nearRight != -1) {
            while(toR.size() && B[toR.top().second] < M[nearRight]) toR.pop();
        }
        int toLeft = toL.size() ? toL.top().second : -1;
        int toRight = toR.size() ? toR.top().second : -1;
        debug(toLeft, toRight);
        ll TLeft = ~toLeft && ~nearLeft ? T[toLeft] + dist(toLeft, nearLeft) : INF;
        ll TRight = ~toRight && ~nearRight ? T[toRight] + dist(toRight, nearRight) : INF;
        debug(toLeft, nearLeft, TLeft);
        debug(toRight, nearRight, TRight);
        if(TLeft >= INF && TRight >= INF) break;
        if(TLeft < TRight) {
            add(nearLeft, TLeft);
            smaller.pop_back();
        } else {
            add(nearRight, TRight);
            bigger.pop_back();
        }
        safe;
    }
}
#ifdef local
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> M(n), B(n);
    vector<ll> T(n);
    for(int i = 0; i < n; i++) cin >> M[i] >> B[i];
    brucia(n, M, B, T);
    for(int i = 0; i < n; i++) cout << T[i] << ' ';
    cout << '\n';
}
#endif // local
