#include <iostream>
#include <bitset>

using namespace std;

long long prs[10001] = {};
int plen = 0;

void buildPr(){
    bitset<65536> notP(0);
    for(long long n = 2;n < 65536;n++){
        if(!notP[n])prs[plen++] = n;
        for(int i = 0;i < plen;i++){
            if(n * prs[i] < 65536)notP[n * prs[i]] = true;
            else break;
            if(n % prs[i] == 0)break;
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, res;
    int i;
    bool notF;
    buildPr();
    /*
    cin >> n;
    for(int i = 0;i < plen && n > 1;i++){
        int p = 0;
        while(n % prs[i] == 0)n /= prs[i],p++;
        if(n == 1)cout << prs[i] << endl;
        else if(p == 1)cout << prs[i] << " * ";
        else if(p > 1)cout << prs[i] << '^' << p << " * ";
    }*/
    while(cin >> n,n){
        res = n;
        for(int i = 0;i < plen && prs[i] <= n;i++){
            notF = true;
            while(n % prs[i] == 0)n /= prs[i],notF = false;
            if(!notF)res = res * (prs[i] - 1) / prs[i];
        }
        if(n > 1)res = res * (n - 1) / n;
        cout << res << endl;
    }
    return 0;
}
