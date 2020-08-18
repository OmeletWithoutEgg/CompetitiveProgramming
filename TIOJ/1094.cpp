#include <bits/stdc++.h>

using namespace std;

const int K = 20;

int n,v;
int bas[K];
void ins(int x) {
    for(int i = K-1; i >= 0; i--) if(x & (1<<i)) {
        if(bas[i]) x ^= bas[i];
        else {
            bas[i] ^= x;
            break;
        }
    }
    /*for(int i = 0; i < K; i++)
        for(int j = i+1; j < K; j++)
            if(bas[j] & (1<<i)) bas[j] ^= bas[i];*/
}
int query() {
    int res = 0;
    for(int i = K-1; i >= 0; i--) {
        if((res ^ bas[i]) & (1<<i)) res ^= bas[i];
    }
    return res;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    while(cin >> n && n) {
        for(int i = 0; i < K; i++) bas[i] = 0;
        for(int i = 0; i < n; i++) {
            cin >> v;
            ins(v);
        }
        cout << query() << '\n';
    }
}
