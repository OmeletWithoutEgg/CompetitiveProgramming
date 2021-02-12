#include "advisor.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100025;
 
vector<int> last[maxn];
int scaffold[maxn];
int onScaffold[maxn];
int tt[maxn];

void ComputeAdvice(int *C, int N, int K, int M) {
    for (int i = 0; i < K; i++)
        scaffold[i] = i, onScaffold[i] = i;
    for (int i = K; i < N; i++)
        onScaffold[i] = -1;
    for (int i = 0; i < N; i++)
        last[i].push_back(maxn);
    for (int i = N-1; i >= 0; i--)
        last[C[i]].push_back(i);

    set<pair<int,int>> st;
    for (int i = 0; i < K; i++)
        st.insert({ -last[i].back(), i }), tt[i] = i;

    vector<bool> garbage(N + K);
    for (int i = 0; i < N; i++) {
        int req = C[i];

        if (onScaffold[req] == -1) {
            last[C[i]].pop_back();
            int pos = st.begin() -> second;
            garbage[tt[pos]] = true;
            st.erase(st.begin());
            onScaffold[req] = pos;
            onScaffold[scaffold[pos]] = -1;
            scaffold[pos] = req;
            tt[pos] = i + K;
            st.insert({ -last[C[i]].back(), pos });
        } else {
            int pos = onScaffold[C[i]];
            st.erase({ -last[C[i]].back(), pos });
            last[C[i]].pop_back();
            tt[pos] = i + K;
            st.insert({ -last[C[i]].back(), pos });
        }
    }

    for (int i = 0; i < N+K; i++)
        WriteAdvice(garbage[i]);
}
