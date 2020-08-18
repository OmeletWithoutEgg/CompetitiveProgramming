#include <bits/stdc++.h>

using namespace std;

int a[1023],n,w;
bool check(int x) {
    int block = 0, sum = 0;
    //cout << "d=" << d << '\n';
    for(int i = 0; i < n; i++) {
        if(a[i] > x) return false;
        if(sum+a[i] > x) block++, sum = a[i];
        else sum += a[i];
        //cout << "sum=" << sum << '\n';
        //cout << "block=" << block << '\n';
    }
    return block<=w;
}
signed main(){
    while(cin >> n >> w,n&&w) {
        for(int i = 0; i < n; i++) cin >> a[i];
        int l = 0, r = 1000000, mid;
        while(l < r) {
            mid = l+(r-l>>1);
            if(check(mid)) r = mid;
            else l = mid+1;
        }
        cout << l << '\n';
    }
}

/*
6 2
5 2 3 4 7 1
*/
