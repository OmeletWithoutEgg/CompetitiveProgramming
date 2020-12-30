#include <bits/stdc++.h>
#define debug(args...) qqbx(#args, args)
template <typename ...T> void qqbx(const char *s, T ...args) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << args << (--cnt ? ", " : ")\n")));
}
#define pb emplace_back
#define all(v) begin(v),end(v)

using namespace std;
using ll = long long;
using ld = double;
using cl = complex<ll>;
using cd = complex<ld>;

bool parallel(complex<ll> a, complex<ll> b) { return (a * conj(b)).imag() == 0; }
template <typename ...T> void print(T ...a) {
    int cnt = sizeof...(T);
    ((cout << a.real() << ' ' << a.imag() << (--cnt ? ' ' : '\n')), ...);
}
cd toCd(cl x) { return cd(x.real(), x.imag()); }
struct Line {
    complex<ll> a, b;
    // at + b, 0 <= t <= 1
    friend istream &operator>>(istream &I, Line &L) {
        int x1, y1, x2, y2;
        I >> x1 >> y1 >> x2 >> y2;
        L.b = complex<ll>(x1, y1);
        L.a = complex<ll>(x2, y2) - L.b;
        return I;
    }
    bool contain(cl p) {
        return parallel(p - b, a) && [](ld x){return 0 <= x && x <= 1; }((toCd(p - b) / toCd(a)).real());
    }
};
void solve() {
    Line L1, L2;
    cin >> L1 >> L2;
    if(L1.a == cl(0) && L2.a == cl(0)) {
        if(L1.b == L2.b) {
            print(toCd(L1.b));
        } else {
            cout << "none\n";
        }
    } else if(L1.a == cl(0)) {
        if(L2.contain(L1.b)) {
            print(toCd(L1.b));
        } else {
            cout << "none\n";
        }
    } else if(L2.a == cl(0)) {
        if(L1.contain(L2.b)) {
            print(toCd(L2.b));
        } else {
            cout << "none\n";
        }
    } else if(parallel(L1.a, L2.a)) {
        if(parallel(L1.b - L2.b, L1.a)) {
            // L1.a * t + L1.b
            //  = L2.a * s + L2.b
            //  s = (L1.a * t + L1.b - L2.b) / L2.a
            //  s = a t + b, 0 <= s <= 1 -> -b <= s <= 1-b
            ld a = (toCd(L1.a) / toCd(L2.a)).real(), b = (toCd(L1.b - L2.b) / toCd(L2.a)).real();
            ld l = (-b) / a;
            ld r = (1-b) / a;
            if(l > r) swap(l, r);
            if(r < 0 || l > 1)
                cout << "none\n";
            else {
                cd p1 = toCd(L1.b) + toCd(L1.a) * clamp<ld>(l, 0, 1);
                cd p2 = toCd(L1.b) + toCd(L1.a) * clamp<ld>(r, 0, 1);
                if(p1.real() > p2.real() || (p1.real() == p2.real() && p1.imag() > p2.imag()))
                    swap(p1, p2);
                if(p1 != p2)
                    print(p1, p2);
                else
                    print(p1);
            }
        } else {
            cout << "none\n";
        }
    } else {
        // L1.a * t + L1.b = L2.a * s + L2.b
        // |L1.a| * t + (L1.b - L2.b)*conj(L1.a) = L2.a * conj(L1.a) * s
        ld s = ((L1.b - L2.b) * conj(L1.a)).imag() / ld((L2.a * conj(L1.a)).imag());
        ld t = ((L2.b - L1.b) * conj(L2.a)).imag() / ld((L1.a * conj(L2.a)).imag());
        cd p = toCd(L2.b) + s * toCd(L2.a);
        cd q = toCd(L1.b) + t * toCd(L1.a);
        // cerr << "(s, t) = (" << s << ", " << t << ")\n";
        // cerr << L1.contain(p) << ' ' << L2.contain(p) << '\n';
        // print(p - q);
        if(0 <= s && s <= 1 && 0 <= t && t <= 1)
            print(p);
        else
            cout << "none\n";
    }
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    cout << fixed << setprecision(2);
    int q;
    cin >> q;
    while(q--)
        solve();
}
