#include <bits/stdc++.h>
#define pb push_back
#define mkp make_pair

using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

int stoi(const char *s){
    int res = 0;
    for(;*s;s++)
        if('0' <= *s && *s <= '9')res *= 10,res += *s - '0';
    return res;
}
int main(){
    int q;
    char a[100]="",b[100]="",o[2]="";
    scanf("%d",&q);
    while(q--){
        scanf("%[^+*/%-]%[+*/%-]%s",a,o,b);
        int res;
        switch(*o){
        case '+':res = stoi(a) + stoi(b);break;
        case '-':res = stoi(a) - stoi(b);break;
        case '*':res = stoi(a) * stoi(b);break;
        case '/':res = stoi(a) / stoi(b);break;
        case '%':res = stoi(a) % stoi(b);break;
        }
        printf("%d\n\n",res);
    }
    return 0;
}

