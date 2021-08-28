// NOTE: Point is complex<Real>
// cross(pt, line.ed-line.st)<=0 <-> pt in half plane
struct Line {
    Point st, ed;
    Point dir;
    Line (Point _s, Point _e) : st(_s), ed(_e), dir(_e - _s) {}
};

bool operator<(const Line &lhs, const Line &rhs) {
    if (int cmp = argCmp(lhs.dir, rhs.dir))
        return cmp == -1;
    return ori(lhs.st, lhs.ed, rhs.st) < 0;
}
Point intersect(const Line &A, const Line &B) {
    Real t = cross(B.st - A.st, B.dir) / cross(A.dir, B.dir);
    return A.st + t * A.dir;
}

Real HPI(vector<Line> &lines) {
    sort(lines.begin(), lines.end());
    deque<Line> que;
    deque<Point> pt;
    que.push_back(lines[0]);
    for (int i = 1; i < (int)lines.size(); i++) {
        if (argCmp(lines[i].dir, lines[i-1].dir) == 0) continue;
#define POP(L, R) \
        while (pt.size() > 0 && ori(L.st, L.ed, pt.back()) < 0) \
            pt.pop_back(), que.pop_back(); \
        while (pt.size() > 0 && ori(R.st, R.ed, pt.front()) < 0) \
            pt.pop_front(), que.pop_front();
        POP(lines[i], lines[i]);
        pt.push_back(intersect(que.back(), lines[i]));
        que.push_back(lines[i]);
    }
    POP(que.front(), que.back())
    if (que.size() <= 1 || argCmp(que.front().dir, que.back().dir) == 0)
        return 0;
    pt.push_back(intersect(que.front(), que.back()));
    return area(pt);
}
