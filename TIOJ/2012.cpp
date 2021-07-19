#include <bits/stdc++.h>
#define debug(a...) qqbx(#a, a)
template <typename ...T> void qqbx(const char *s, T ...a) {
    int cnt = sizeof...(T);
    ((std::cerr << "(" << s << ") = (") , ... , (std::cerr << a << (--cnt ? ", " : ")\n")));
}

using namespace std;
using ld = long double;
const int maxn = 625;

ld A[maxn][maxn], B[maxn];
ld x[maxn];
int p[maxn];
void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int c;
        for (int j = 0; j < n; j++) {
            cin >> c;
            A[i][j] = c;
        }
        cin >> c;
        B[i] = c;
    }

    auto print = [n]() {
        cerr << fixed << setprecision(5);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                cerr << A[i][j] << '\t';
            cerr << "|\t";
            cerr << B[i] << '\n';
        }
        for (int i = 0; i < n; i++)
            cerr << p[i] << ' ';
        cerr << '\n';
    };
    iota(p, p+n, 0);
    for (int k = 0; k < n; k++) {
        int mxr = -1, mxc = -1;
        ld mx = 0;
        for (int i = k; i < n; i++) for (int j = k; j < n; j++) {
            if (abs(A[i][j]) > mx)
                mxr = i, mxc = j, mx = abs(A[i][j]);
        }
        // debug(mxr, mxc);

        // assert(mx > 0)

        // print();
        if (mxr != k) {
            for (int j = k; j < n; j++)
                swap(A[mxr][j], A[k][j]);
            swap(B[mxr], B[k]);
        }
        if (mxc != k) {
            for (int i = 0; i < n; i++)
                swap(A[i][mxc], A[i][k]);
            swap(p[mxc], p[k]);
        }
        // print();
        for (int i = k+1; i < n; i++) {
            ld r = -A[i][k] / A[k][k];
            for (int j = k; j < n; j++) {
                A[i][j] += r * A[k][j];
            }
            B[i] += r * B[k];
        }
    }
    for (int i = n-1; i >= 0; i--) {
        ld sum = B[i];
        for (int j = i+1; j < n; j++) sum -= A[i][j] * x[p[j]];
        x[p[i]] = sum / A[i][i];
    }
    for (int i = 0; i < n; i++)
        cout << x[i] << '\n';
}
signed main() {
    cout << fixed << setprecision(20);
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
}
