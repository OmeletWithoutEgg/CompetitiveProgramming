#pragma g++ optimize("Ofast")
#include <cstdio>
#include <cstring>

const char star[201] = "********************************************************************************************************************************************************************************************************";
char s[201];
int main() {
    memset(s, ' ', sizeof s);
    int n;
    while(scanf("%d", &n) && n) {
        s[n-1] = '*';
        for(register int i = 0, j = n*2-2; i!=j; i++, j--) {
            s[i] = s[j] = '*';
            s[j+1] = '\0';
            puts(s);
            s[i] = s[j] = s[j+1] = ' ';
        }
        puts(star+200-(n*2-1));
        for(register int i = n-2, j = n; i>=0; i--, j++) {
            s[i] = s[j] = '*';
            s[j+1] = '\0';
            puts(s);
            s[i] = s[j] = s[j+1] = ' ';
        }
        s[n-1] = ' ';
    }
}
