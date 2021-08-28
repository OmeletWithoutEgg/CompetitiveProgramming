using coord_t = int;
using Real = double;
using Point = std::complex<coord_t>;
int sgn(coord_t x) {
    return (x > 0) - (x < 0);
}
coord_t dot(Point a, Point b) {
    return real(conj(a) * b);
}
coord_t cross(Point a, Point b) {
    return imag(conj(a) * b);
}
int ori(Point a, Point b, Point c) {
    return sgn(cross(b - a, c - a));
}
bool operator<(const Point &a, const Point &b) {
    return real(a) != real(b) ? real(a) < real(b) : imag(a) < imag(b);
}
bool argCmp(Point a, Point b) {
    // -1 / 0 / 1 <-> < / == / > (atan2)
    int qa = (imag(a) == 0 ? (real(a) < 0 ? 3 : 1) : (imag(a) < 0 ? 0 : 2));
    int qb = (imag(b) == 0 ? (real(b) < 0 ? 3 : 1) : (imag(b) < 0 ? 0 : 2));
    if (qa != qb)
        return sgn(qa - qb);
    return sgn(cross(b, a));
}
template <typename V> Real area(const V & pt) {
    coord_t ret = 0;
    for (int i = 1; i + 1 < (int)pt.size(); i++)
        ret += cross(pt[i] - pt[0], pt[i+1] - pt[0]);
    return ret / 2.0;
}
