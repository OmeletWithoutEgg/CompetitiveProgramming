#include <stdio.h>

int add(int a, int b) {
    while(b) {
        int ta = a ^ b, tb = (a & b) << 1;
        a = ta, b = tb;
    }
    return a;
}

int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", add(a, b));

    return 0;
}

