#include <bits/stdc++.h>
#define N 500000

using namespace std;

signed main(){
    char a[N+1] = {};
    char b[N+1] = {};
    long long i,j,ia = 0,ib = 0;
    scanf("%s %s",a,b);
    for(i = 0;a[i] && a[i] != '.';i++)ia *= 10,ia += a[i] - '0';
    for(j = 0;b[j] && b[j] != '.';j++)ib *= 10,ib += b[j] - '0';
    if(ia != ib){
        puts(ia>ib?a:b);
    }else{
        while(a[i] && b[j] && a[i] == b[j])i++,j++;
        if(a[i] && b[j])puts(a[i] > b[j]?a:b);
        else puts(a[i]?a:b);
    }
}
