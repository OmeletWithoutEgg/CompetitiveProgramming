#include "assistant.h"
#include <bits/stdc++.h>
using namespace std;
 
const int maxn = 100025;
 
int scaffold[maxn];
int onScaffold[maxn];
 
void Assist(unsigned char *A, int N, int K, int R) {
    std::queue<int> q;
    for (int i = 0; i < K; i++) {
        onScaffold[i] = i;
        scaffold[i] = i;
        if (A[i])
            q.push(i);
    }

    for (int i = K; i < N; i++)
        onScaffold[i] = -1;

    for (int i = 0; i < N; i++) {
        int r = GetRequest();
        if (onScaffold[r] == -1) {
            int pos = q.front(); q.pop();
            onScaffold[scaffold[pos]] = -1;
            onScaffold[r] = pos;
            PutBack(scaffold[pos]);
            scaffold[pos] = r;
        }
        if (A[i+K])
            q.push(onScaffold[r]);
    }
}
