#include <iostream>
#include <utility>
#include <algorithm>
#include <set>
using namespace std;

struct mode {
    int t, a, b;
    bool operator<(const mode &x) const {
        if (a != x.a) return a < x.a;
        return b < x.b;
    }
}event[500005];

bool cmp(mode x, mode y) {
    return x.t > y.t;
}

pair<int, int> profit[1000000];
int arr[500005];
set<mode> seg;

int main () {
    int n, m, t, d, top = 0, ans = 0;
    long long k;
    cin >> n >> m >> k >> t >> d;
        seg.insert(mode{t, 1, n});
    for (int i = 1; i <= n; ++i)
        cin >> arr[i];
    sort(arr + 1, arr + n + 1);
    for (int i = 1; i <= m; ++i) {
        cin >> event[i].t >> event[i].a >> event[i].b;
        event[i].a = lower_bound(arr + 1, arr + n + 1, event[i].a) - arr;
        event[i].b = upper_bound(arr + 1, arr + n + 1, event[i].b) - arr;
    }
    sort(event + 1, event + m + 1, cmp);
    for (int i = 1; i <= m; ++i) {
        if (event[i].a > n || event[i].a >= event[i].b)
            continue;
        auto p = seg.lower_bound(mode{0, event[i].a, event[i].a});
        if (p != seg.begin() && prev(p) -> b >= event[i].a) {
            mode tmp = *prev(p);
            seg.erase(prev(p));
            if (tmp.b < event[i].b) {
                profit[top++] = make_pair(tmp.t - event[i].t, tmp.b - event[i].a);
                tmp.b = event[i].a - 1, seg.insert(tmp);
            }
            else {
                profit[top++] = make_pair(tmp.t - event[i].t, event[i].b - event[i].a);
                mode tmp2 = tmp;
                tmp.b = event[i].a - 1, seg.insert(tmp);
                tmp2.a = event[i].b, seg.insert(tmp2);
                goto con;
            }
        }
        while (p != seg.end() && p -> b < event[i].b)
            profit[top++] = make_pair(p -> t - event[i].t, p -> b - p -> a + 1), p = seg.erase(p);
        if (p != seg.end() && p -> a < event[i].b) {
            mode tmp = *p;
            profit[top++] = make_pair(p -> t - event[i].t, event[i].b - p -> a), p = seg.erase(p);
            tmp.a = event[i].b, seg.insert(tmp);
        }
        con:
        --event[i].b, seg.insert(event[i]);
    }
    for (auto i : seg)
        ans = ((long long)i.t * (i.b - i.a + 1) + ans) % d;
    ans = (k % d * ans) % d;
    sort(profit, profit + top, greater<pair<int, int>>());
    for (int i = 0; i < top && k; ++i)
        if (k >= profit[i].second)
            if (profit[i].second & 1)
                ans = ((long long)(k * 2 - profit[i].second + 1) / 2 * profit[i].first % d * profit[i].second + ans) % d, k -= profit[i].second;
            else
                ans = ((long long)(k * 2 - profit[i].second + 1) * profit[i].first % d * (profit[i].second / 2) + ans) % d, k -= profit[i].second;
        else
            if (k & 1)
                ans = ((long long)(k + 1) / 2 * profit[i].first % d * k + ans) % d, k = 0;
            else
                ans = ((long long)profit[i].first * k / 2 % d * (k + 1) + ans) % d, k = 0;
    cout << ans << "\n";
}
