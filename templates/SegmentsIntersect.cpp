#include <bits/stdc++.h>

using namespace std;

typedef __int128 C;
typedef complex<C> point;
struct Segment {
    point S, L;
    static bool valid(C p, C q) {
        if(q == 0) return p == 0;
        if(q < 0) q = -q, p = -p;
        return 0 <= p && p <= q;
    }
};
bool intersect(Segment A, point P) {
    // A.S + t A.L = P
    if(A.L == point{0}) return P == A.S;
    return (imag((P - A.S) * conj(A.L)) == 0) && Segment::valid(real((P - A.S) * conj(A.L)), real(A.L * conj(A.L)));
}
bool intersect(Segment A, Segment B) {
    // a + tLa = b + sLb
    // b - a = tLa - sLb
    // (b-a)conj(La) = t(La*conj(La)) - s(Lb*conj(La))
    // s = IM((a-b)conj(La)) / IM(Lb*conj(La))
    if(imag(A.L * conj(B.L)) == 0)
        return intersect(A, B.S) || intersect(A, B.S+B.L) || intersect(B, A.S) || intersect(B, A.S+A.L);
    return Segment::valid(imag((A.S - B.S) * conj(A.L)), imag(B.L * conj(A.L)))
        && Segment::valid(imag((B.S - A.S) * conj(B.L)), imag(A.L * conj(B.L)));
}
istream& operator>>(istream &I, point &p) {
    int64_t x, y;
    I >> x >> y;
    p = point(x, y);
    return I;
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int t;
    cin >> t;
    while(t--) {
        point p1, p2, q1, q2;
        cin >> p1 >> p2 >> q1 >> q2;
        Segment P {p1, p2 - p1};
        Segment Q {q1, q2 - q1};
        cout << (intersect(P, Q) ? "Yes\n" : "No\n");
    }
}
