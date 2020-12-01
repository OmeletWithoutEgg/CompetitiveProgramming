#include <bits/stdc++.h>

using namespace std;

int p[1000002] = {};
int main(){
    int t, n, x, v,face, max_d;
    cin >> t;
    while(t--){
        cin >> n >> x >> v;
        for(int i = 0;i < n;i++)cin >> p[i] >> face,(face?p[i] = (p[i] - v + x) % x:p[i] = (p[i] + v + x) % x);
        sort(p,p + n);
        for(int i = 0;i < n;i++)cout << p[i] << ' ';
        cout << endl;

        max_d = p[0] + x - p[n - 1];
        for(int i = 0;i < n - 1;i++)max_d = max(max_d,p[i + 1] - p[i]);
        cout << max_d << endl;
    }
    return 0;
}
