///Source: SCPC 2018: Histogram
#include<bits/stdc++.h>
using namespace std;

const int MAXN = 1000003;
int n;
double h[MAXN];
double hsum[MAXN];
double hsqsum[MAXN];

inline double hpartial(int st, int ed) {
    return hsum[ed] - hsum[st - 1];
}
inline double hsqpartial(int st, int ed) {
    return hsqsum[ed] - hsqsum[st - 1];
}
inline double minpt(int st, int ed) {
    return hpartial(st, ed) / (double)(ed - st + 1);
}
inline double sqcalc(double a, double b, double c, double x) {
    return a * x * x + b * x + c;
}

struct Point {
    double x, y;
    Point operator-(const Point& r) const {
        return Point{ x - r.x, y - r.y };
    }
};
inline double inner(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
}
inline double outer(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
}
inline double ccw(const Point& a, const Point& b, const Point& c) {
    return outer(b - a, c - a) - 0;
}

void proc(int caseidx) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        double p;
        cin >> p;
        h[i] = p;
        hsum[i] = hsum[i - 1] + h[i];
        hsqsum[i] = hsqsum[i - 1] + h[i] * h[i];
    }

    vector<Point> pts, lower;
    pts.push_back(Point{ 0, 0 });
    for (int i = 1; i <= n; ++i) {
        pts.push_back(Point{ (double)i, hsum[i] });
    }

    sort(pts.begin(), pts.end(), [](const Point& a, const Point& b) {
        return abs(a.x - b.x) < (1e-6) ? a.y < b.y : a.x < b.x;
    });
    for (const auto& p : pts) {
        while (lower.size() >= 2 && ccw(*++lower.rbegin(), *lower.rbegin(), p) <= 0) lower.pop_back();
        lower.emplace_back(p);
    }

    double mmans = 0;
    int prv = 0;
    for (int i = 1; i < (int)lower.size(); ++i) {
        int st = prv + 1;
        int minid = lower[i].x;
        double minv = minpt(st, minid);
        mmans += sqcalc(
            minid - st + 1,
            (-2) * hpartial(st, minid),
            hsqpartial(st, minid),
            minv
        );
        prv = lower[i].x;
    }

    cout << fixed << setprecision(10) << sqrt(mmans) << '\n';
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    //cin >> t;
    for (int i = 1; i <= t; ++i) {
        proc(i);
    }
    return 0;
}
