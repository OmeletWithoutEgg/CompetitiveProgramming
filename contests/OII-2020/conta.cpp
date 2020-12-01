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
using ll = long long;
template <typename T> using max_heap = priority_queue<T>;
const int N = 500025, inf = 1e9;

int conta(int n, vector<int> &A, vector<int> &B, vector<int> &C) {
    vector<int> u;
    for(int x: A) u.pb(x);
    for(int x: B) u.pb(x);
    for(int x: C) u.pb(x);
    sort(all(u));
    u.erase(unique(all(u)), u.end());
    for(int &x: A) x = int(lower_bound(all(u), x) - u.begin());
    for(int &x: B) x = int(lower_bound(all(u), x) - u.begin());
    for(int &x: C) x = int(lower_bound(all(u), x) - u.begin());
    vector<pair<int,int>> pr;
    {
        int j;
        vector<int> cnt(u.size());
        for(j = 0; j < n; j++) {
            if(cnt[C[j]] != 0) break;
            ++cnt[C[j]];
        }
        pr.pb(0, j);
        for(int i = 0; i < n; i++) {
            while(j > 0 && cnt[B[i]] != 0) --cnt[C[--j]];
            if(cnt[B[i]] != 0) break;
            ++cnt[B[i]];
            pr.pb(i+1, j);
        }
        safe;
        for(auto [a, b]: pr) debug(a, b);
    }
    int ans = 0;
    {
        vector<int> cnt(u.size());
        vector<int> posB(u.size(), n);
        vector<int> posC(u.size(), n);
        for(int i = n-1; i >= 0; i--) posB[B[i]] = i;
        for(int i = n-1; i >= 0; i--) posC[C[i]] = i;
        for(auto [a, b]: pr) ans = max(ans, a+b);

        max_heap<pair<int,int>> pqB, pqC;
        multiset<int, greater<int>> ms, msB, msC;
        int BC = 0;

        auto add = [&](pair<int,int> p) {
            if(p.first == -1 && p.second == -1) return;
            if(p.first == -1) msC.insert(p.second);
            else if(p.second == -1) msB.insert(p.first);
            else ++BC;
        };
        auto del = [&](pair<int,int> p) {
            if(p.first == -1 && p.second == -1) return exit(3), void();
            if(p.first == -1) msC.erase(msC.find(p.second));
            else if(p.second == -1) msB.erase(msB.find(p.first));
            else ms.erase(ms.find(p.first + p.second));
        };

        for(int i = 0; i < int(pr.size()); i++) {
            auto [b, c] = pr[i];
            pqB.push({ b, i });
            pqC.push({ c, i });
            ms.insert(b+c);
        }
        int LB = n, LC = n;
        for(int i = 0; i < n; i++) {
            if(cnt[A[i]] != 0) break;
            ++cnt[A[i]];
            LB = min(LB, posB[A[i]]);
            LC = min(LC, posC[A[i]]);
            // delete b < LB
            // delete c < LC
            while(pqB.size() && pqB.top().first > LB) {
                int id = pqB.top().second; pqB.pop();
                del(pr[id]);
                pr[id].first = -1;
                add(pr[id]);
            }
            while(pqC.size() && pqC.top().first > LC) {
                int id = pqC.top().second; pqC.pop();
                del(pr[id]);
                pr[id].second = -1;
                add(pr[id]);
            }
            if(ms.size()) ans = max(ans, i+1 + *ms.begin());
            if(msB.size()) ans = max(ans, i+1 + *msB.begin() + LC);
            if(msC.size()) ans = max(ans, i+1 + *msC.begin() + LB);
            if(BC) ans = max(ans, i+1 + LB + LC);
        }
    }
    return ans;
}
#ifdef local
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int n;
    cin >> n;
    vector<int> A[3];
    for(int j = 0; j < 3; j++) {
        A[j].resize(n);
        for(int i = 0; i < n; i++) cin >> A[j][i];
    }
    cout << conta(n, A[0], A[1], A[2]) << '\n';
}
#endif // local
