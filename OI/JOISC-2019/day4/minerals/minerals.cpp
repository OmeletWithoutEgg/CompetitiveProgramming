#include "minerals.h"
#include <bits/stdc++.h>
using namespace std;

const double e = exp(1);
 
int cur = 0;
void dq(vector<int> A, vector<int> B, bool flag) {
    assert(A.size() == B.size());
    if (A.empty()) return;
    if (A.size() == 1) {
        // cerr << "cand.size() = " << cand.size() << endl;
        Answer(A[0], B[0]);
        return;
    }
    int m = max<int>(1,  A.size() / e);
    for (int i = 0; i < m; i++)
        cur = Query(A[i]);
    vector<int> L, R;
    for (int x: B) {
        if (L.size() == m) {
            R.push_back(x);
            continue;
        }
        if (R.size() == A.size() - m) {
            L.push_back(x);
            continue;
        }
        int now = Query(x);
        if ((now == cur) ^ flag) {
            L.push_back(x);
        } else {
            R.push_back(x);
        }
        cur = now;
    }
    dq(vector<int>(A.begin(), A.begin() + m), L, !flag);
    dq(vector<int>(A.begin() + m, A.end()), R, flag);
}
void Solve(int N) {
    vector<int> A, B;
    int cur = 0;
    for (int i = 1; i <= N*2; i++) {
        int q = Query(i);
        if (q == cur) {
            A.push_back(i);
        } else {
            B.push_back(i);
        }
        cur = q;
    }
    dq(A, B, true);
    // for (int i = 1; i <= 50; i++) cerr << i << ' ' << f(i) << endl;
    /*
    for (int i = 1; i <= N*2; i++) {
        Query(i);
        for (int j = 1; j < i; j++) {
            if (Query(j) == 1)
                Answer(i, j);
            Query(j);
        }
        Query(i);
    }
    */
}
