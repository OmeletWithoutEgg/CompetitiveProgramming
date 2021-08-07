#include <bits/stdc++.h>
using namespace std;


namespace Interactor {
random_device rd;
mt19937 rng(rd());
int nextRand(int l, int r) {
    return uniform_int_distribution<int>(l, r-1)(rng);
}
const int K = 1;
int max_infect;
set<int> infect;
bool has[1000000];
int cost;
int cnt;
bool ask(int l, int r) {
    cost += r - l;
    cnt += 1;
    /*
    for (int i = l; i < r; i++)
        if (has[i])
            return true;
    return false;
    */
    auto it = infect.lower_bound(l);
    if (it != infect.end() && *it < r)
        return true;
    if (r - l >= K && infect.size() < max_infect) {
        int x = nextRand(l, r);
        infect.insert(x);
        return true;
    } else {
        return false;
    }
    cout << "? " << r - l;
    for (int i = l; i < r; i++)
        cout << ' ' << i+1;
    cout << '\n';
    int res;
    cin >> res;
    return res;
}
void init(int n, double p) {
    max_infect = floor(n * p);

    for (int i = 0; i < n; i++)
        has[i] = (i < max_infect);
    reverse(has, has+n);

    infect.clear();
    cost = 0;
    cnt = 0;
}
}

const double p = 0.05;
using Interactor::ask;
vector<int> ans;
void GBSA(int n, int d) {
    while (d > 0) {
        if (n <= d * 2 - 2) {
            for (int i = 0; i < n; i++) {
                if (ask(i, i+1))
                    ans.push_back(i);
            }
            return;
        }

        int l = n - d + 1;
        int alpha = floor(log2((double)l / d));
        int s = 1 << alpha;
        cerr << alpha << endl;
        if (ask(n - s, n) == false) {
            n -= s;
            continue;
        }
        int pos = n;
        while (s >>= 1) {
            if (ask(pos - s, n) == false) {
                pos -= s;
            }
        }
        // [pos, n) : safe
        // pos-1: infect
        n = pos - 1;
        ans.push_back(n);
        --d;
    }
}
int main() {
    srand(time(0));
    int n;
    n = 20000;
    Interactor::init(n, p);
    GBSA(n, ceil(n * p));
    cerr << n*p << endl;
    cerr << ans.size() << endl;
    /*
    cout << "! " << ans.size();
    for (int x: ans)
        cout << ' ' << x+1;
    cout << '\n';
    */
    cerr << Interactor::cost << endl;
    cerr << Interactor::cnt << endl;
}
