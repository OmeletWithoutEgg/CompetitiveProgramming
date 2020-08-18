#include <cstdio>
#include <cmath>
const double PI = acos(-1);

double x,y,r;
signed main() {
    while(~scanf("%lf%lf%lf", &x, &y, &r)) {
        if(y <= -r) puts("0.00");
        else if(y >= r) printf("%.2lf\n", r*r*PI);
        else {
            double h = sqrt(r*r - y*y);
            double theta = acos(-y/r);
            printf("%.2lf\n", r*r*theta + y*h);
        }
    }
}

