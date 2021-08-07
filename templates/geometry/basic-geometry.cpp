using coord_t = int;
using point = complex<coord_t>;
coord_t dot(point a, point b) {
    return real(a * conj(b));
}
coord_t cross(point a, point b) {
    return imag(a * conj(b));
}
bool ori(point a, point b, point c) {
    coord_t C = cross(b - a, c - a);
    return (C > 0) - (C < 0);
}
bool operator<(const point &a, const point &b) {
    return a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag();
}
bool argCmp(point a, point b) {
    int qa = a < point{0};
    int qb = b < point{0};
    if (qa != qb) return qa > qb;
    return cross(a, b) > 0;
}
