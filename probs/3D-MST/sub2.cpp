#include <iostream>
#include <algorithm>
#include <chrono>
#define TIME Timer __timer(__PRETTY_FUNCTION__)
using namespace std;
class Timer {
private:
    std::string title;
    chrono::high_resolution_clock::time_point start;
public:
    Timer(std::string t) :
        title(t), start(chrono::high_resolution_clock::now()) {}
    ~Timer() {
        auto finish = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(finish - start).count();
        double ms = double(duration) * 0.001;
        std::cerr << "Timer: " << title << " takes " << ms << " ms to finish.\n";
    }
};


struct Edge {
    int u, v;
    long long w;
    bool operator<(const Edge &e) {
        return w < e.w;
    }
}edge[5000 * 4999 / 2];

struct Vertex {
    int x, y, z;
    bool operator<(const Vertex &v) const {
        int a=x+y+z, va = v.x+v.y+v.z; if(a != va) return a < va;
        int b=x-y+z, vb = v.x-v.y+v.z; if(b != vb) return b < vb;
        int c=x+y-z, vc = v.x+v.y-v.z; if(c != vc) return c < vc;
        if (x != v.x) return x < v.x;
        if (y != v.y) return y < v.y;
        return z < v.z;
    }
}vertex[5000];

int boss[5000];

int finds(int x) {
    if (x == boss[x]) return x;
    return boss[x] = finds(boss[x]);
}

long long Union(int u, int v, long long w) {
    u = finds(u), v = finds(v);
    if (u == v) return 0;
    return boss[u] = v, w;
}

int main(int argc, char **argv) {
    TIME;
    ios::sync_with_stdio(0), cin.tie(0);
    int n, tp = 0;
    long long ans = 0;
    cin >> n;
    for (int i = 0; i < n; ++i)
        cin >> vertex[i].x >> vertex[i].y >> vertex[i].z, boss[i] = i;
    sort(vertex, vertex + n);
    for (int i = 0; i < n; ++i) {
        for (int j = max(0, i - 1500); j < i; ++j)
            edge[tp++] = Edge{i, j,
                (long long)(vertex[i].x - vertex[j].x) * (vertex[i].x - vertex[j].x) +
                (long long)(vertex[i].y - vertex[j].y) * (vertex[i].y - vertex[j].y) +
                (long long)(vertex[i].z - vertex[j].z) * (vertex[i].z - vertex[j].z)};
    }
    sort(edge, edge + tp);
    for (int i = 0; i < tp; ++i)
        ans += Union(edge[i].u, edge[i].v, edge[i].w);
    cout << ans << "\n";
}
