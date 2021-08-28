// constant: eps
struct Real {
    ld x;
    Real() = default;
    Real(ld _x) : x(_x) {}
    ld operator()() const { return x; }
#define REFOP(type) Real & operator type(const Real &rhs){ return x type rhs.x, *this; }
    REFOP(+=) REFOP(-=) REFOP(*=) REFOP(/=)
#define VALOP(type) friend Real operator type(const Real &a, const Real &b){ return a.x type b.x; }
    VALOP(+) VALOP(-) VALOP(*) VALOP(/)
    Real operator-() { return -x; }
#define CMPOP(caneq, type) friend bool operator type(const Real &a, const Real &b) { \
        return abs(a.x - b.x) < eps ? caneq : a.x type b.x; \
    }
    CMPOP(false, <) CMPOP(false, >) CMPOP(true, ==) CMPOP(true, <=) CMPOP(true, >=) CMPOP(false, !=)
    friend istream & operator>>(istream &I, Real &f) {
        return I >> f.x;
    }
    friend ostream & operator<<(ostream &O, Real f) {
        return O << f.x;
    }
};
