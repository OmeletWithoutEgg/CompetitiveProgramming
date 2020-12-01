#include <bits/stdc++.h>

using namespace std;

int n,m,sum;
int sumX[127],sumY[127];
int stu[127][127] = {};
signed main(){
    ios_base::sync_with_stdio(0),cin.tie(0);
    cin >> n >> m;
    for(int i = 1;i <= n;i++)
        for(int j = 1;j <= m;j++)
            cin >> stu[i][j], sumX[i] = stu[i][j], sumY[j] += stu[i][j], sum += stu[i][j];
    int mid = sum+1>>1, i = 1, j = 1;
    while(i < n && sumX[i]<mid) sumX[i+1] += sumX[i], i++;
    while(j < m && sumY[j]<mid) sumY[j+1] += sumY[j], j++;
    cout << i << ' ' << j;
}
