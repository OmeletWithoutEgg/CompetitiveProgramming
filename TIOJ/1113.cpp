#include <bits/stdc++.h>

using namespace std;

int main(){
    char str[10] = "";
    scanf("%s",str);
    int l = strlen(str);
    sort(str,str+l);
    do{puts(str);}while(next_permutation(str,str+l));
    while(~scanf("%s",str)){
        int l = strlen(str);
        sort(str,str+l);
        puts("");
        do{puts(str);}while(next_permutation(str,str+l));
    }
    return 0;
}
