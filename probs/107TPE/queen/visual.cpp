#include "jngen.h"
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

int ori(Point a, Point b, Point c) {
    // AB ^ AC
    b -= a;
    c -= a;
    long long cross = b % c;
    return cross ? (cross < 0 ? -1 : 1) : 0;
}
std::vector<Point> convexHull(std::vector<Point> sorted) {
    std::vector<Point> L, U;
    for(auto p: sorted) {
        while(L.size() >= 2 && ori(L[L.size()-2], L.back(), p) <= 0) L.pop_back();
        L.push_back(p);
    }
    std::reverse(sorted.begin(), sorted.end());
    for(auto p: sorted) {
        while(U.size() >= 2 && ori(U[U.size()-2], U.back(), p) <= 0) U.pop_back();
        U.push_back(p);
    }
    L.pop_back();
    U.pop_back();
    for(auto p: U) L.push_back(p);
    for(auto p: L)
        std::cerr << p << '\n';
    return L;
}
int main() {
    int n;
    std::cin >> n;
    std::vector<Point> v(n);
    for(int i = 0; i < n; i++) {
        int x, y;
        std::cin >> x >> y;
        v[i] = Point(x, y);
    }
    std::sort(v.begin(), v.end());
    Drawer d;
    d.polygon(convexHull(std::vector<Point>(v.begin(), v.begin() + n/2)));
    d.polygon(convexHull(std::vector<Point>(v.begin()+n/2, v.end())));
    d.dumpSvg("polygon.svg");
}
