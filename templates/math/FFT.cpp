template <typename T> void buildRoots(complex<T> roots[]) {
    const T pi = acos(-1);
    for(int i = 1; i < maxn; i *= 2) {
        for(int j = 0; j < i; j++) {
            roots[i + j] = polar<T>(1, pi * j / i);
        }
    }
}

template <typename T>
void inplace_fft(T F[], int n, bool inv) {
    static T roots[maxn];
    static bool inited;
    if (!inited) {
        buildRoots(roots);
        inited = true;
    }
    for (int i = 0, j = 0; i < n; i++) {
        if (i < j) swap(F[i], F[j]);
        for (int k = n>>1; (j^=k) < k; k>>=1);
    }
    for (int step = 1; step < n; step *= 2) {
        for (int i = 0; i < n; i += step * 2) {
            for (int j = 0; j < step; j++) {
                T a = F[i+j];
                T b = F[i+j+step] * roots[step + j];
                F[i+j] = a + b;
                F[i+j+step] = a - b;
            }
        }
    }
    if (inv) {
        T invn = T(1) / n;
        for (int i = 0; i < n; i++) F[i] *= invn;
        reverse(F + 1, F + n);
    }
}
template <typename T> vector<T> fft(vector<T> F, bool inv) {
    inplace_fft(F.data(), F.size(), inv);
    return F;
}
